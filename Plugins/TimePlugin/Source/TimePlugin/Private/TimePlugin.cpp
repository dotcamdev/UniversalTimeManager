// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TimePlugin.h"
#include "EngineUtils.h"



void FTimePlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	//Create our delegate type
	FWorldDelegates::FWorldInitializationEvent::FDelegate OnWorldCreatedDelegate;
	//Declare which function we want to bind to
	OnWorldCreatedDelegate = FWorldDelegates::FWorldInitializationEvent::FDelegate::CreateRaw(this, &FTimePlugin::OnWorldCreated);
	//Declare which event we want to bind to
	FDelegateHandle OnWorldCreatedDelegateHandle = FWorldDelegates::OnPostWorldInitialization.Add(OnWorldCreatedDelegate);
}

void FTimePlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FTimePlugin::OnWorldCreated(UWorld* World, const UWorld::InitializationValues IVS)
{
	//If we already have a TimeManagerActor do not spawn another one
	//Just store it as the current TimeManagerActor for other plugins to use
	for (TActorIterator<ATimeManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		TimeManagerActor = *ActorItr;
		return;
	}
	FVector location = FVector(0,0,0);
	FRotator rotate = FRotator(0,0,0);
	FActorSpawnParameters SpawnInfo;
	TimeManagerActor = World->SpawnActor<ATimeManager>(ATimeManager::StaticClass(), location, rotate, SpawnInfo);
}

	
IMPLEMENT_MODULE(FTimePlugin, TimePlugin)

