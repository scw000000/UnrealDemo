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

   void Tick( float DeltaTime ) override;
	
   //custom function for movement
   void MoveForward( float amount );

   //custom function for movement
   void MoveRight( float amount );

   //custom function for movement
   void Yaw( float amount );

   //custom function for movement
   void Pitch( float amount );

   void SetControllingCharacter( ABasicCharacter* character );

   

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      UClass* BPCharacter;
private:
   ABasicCharacter* m_ControllingCharacter;
};
