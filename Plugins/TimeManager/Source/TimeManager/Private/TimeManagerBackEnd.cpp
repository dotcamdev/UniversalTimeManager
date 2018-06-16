// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TimeManagerBackEnd.h"
#include "EngineUtils.h"


#define LOCTEXT_NAMESPACE "FTimeManagerModule"

void FTimeManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	//Declare what function we will delegate
	//FWorldDelegates::FWorldEvent::FDelegate OnPostWorldCreationDelegate;
	//Setup our delegate
	//OnPostWorldCreationDelegate = FWorldDelegates::FWorldEvent::FDelegate::CreateRaw(this, &FTimeManagerModule::Init);
	//Register our delegate
	//FDelegateHandle OnPostWorldCreationDelegateHandle = FWorldDelegates::OnPostWorldCreation.Add(OnPostWorldCreationDelegate);

	FWorldDelegates::FWorldInitializationEvent::FDelegate OnWorldCreatedDelegate;
	OnWorldCreatedDelegate = FWorldDelegates::FWorldInitializationEvent::FDelegate::CreateRaw(this, &FTimeManagerModule::OnWorldCreated);
	FDelegateHandle OnWorldCreatedDelegateHandle = FWorldDelegates::OnPostWorldInitialization.Add(OnWorldCreatedDelegate);
	
}

void FTimeManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FTimeManagerModule::OnWorldCreated(UWorld* World, const UWorld::InitializationValues IVS)
{
	//If we already have a TimeManagerActor do not spawn another one
	for (TActorIterator<ATimeManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		return;
	}
	FVector location = FVector(0,0,0);
	FRotator rotate = FRotator(0,0,0);
	FActorSpawnParameters SpawnInfo;
	/*TimeManagerActor = */World->SpawnActor<ATimeManager>(ATimeManager::StaticClass(), location, rotate, SpawnInfo);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTimeManagerModule, TimeManager)

