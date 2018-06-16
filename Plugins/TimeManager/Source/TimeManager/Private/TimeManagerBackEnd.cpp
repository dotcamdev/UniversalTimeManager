// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TimeManagerBackEnd.h"

#define LOCTEXT_NAMESPACE "FTimeManagerModule"

void FTimeManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
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
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTimeManagerModule, TimeManager)

