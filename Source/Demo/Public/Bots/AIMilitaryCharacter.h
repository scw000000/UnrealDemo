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

   virtual void PostInitializeComponents() override;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComponent )
	   class UBehaviorTree* botBehavior;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComponent )
      class UPawnSensingComponent* pawnSensingComp;

protected:

      UFUNCTION()
   void OnHearNoise( APawn *OtherActor, const FVector &Location, float Volume );

      UFUNCTION()
   void OnSeePawn( APawn *OtherPawn );

   
};
