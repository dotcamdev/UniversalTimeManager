#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "TimeManagerBackEnd.h"
#include "TimeManagerFrontEnd.generated.h"


//An actor based calendar system for tracking date + time, and Sun/Moon rotation/phase.
UCLASS(BlueprintType)
class ATimeManagerFrontEnd : public AActor
{
	GENERATED_UCLASS_BODY()

public:
		
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		void InitializeCalendar(FTimeDate time);

private:

	FTimeManagerModule TimeManagerBackEnd = FTimeManagerModule::Get();
	
};