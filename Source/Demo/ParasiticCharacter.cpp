// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "ParasiticCharacter.h"

AParasiticCharacter::AParasiticCharacter( const FObjectInitializer& ObjectInitializer ) : ABasicCharacter( ObjectInitializer ) 
{
  // ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &AParasiticCharacter::Prox );
   GetCapsuleComponent()->OnComponentHit.AddDynamic( this, &AParasiticCharacter::OnHit );
   parasitizingHuman = false;
   //capsuleComponent->
 //  UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
  // capsuleComponent->OnComponentBeginOverlap.AddDynamic( this, &AParasiticCharacter::Prox );
  // ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &APickupItem::Prox );
}

void AParasiticCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
   
}

void AParasiticCharacter::OnHit_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
   ABasicCharacter *otherCharacter = Cast<ABasicCharacter>( OtherActor );
   if( otherCharacter != nullptr )
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess enter" );
      Parasitize( otherCharacter );
      }
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "cast fail" );
      }
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "possess end" );
}

void AParasiticCharacter::Parasitize( ABasicCharacter* target )
{
   if( !parasitizingHuman )
      {
    //  GetCapsuleComponent()->SetCollisionObjectType();
      GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
      APlayerController* pController = GetWorld( )->GetFirstPlayerController( );
      pController->Possess( target );
      this->AttachRootComponentTo( target->GetCapsuleComponent(), NAME_None, EAttachLocation::SnapToTarget );
     // this->AttachRootComponentToActor( target, NAME_None, EAttachLocation::KeepRelativeOffset );
      parasitizingHuman = true;
      }
   
}


