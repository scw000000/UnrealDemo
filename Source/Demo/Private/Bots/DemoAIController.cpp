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
   
	AAIMilitaryCharacter* bot = Cast<AAIMilitaryCharacter>( inPawn );

	// start behavior
	if ( bot && bot->botBehavior)
	{
		if ( bot->botBehavior->BlackboardAsset)
		{
			blackboardComp->InitializeBlackboard( *bot->botBehavior->BlackboardAsset );
		}

		enemyKeyID = blackboardComp->GetKeyID( "Enemy" );
		needAmmoKeyID = blackboardComp->GetKeyID( "NeedAmmo" );

		behaviorComp->StartTree( *( bot->botBehavior ) );
	}
}

void ADemoAIController::SetEnemy( APawn* inPawn )
{
	if ( blackboardComp )
	   {
		blackboardComp->SetValue<UBlackboardKeyType_Object>( enemyKeyID, inPawn );
		SetFocus( inPawn );
	   }
}



