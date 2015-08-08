// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class ABasicCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
   // Called when the game starts or when spawned
   virtual void BeginPlay( ) override;

   UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn" )
      virtual void Possess( APawn * InPawn ) override;

   virtual bool SetControllingCharacter( APawn* InPawn );

protected:
   ABasicCharacter* m_ControllingCharacter;
	
	
};
