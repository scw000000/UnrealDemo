// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "CameraBoom.h"


// Sets default values
ACameraBoom::ACameraBoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraBoom::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraBoom::Yaw( float amount )
{
}

void ACameraBoom::Pitch( float amount )
{
}

USceneComponent* ACameraBoom::GetCameraAttachComponent( )
{
   return NULL;
}

// Called every frame
void ACameraBoom::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ACameraBoom::AttachToCharacter( ABasicCharacter *inCharacter )
{
   return false;
}

FName ACameraBoom::GetSocketName( )
 {
 return FName();
 }
