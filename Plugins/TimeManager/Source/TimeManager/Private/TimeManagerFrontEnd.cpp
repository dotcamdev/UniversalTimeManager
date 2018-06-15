#include "TimeManagerFrontEnd.h"
#include "TimeManagerBackEnd.h"
#include "Kismet/KismetMathLibrary.h"
#include "ModuleManager.h"

ATimeManagerFrontEnd::ATimeManagerFrontEnd(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimeManagerFrontEnd::InitializeCalendar(FTimeDate time)
{
	TimeManagerBackEnd.InitializeCalendar(time);
}