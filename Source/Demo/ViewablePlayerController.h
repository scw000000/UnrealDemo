// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ViewablePlayerController.generated.h"

class ABasicCharacter;

/**
 * 
 */
UCLASS()
class DEMO_API AViewablePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
   // Sets default values for this character's properties
   AViewablePlayerController( const FObjectInitializer& ObjectInitializer );

   virtual void SetupInputComponent( ) override;

   // Called when the game starts or when spawned
   virtual void BeginPlay( ) override;

   UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn" )
      virtual void Possess( APawn * InPawn ) override;

   virtual void CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult ) override;

   void Tick( float DeltaTime ) override;

   //custom function for movement
   void Yaw( float amount );

   //custom function for movement
   void Pitch( float amount );

   bool SetControllingCharacter( APawn* InPawn );

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* m_Camera;

   //camera boom of yaw and pitch
   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_CameraBoomYaw;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_CameraBoomPitch;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = CharacterProperties )
      UClass* BPCharacter;
protected:
   ABasicCharacter* m_ControllingCharacter;
	
};
