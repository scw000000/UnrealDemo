// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "ThirdPersonCameraBoom.h"
#include "SingleArmCameraBoom.h"
#include "BasicCharacter.h"

// Sets default values
ABasicCharacter::ABasicCharacter( const FObjectInitializer& ObjectInitializer ) 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay( )
{
	Super::BeginPlay();
}

// Called every frame
void ABasicCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

