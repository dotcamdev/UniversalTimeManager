#include "TimeManagerFrontEnd.h"
#include "TimeManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "ModuleManager.h"

ATimeManagerFrontEnd::ATimeManagerFrontEnd(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ATimeManagerFrontEnd::InitializeCalendar(FTimeDate time)
{
	bool test = FTimeManagerModule::Get().IsThisNumber42(42);
	FTimeManagerModule::Get().InitializeCalendar(time);
	return test;
	
	
}