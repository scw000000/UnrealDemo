#pragma once
#include "AnimMontageProperties.generated.h"

USTRUCT(BlueprintType)
struct FAnimMontageProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim Properties")
   	int32 SampleInt32;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flower Struct")
	   AActor* TargetActor;
 	//Constructor
	FAnimMontageProperties()
	{
		//Always initialize your USTRUCT variables!
		//   exception is if you know the variable type has its own default constructor
		SampleInt32 	= 5;
		TargetActor = NULL;
	}
};  