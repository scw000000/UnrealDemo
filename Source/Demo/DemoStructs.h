/*
#pragma once
#include "DemoStructs.generated.h"

USTRUCT( BlueprintType )
struct AmmoProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      UClass* BPAmmo;
 	//Constructor
	AmmoProperties()
	{
		//Always initialize your USTRUCT variables!
		//   exception is if you know the variable type has its own default constructor
		SampleInt32 	= 5;
		TargetActor = NULL;
	}
};*/