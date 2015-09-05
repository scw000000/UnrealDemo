// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "ParasiticCharacter.h"

AParasiticCharacter::AParasiticCharacter( const FObjectInitializer& ObjectInitializer ) : ABasicCharacter( ObjectInitializer ) 
{
ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>( this, TEXT( "Proximity SPhere" ) );
   ProxSphere->AttachTo( GetRootComponent() );
   ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &AParasiticCharacter::Prox );
 //  UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
  // capsuleComponent->OnComponentBeginOverlap.AddDynamic( this, &AParasiticCharacter::Prox );
  // ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &APickupItem::Prox );
}

void AParasiticCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
   
}

void AParasiticCharacter::Prox_Implementation( AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult )
{
   APlayerController* pController = GetWorld( )->GetFirstPlayerController( );

   ABasicCharacter *character = Cast<ABasicCharacter>( OtherActor );
   if( character != nullptr )
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess enter" );
      pController->Possess( character );
      }
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "cast fail" );
      }
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess end" );
}

