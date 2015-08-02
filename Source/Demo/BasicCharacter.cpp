// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"
#include "BasicPlayerController.h"

// Sets default values
ABasicCharacter::ABasicCharacter( const FObjectInitializer& ObjectInitializer ) 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
   m_SpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "Camera Spring Arm" ) );
   m_SpringArm->AttachTo( RootComponent );
   m_SpringArm->TargetArmLength = 300.0f;
   m_SpringArm->bUsePawnControlRotation = true;
   //ACharacter::CharacterMovementComponentName.ToString
   
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay( )
{
	Super::BeginPlay();
//   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, ACharacter::CharacterInputComponentName.ToString( ) );
  // this->InputComponent
}

// Called every frame
void ABasicCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


