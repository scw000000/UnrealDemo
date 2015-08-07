// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BasicCharacter.h"

// Sets default values
ABasicCharacter::ABasicCharacter( const FObjectInitializer& ObjectInitializer ) 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
   m_CameraBoomShift = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "Camera Spring Arm Shift" ) );
   m_CameraBoomShift->AttachTo( RootComponent );
   m_CameraBoomShift->TargetArmLength = 300.0f;
   m_CameraBoomShift->bUsePawnControlRotation = false;

   m_CameraBoomRotation = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>( this, TEXT( "Camera Spring Arm Rotation" ) );
   m_CameraBoomRotation->AttachTo( m_CameraBoomShift );
   m_CameraBoomRotation->TargetArmLength = 300.0f;
   m_CameraBoomRotation->bUsePawnControlRotation = false;
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

USpringArmComponent* ABasicCharacter::GetCameraBoomShift( )
{
   return m_CameraBoomShift;
}

USpringArmComponent* ABasicCharacter::GetCameraBoomRotation( )
   {
   return m_CameraBoomRotation;
   }


