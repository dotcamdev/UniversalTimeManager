#pragma once
 
#include "FunctionLibrary.generated.h"
 
UCLASS() 
class UTimeManagerFunctionLibrary : public UObject
{
	GENERATED_UCLASS_BODY()
 
	//FORCEINLNE function
	static FORCEINLINE bool IsValid()
	{
		return true;
	}
 
	//cpp function
	static int32 ComplicatedGameDataAnalysis();
};