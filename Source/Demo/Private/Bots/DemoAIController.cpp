// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BasicCharacter.h"
#include "Bots/AIMilitaryCharacter.h"
#include "GameInfo/DemoPlayerState.h"
#include "DemoGame.h"

ADemoAIController::ADemoAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	blackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = behaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp") );	
}

void ADemoAIController::FindClosestEnemy()
{
	APawn* myPawn = GetPawn();
	if( !myPawn )
	   {
		return;
	   }

	const FVector myLocation = myPawn->GetActorLocation();
	float bestTargetDistSq = MAX_FLT;
	ABasicCharacter* bestTargetPawn = NULL;

   //finding the nearest hostile pawn
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	   {
		ABasicCharacter* testPawn = Cast<ABasicCharacter>( *It );
		if ( testPawn && testPawn->IsAlive() && testPawn->IsEnemyFor( this ) )
		   {
			const float distSq = ( testPawn->GetActorLocation() - myLocation ).SizeSquared();
			if ( distSq < bestTargetDistSq )
			   {
				bestTargetDistSq = distSq;
				bestTargetPawn = testPawn;
			   }
		   }
	   }

	if ( bestTargetPawn )
	   {
		SetEnemy( bestTargetPawn );
	   }
}

void ADemoAIController::Possess( APawn* inPawn )
{
	Super::Possess( inPawn );
   
	AAIMilitaryCharacter* myCharacter = Cast<AAIMilitaryCharacter>( inPawn );

	// start behavior
	if ( myCharacter && myCharacter->botBehavior)
	{
		if ( myCharacter->botBehavior->BlackboardAsset)
		{
			blackboardComp->InitializeBlackboard( *myCharacter->botBehavior->BlackboardAsset );
		}

		enemyKeyID = blackboardComp->GetKeyID( "Enemy" );
		needAmmoKeyID = blackboardComp->GetKeyID( "NeedAmmo" );

		behaviorComp->StartTree( *( myCharacter->botBehavior ) );
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf(TEXT("have behavior")) );
	}
   else
      {
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf(TEXT("doesn;t have behavior")) );
      }
   ADemoPlayerState* myCharacterState = Cast<ADemoPlayerState>( PlayerState );
   if( myCharacterState )
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf(TEXT("team num %d"), myCharacterState->GetTeamNum()) );
   else
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf(TEXT("Fail")) );

}

void ADemoAIController::SetEnemy( APawn* inPawn )
{
	if ( blackboardComp )
	   {
		blackboardComp->SetValue<UBlackboardKeyType_Object>( enemyKeyID, inPawn );
		SetFocus( inPawn );
	   }
   else
      GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf(TEXT("doesn;t have Blackborad")) );
}

bool ADemoAIController::FindClosestEnemyWithLOS( ABasicCharacter* excludeEnemy )
{
	bool bGotEnemy = false;
	APawn* myPawn = GetPawn();
	if( !myPawn )
	   {
		return bGotEnemy;
	   }
	const FVector myLoc = myPawn->GetActorLocation();
	float bestDistSq = MAX_FLT;
	ABasicCharacter* bestTargetPawn = NULL;

	for ( FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it )
		{
		ABasicCharacter* testPawn = Cast<ABasicCharacter>( *it );
		if ( testPawn && testPawn != excludeEnemy && testPawn->IsAlive() && testPawn->IsEnemyFor( this ) )
			{
			if ( HasWeaponLOSToEnemy( testPawn, true ) == true )
				{
				const float DistSq = ( testPawn->GetActorLocation() - myLoc ).SizeSquared();
				if (DistSq < bestDistSq)
					{
					bestDistSq = DistSq;
					bestTargetPawn = testPawn;
					}
				}
			}
		}
   SetEnemy( bestTargetPawn );
	if ( bestTargetPawn )
		{
		//SetEnemy( bestTargetPawn );
		bGotEnemy = true;
		}
   else
      {
      bGotEnemy = false;
      }
	return bGotEnemy;
}

bool ADemoAIController::HasWeaponLOSToEnemy( AActor* enemyActor, const bool bAnyEnemy ) const
{
	static FName LosTag = FName( TEXT( "AIWeaponLosTrace" ) );
	
	AMilitaryCharacter* myCharacter = Cast<AMilitaryCharacter>( GetPawn() );

	bool bHasLOS = false;
	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams( LosTag, true, GetPawn() );
	TraceParams.bTraceAsyncScene = true;

	TraceParams.bReturnPhysicalMaterial = true;	
	FVector StartLocation = myCharacter->GetActorLocation();	
	StartLocation.Z += GetPawn()->BaseEyeHeight; //look from eyes
	
	FHitResult Hit( ForceInit );
	const FVector EndLocation = enemyActor->GetActorLocation();
	GetWorld()->LineTraceSingleByChannel( Hit, StartLocation, EndLocation, COLLISION_WEAPON, TraceParams );
	if ( Hit.bBlockingHit == true )
	   {
		// Theres a blocking hit - check if its tested enemy actor
		AActor* hitActor = Hit.GetActor();
		if ( Hit.GetActor() )
		   {
			if ( hitActor == enemyActor )
			   {
				bHasLOS = true;
			   }
			else if (bAnyEnemy == true)
			   {
				// Its not our actor, maybe its still an enemy ?
				ABasicCharacter* hitCharater = Cast<ABasicCharacter>( hitActor );
				if ( hitCharater )
				   {
               if( myCharacter->IsEnemyFor( hitCharater ) )
                  {
                  bHasLOS = true;
                  }
               /*
					AShooterPlayerState* HitPlayerState = Cast<AShooterPlayerState>( hitCharater->PlayerState );
					AShooterPlayerState* MyPlayerState = Cast<AShooterPlayerState>( PlayerState );
					if ( HitPlayerState && MyPlayerState )
					   {
						if (HitPlayerState->GetTeamNum() != MyPlayerState->GetTeamNum())
						   {
							bHasLOS = true;
						   }
					   }
                */
				   }
			   }
		   }  
	   }

	

	return bHasLOS;
}