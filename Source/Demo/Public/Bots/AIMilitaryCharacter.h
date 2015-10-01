// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MilitaryCharacter.h"
#include "AIMilitaryCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AAIMilitaryCharacter : public AMilitaryCharacter
{
	GENERATED_BODY()
public:
	AAIMilitaryCharacter( const FObjectInitializer& ObjectInitializer ) ;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AI )
	   class UBehaviorTree* botBehavior;
	
};
