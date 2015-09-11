// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "ParasiticCharacter.h"

AParasiticCharacter::AParasiticCharacter( const FObjectInitializer& ObjectInitializer ) : ABasicCharacter( ObjectInitializer ) 
{
   GetCapsuleComponent()->OnComponentHit.AddDynamic( this, &AParasiticCharacter::OnHit );
   parasitizingHuman = false;
   parasitizeTimeMax = 5.0f;
}

void AParasiticCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AParasiticCharacter::OnHit_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
   ABasicCharacter *otherCharacter = Cast<ABasicCharacter>( OtherActor );
   if( otherCharacter != nullptr && !parasitizingHuman)
      {  
      //attach to otherCharacter
      OnParasitize( otherCharacter );    
      //start timer
      parasitizingDelegate = FTimerDelegate::CreateUObject( this, &AParasiticCharacter::Parasitize, otherCharacter );
      GetWorld()->GetTimerManager().SetTimer( parasitizingTimerHandle, parasitizingDelegate, parasitizeTimeMax, false);
      parasitizingHuman = true;
      }
   else
      {
      }
}

void AParasiticCharacter::OnParasitize( ABasicCharacter* target )
{
   //disable collision, movement and gravity
   GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
   GetWorld( )->GetFirstPlayerController( )->SetIgnoreMoveInput( true );
   GetMovementComponent()->StopMovementImmediately();
   GetCharacterMovement()->GravityScale = 0.f;
 
   //attach to target, while preserving its height
   this->AttachRootComponentTo( target->GetCapsuleComponent(), NAME_None, EAttachLocation::KeepWorldPosition );
   float relativeHeight = GetRootComponent()->GetRelativeTransform().GetLocation().Z;
   GetRootComponent()->SetRelativeLocation( FVector( 0.f, 0.f, relativeHeight ) );
}

void AParasiticCharacter::Parasitize( ABasicCharacter* target )
{
   APlayerController* pController = GetWorld( )->GetFirstPlayerController( );
   pController->Possess( target );
   GetMesh()->SetVisibility( false );
}


