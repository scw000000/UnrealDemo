// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.h"
#include "ViewablePlayerController.generated.h"

class ABasicCharacter;
class ACameraBoom;
/**
 * 
 */
UCLASS()
class DEMO_API AViewablePlayerController : public ABasicPlayerController
{
	GENERATED_BODY()

public:
   // Sets default values for this character's properties
   AViewablePlayerController( const FObjectInitializer& ObjectInitializer );

   virtual void SetupInputComponent( ) override;

   // Called when the game starts or when spawned
   virtual void BeginPlay( ) override;

   virtual void CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult ) override;

   void AttachToCameraBoom();

   void Tick( float DeltaTime ) override;

   //custom function for movement
   void Yaw( float amount );

   //custom function for movement
   void Pitch( float amount );

   //bool SetControllingCharacter( APawn* InPawn );


   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* m_Camera;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UClass* m_BPCameraBoom;
private:
	
};
