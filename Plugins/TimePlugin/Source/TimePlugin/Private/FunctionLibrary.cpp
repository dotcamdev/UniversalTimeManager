// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
#include "FunctionLibrary.h"
 
//////////////////////////////////////////////////////////////////////////
// MyStaticLibrary
 
UTimeManagerFunctionLibrary::UTimeManagerFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 
}
 
int32 UTimeManagerFunctionLibrary::ExampleTimeManagerFunction()
{
        return 9000;
}