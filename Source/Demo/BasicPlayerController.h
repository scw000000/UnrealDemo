// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

/**
 * 
 */
class ABasicCharacter;

UCLASS()
class DEMO_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
public:	
   // Sets default values for this character's properties
   ABasicPlayerController( const FObjectInitializer& ObjectInitializer );

   virtual void SetupInputComponent( ) override;

   // Called when the game starts or when spawned
   virtual void BeginPlay() override;

  void InitiateCamrea();

   UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn" )
      virtual void Possess( APawn * InPawn ) override;

   virtual void CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult ) override;

   void Tick( float DeltaTime ) override;
	
   //custom function for movement
   void MoveForward( float amount );

   //custom function for movement
   void MoveRight( float amount );

   //custom function for movement
   void Yaw( float amount );

   //custom function for movement
   void Pitch( float amount );

   bool SetControllingCharacter( APawn* InPawn );

   

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* m_Camera;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterProperties )
      UClass* BPCharacter;
private:
   ABasicCharacter* m_ControllingCharacter;
};
