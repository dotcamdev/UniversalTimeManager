// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
#include "FunctionLibrary.h"
 
//////////////////////////////////////////////////////////////////////////
// MyStaticLibrary
 
UTimeManagerFunctionLibrary::UTimeManagerFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 
}
 
int32 UTimeManagerFunctionLibrary::ComplicatedGameDataAnalysis()
{
	//Do lots of stuff that requires the entire Game's compiled header source,
	//  involving lots of your custom project-specific classes,
	//    classes that have not been compiled in the .h of this library 
	//    since they depend on it.
        return 9000;
}