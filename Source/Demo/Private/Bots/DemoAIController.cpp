// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Bots/AIMilitaryCharacter.h"

ADemoAIController::ADemoAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	blackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = behaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp") );	
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


