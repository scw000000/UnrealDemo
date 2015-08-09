// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

   virtual void PostInitializeComponents( ) override;

   // Called when the game starts or when spawned
   virtual void BeginPlay( ) override;

   void AttachCameraComponents();

   // Called every frame
   virtual void Tick( float DeltaSeconds ) override;

   UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn" )
      virtual void Possess( APawn * InPawn ) override;

   virtual void CalcCamera( float DeltaTime, struct FMinimalViewInfo& OutResult ) override;

   //custom function for movement
   void Yaw( float amount );

   //custom function for movement
   void Pitch( float amount );

   //bool SetControllingCharacter( APawn* InPawn );


   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* m_Camera;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UClass* m_BPCameraBoom;

   //custom function for movement
   //void MoveForward( float amount );

   //custom function for movement
   //void MoveRight( float amount );
private:
   ACameraBoom *m_CameraBoom;
	
};
