// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "TimeDateStruct.h"

class FTimeManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	bool IsThisNumber42(int32 num);
	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FTimeManagerModule& Get()
	{
		return FModuleManager::LoadModuleChecked< FTimeManagerModule >("TimeManager");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("TimeManager");
	}



// Current Local Clock Time (LCT)
	FTimeDate CurrentLocalTime;

// The Latitude of the local location (-90 to +90 in degrees)
	float Latitude = 0.0f;

// The Longitude of the local location (-180 to +180 in degrees)
	float Longitude = 0.0f;

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

		
// -------------------
// PUBLIC FUNCTIONS
// -------------------

/**
* Name: InitializeCalendar
* Description: Initializes the calendar with the provided TimeDate, and validates the range of all input values.
*
* @param: time (TimeDate) - The TimeDate value to calculate from.
*/
	void InitializeCalendar(FTimeDate time);


/**
* Name: GetDayOfYear
* Description: Gets the number of full days elapsed in the current year for the provided date.
*
* @param: time (TimeDate) - The TimeDate value to calculate from.
* @return: int32 - The number of days elapsed in the current year.
*/
	int32 GetDayOfYear(FTimeDate time);

/**
* Name: DaysInYear
* Description: Gets the total number of days in a given year (takes leap years into account).
*
* @param: year (int32) - The year value.
* @return: int32 - The total number of days in the given year.
*/
	int32 GetDaysInYear(int32 year);

/**
* Name: DaysInMonth
* Description: The number of days in the specified month (leap years are taken into account).
*
* @param: month (int32) - The month value.
* @param: year (int32) - The year value.
* @return: int32 - The number of days in the given month for the given year.
*/
	int32 GetDaysInMonth(int32 year, int32 month);

/**
* Name: GetElapsedDayInMinutes
* Description: Gets the accumulated number of minutes (plus fractional) for the current day.
*
* @return: float - The number of minutes (plus fractional minute - NOT seconds) elapsed in the given day.
*/
	float GetElapsedDayInMinutes();


/**
* Name: SetCurrentLocalTime
* Description: Sets the local time from minutes, and runs InitializeCalendar to validate and set variables.
*
* @param: time (float) - The number of minutes (+ frac minutes) to calculate from.
*/
	void SetCurrentLocalTime(float time);



/**
* Name: GetDayPhase
* Description: Gets the current day phase in a 0 to 1 range (fractional).
*
* @return: float - The day phase in a 0.0 to 1.0 range.
*/
	float GetDayPhase();


/**
* Name: GetYearPhase
* Description: Gets the current year phase in a 0 to 1 range (fractional).
*
* @return: float - The year phase in a 0.0 to 1.0 range.
*/
	float GetYearPhase();

/**
* Name: IsLeapYear
* Description: Determines whether the specified year is a leap year.
*
* @param: year (int32) - The year value to check
* @return: bool - Will return true if it is a leap year, otherwise false.
*/
	bool IsLeapYear(int32 year);


/**
* Name: IncrementTime
* Description: Increments time based on the deltaSeconds * TimeScaleMultiplier
*
* @param: deltaSeconds (float) - The Tick (or accumulated ticks) delta time since the last update
*///float deltaSeconds
	void IncrementTime(UWorld * World, ELevelTick TickType, float deltaTime);


//private:
	//This is no longer needed since we auto init during module startup
	//bool bIsCalendarInitialized = false;

	FDateTime InternalTime;

	// The UTC + DST TimeSpan difference vs current time
	FTimespan SpanUTC;

	// The Julian Day number for Jan 1, 2000 @ 12:00 UTC
	double JD2000 = 2451545.0;

	// The Julian Day number for Jan 1, 1900 @ 12:00 UTC
	double JD1900 = 2415020.0;

	double ElapsedJD1900 = 0.0;

	// Obliquity of the Ecliptic (as of 2000/01/01 - approximation, but fairly accurate)
	double EcObliquity = 23.4397;

	/* --- Utility Functions --- */

	// Float versions

	FTimeDate ConvertToTimeDate(FDateTime dt);

	FDateTime ConvertToDateTime(FTimeDate td);

	FTimeDate ValidateTimeDate(FTimeDate time);

	// TODO - Requires extra functions & rewriting to accommodate, FUTURE/NOT URGENT
	// Designates that the calendar should use custom Date & Time struct rather than
	// using the built in DateTime values. This is useful for worlds that have longer days,
	// months, and years.
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DateTime")
	//bool UsingCustomCaledar;

};
