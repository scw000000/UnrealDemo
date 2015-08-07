// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UCLASS()
class DEMO_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
   // Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sets default values for this character's properties
   ABasicCharacter( const FObjectInitializer& ObjectInitializer );
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   USpringArmComponent* GetCameraBoomShift( );

   USpringArmComponent* GetCameraBoomRotation( );

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_CameraBoomShift;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = PlayerView )
      USpringArmComponent* m_CameraBoomRotation;

};
