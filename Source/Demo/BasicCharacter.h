// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UCLASS()
class DEMO_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
   ABasicCharacter( const FObjectInitializer& ObjectInitializer );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
   void SetViewPointToThirdPerson();

   void SetViewPointToFirstPerson();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_ThirdPersonArmYaw;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_ThirdPersonArmPitch;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      UCameraComponent* m_PlayerCamera;

   //custom function for movement
   void MoveForward( float amount );

   //custom function for movement
   void MoveRight( float amount );

   void Yaw( float amount );

   void Pitch( float amount );

private:
   
	
};
