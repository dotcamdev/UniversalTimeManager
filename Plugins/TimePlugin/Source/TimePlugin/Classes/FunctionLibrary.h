#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionLibrary.generated.h"
 
UCLASS() 
class UTimeManagerFunctionLibrary :	public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
 
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
	static FORCEINLINE bool IsValid()
	{
		return true;
	}

	UFUNCTION(BlueprintCallable, Category = "TimeManager")
	static int32 ExampleTimeManagerFunction();
};