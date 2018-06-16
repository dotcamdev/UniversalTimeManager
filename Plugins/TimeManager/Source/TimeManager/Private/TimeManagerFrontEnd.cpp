#include "TimeManagerFrontEnd.h"
#include "TimeManagerBackEnd.h"
#include "ModuleManager.h"

ATimeManagerFrontEnd::ATimeManagerFrontEnd(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimeManagerFrontEnd::InitializeCalendar(FTimeDateStruct time)
{
	TimeManagerBackEnd.InitializeCalendar(time);
}

//void ATimeManagerFrontEnd::SendFrontEnd()
//{
//}