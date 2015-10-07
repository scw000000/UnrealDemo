// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "AIMilitaryCharacter.h"
#include "Bots/DemoAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

AAIMilitaryCharacter::AAIMilitaryCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AIControllerClass = ADemoAIController::StaticClass();

   pawnSensingComp = ObjectInitializer.CreateDefaultSubobject<UPawnSensingComponent>(this, TEXT("Pawn Sensor") );
   pawnSensingComp->SensingInterval = .5f; // 4 times per second
   pawnSensingComp->bOnlySensePlayers = false;
   pawnSensingComp->SetPeripheralVisionAngle( 65.f );
}

void AAIMilitaryCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    pawnSensingComp->OnSeePawn.AddDynamic( this, &AAIMilitaryCharacter::OnSeePawn );
    pawnSensingComp->OnHearNoise.AddDynamic( this, &AAIMilitaryCharacter::OnHearNoise );
}

void AAIMilitaryCharacter::OnHearNoise( APawn *otherPawn, const FVector &location, float volume )
{

    const FString VolumeDesc = FString::Printf(TEXT(" at volume %f"), volume);    
    FString message = TEXT("Heard Actor ") + otherPawn->GetName() + VolumeDesc;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
}

void AAIMilitaryCharacter::OnSeePawn( APawn *otherPawn )
{
    FString message = TEXT("Saw Actor ") + otherPawn->GetName();
    
    ADemoAIController* myAIController = Cast<ADemoAIController>( Controller );
    ABasicCharacter* otherCharacter = Cast<ABasicCharacter>( otherPawn );
    if( myAIController && otherCharacter->IsAlive() && otherCharacter->IsEnemyFor( this ) )
       {
       if( pawnSensingComp->CouldSeePawn( otherCharacter ) && pawnSensingComp->HasLineOfSightTo( otherCharacter ) )
          {
          GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
          }
       
     //  myAICoroller->SetEnemy( OtherPawn );
       }
}


