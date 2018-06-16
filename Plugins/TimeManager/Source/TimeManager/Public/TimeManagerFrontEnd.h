#pragma once

#include "GameFramework/Actor.h"
#include  "TimeManagerBackEnd.h"
#include "TimeManagerFrontEnd.generated.h"


//An actor based calendar system for tracking date + time, and Sun/Moon rotation/phase.
UCLASS(BlueprintType)
class ATimeManagerFrontEnd : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	FTimeManagerModule TimeManagerBackEnd = FTimeManagerModule::Get();

	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		void InitializeCalendar(FTimeDateStruct time);

	//	UFUNCTION(BlueprintCallable, Category = "TimeManager")
	//		void SendFrontEnd();



	// Current Local Clock Time (LCT)
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TimeManager")
	//	TWeakObjectPtr<FTimeDateStruct> CurrentLocalTime = &TimeManagerBackEnd.CurrentLocalTime;



	// The Latitude of the local location (-90 to +90 in degrees)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float Latitude = 0.0f;

	// The Longitude of the local location (-180 to +180 in degrees)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float Longitude = 0.0f;

	// The number of hours offset from UTC for the local location (value in the range of -12 to +12 hours from UTC)	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		int32 OffsetUTC = 0;

	// The number of hours (0 or 1) to subtract for the current TimeDate for Daylight Savings Time (if enabled)
	UPROPERTY(BlueprintReadOnly, Category = "TimeManager")
		int32 OffsetDST = 0;

	// Determines whether Daylight Savings time should be enabled for the local location
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		bool bAllowDaylightSavings = false;

	// Determines whether Daylight Savings is active for the current date
	UPROPERTY(BlueprintReadOnly, Category = "TimeManager")
		bool bDaylightSavingsActive = false;

	// The value to multiply the base game time by (1 second real time is multiplied to equal X seconds in game)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float TimeScaleMultiplier = 1.0f;

private:



};