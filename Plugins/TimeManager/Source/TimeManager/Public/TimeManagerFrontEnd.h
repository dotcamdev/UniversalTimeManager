#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "TimeManager.h"
#include "TimeManagerFrontEnd.generated.h"


//An actor based calendar system for tracking date + time, and Sun/Moon rotation/phase.
UCLASS(BlueprintType)
class ATimeManagerFrontEnd : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		bool InitializeCalendar(FTimeDate time);
};