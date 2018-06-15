// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TimeManager.h"
#include "TimeDate.h"

#define LOCTEXT_NAMESPACE "FTimeManagerModule"

void FTimeManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	int32 Year, Month, Day, DayOfWeek;
	int32 Hour, Minute, Second, Millisecond;

	FPlatformTime::SystemTime(Year, Month, DayOfWeek, Day, Hour, Minute, Second, Millisecond);
	CurrentLocalTime = FTimeDate(Year, Month, Day, Hour, Minute, Second, Millisecond);
	InitializeCalendar(CurrentLocalTime);

	//Declare what function we will delegate
	FWorldDelegates::FOnWorldPostActorTick::FDelegate OnWorldTickDelegate;
	//Setup our delegate
	OnWorldTickDelegate = FWorldDelegates::FOnWorldPostActorTick::FDelegate::CreateRaw(this, &FTimeManagerModule::IncrementTime);
	//Register our delegate
	FDelegateHandle OnWorldTickDelegateHandle = FWorldDelegates::OnWorldPostActorTick.Add(OnWorldTickDelegate);

	
}

void FTimeManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FTimeManagerModule::IsThisNumber42(int32 num)
{
	return num == 42;
}

// Current Local Clock Time (LCT)
FTimeDate CurrentLocalTime;

// The number of hours offset from UTC for the local location (value in the range of -12 to +12 hours from UTC)	
int32 OffsetUTC = 0;

// The number of hours (0 or 1) to subtract for the current TimeDate for Daylight Savings Time (if enabled)
int32 OffsetDST = 0;

// Determines whether Daylight Savings time should be enabled for the local location
bool bAllowDaylightSavings = false;

// Determines whether Daylight Savings is active for the current date
bool bDaylightSavingsActive = false;

// The value to multiply the base game time by (1 second real time is multiplied to equal X seconds in game)
float TimeScaleMultiplier = 1.0f;

// The current Local Clock Time value (in minutes)
float LocalClockTime = 0.0f;

// The current Time Correction factor
float TimeCorrection = 0.0f;

// The value of the local Standard Time Meridian (15deg intervals)
int32 LSTM = 0;

int32 DayOfYear = 0;

// THe current Equation of Time value
float EoT = 0.0f;


void FTimeManagerModule::InitializeCalendar(FTimeDate time)
{
	time = ValidateTimeDate(time);

	InternalTime = ConvertToDateTime(time);
	OffsetUTC = FMath::Clamp(OffsetUTC, -12, 12);

	DayOfYear = InternalTime.GetDayOfYear();
	int32 leapDays = IsLeapYear(time.Year);

	if (DayOfYear >= (79 + leapDays) && DayOfYear < (265 + leapDays))
	{
		bDaylightSavingsActive = true;
	}

	OffsetDST = bAllowDaylightSavings && bDaylightSavingsActive ? 1 : 0;

	// Local Standard Time Meridian (degrees) = 15 * Hour Offset from UTC
	LSTM = 15 * OffsetUTC;

	SpanUTC = FTimespan((FMath::Abs(OffsetUTC) + OffsetDST), 0, 0);

	Latitude = FMath::Clamp(Latitude, -90.0f, 90.0f);
	Longitude = FMath::Clamp(Longitude, -180.0f, 180.0f);

	CurrentLocalTime = time;
}

FTimeDate FTimeManagerModule::ValidateTimeDate(FTimeDate time)
{
	time.Year = FMath::Clamp(time.Year, 1, 9999);
	time.Month = FMath::Clamp(time.Month, 1, 12);
	time.Day = FMath::Clamp(time.Day, 1, GetDaysInMonth(time.Year, time.Month));
	time.Hour = FMath::Clamp(time.Hour, 0, 23);
	time.Minute = FMath::Clamp(time.Minute, 0, 59);
	time.Second = FMath::Clamp(time.Second, 0, 59);
	time.Millisecond = FMath::Clamp(time.Millisecond, 0, 999);

	return time;
}


FTimeDate FTimeManagerModule::ConvertToTimeDate(FDateTime dt)
{
	return FTimeDate(dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), dt.GetMinute(), dt.GetSecond(), dt.GetMillisecond());
}

FDateTime FTimeManagerModule::ConvertToDateTime(FTimeDate td)
{
	return FDateTime(td.Year, td.Month, td.Day, td.Hour, td.Minute, td.Second, td.Millisecond);
}


/* --- Time of Day --- */

float FTimeManagerModule::GetElapsedDayInMinutes()
{

	return (float)InternalTime.GetTimeOfDay().GetTotalMinutes();
}

void FTimeManagerModule::IncrementTime(UWorld * World, ELevelTick TickType, float deltaTime)
{
	//Make sure we are only running on LevelTick_All ELevelTick
	if (TickType != 2)
	{
		return;
	}

	InternalTime += FTimespan::FromSeconds(deltaTime * TimeScaleMultiplier);

	if (CurrentLocalTime.Day != InternalTime.GetDay())
	{
		int32 leapDays = IsLeapYear(InternalTime.GetYear());
		DayOfYear = InternalTime.GetDayOfYear();

		if (DayOfYear >= (79 + leapDays) && DayOfYear < (265 + leapDays))
		{
			bDaylightSavingsActive = true;
		}
	}
	CurrentLocalTime = ConvertToTimeDate(InternalTime);
}


void FTimeManagerModule::SetCurrentLocalTime(float time)
{
	float minute = FMath::Frac(time / 60) * 60;
	float second = FMath::Frac(minute) * 60;
	float millisec = FMath::Frac(second) * 1000;
	FTimeDate newTD = FTimeDate(InternalTime.GetYear(), InternalTime.GetMonth(), InternalTime.GetDay(),
		FPlatformMath::FloorToInt(time / 60), minute, second, millisec);

	InitializeCalendar(newTD);
}


int32 FTimeManagerModule::GetDaysInYear(int32 year)
{
	return FDateTime::DaysInYear(year);
}


int32 FTimeManagerModule::GetDaysInMonth(int32 year, int32 month)
{
	return FDateTime::DaysInMonth(year, month);
}


int32 FTimeManagerModule::GetDayOfYear(FTimeDate time)
{
	return ConvertToDateTime(time).GetDayOfYear();
}


float FTimeManagerModule::GetDayPhase()
{
	return GetElapsedDayInMinutes() / 1440.0;
}


float FTimeManagerModule::GetYearPhase()
{
	return InternalTime.DaysInYear(InternalTime.GetYear()) / (InternalTime.GetDayOfYear() + (GetElapsedDayInMinutes() / 1440));
}


bool FTimeManagerModule::IsLeapYear(int32 year)
{
	bool isLeap = false;

	if ((year % 4) == 0)
	{
		isLeap = (year % 100) == 0 ? (year % 400) == 0 : true;
	}
	return isLeap;
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTimeManagerModule, TimeManager)

