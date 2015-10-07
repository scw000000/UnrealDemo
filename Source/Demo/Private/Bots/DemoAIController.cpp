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
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"



ADemoAIController::ADemoAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	blackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = behaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp") );	
}

void ADemoAIController::PostInitializeComponents()
{
  Super::PostInitializeComponents();
  
}

void ADemoAIController::BeginPlay()
{
  Super::BeginPlay();
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
		if ( myCharacter->botBehavior->BlackboardAsset )
		   {
			blackboardComp->InitializeBlackboard( *myCharacter->botBehavior->BlackboardAsset );
		   }

		enemyKeyID = blackboardComp->GetKeyID( "VisualEnemy" );
		needAmmoKeyID = blackboardComp->GetKeyID( "NeedAmmo" );

		behaviorComp->StartTree( *( myCharacter->botBehavior ) );
	   }
}

void ADemoAIController::SetEnemy( APawn* inPawn )
{

   blackboardComp->SetValue<UBlackboardKeyType_Object>( enemyKeyID, inPawn );
	SetFocus( inPawn );
}

bool ADemoAIController::FindClosestEnemyWithLOS( ABasicCharacter* excludeEnemy )
{
   static APawn* lastSetPawn = NULL;
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   const FVector myLoc = myAICharacter->GetActorLocation();
   float bestDistSq = MAX_FLT;
   APawn* bestTargetPawn = NULL;
   for ( FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it )
		{
		ABasicCharacter* testPawn = Cast<ABasicCharacter>( *it );
		if ( testPawn 
           && testPawn != excludeEnemy 
           && testPawn->IsAlive() 
           && testPawn->IsEnemyFor( this ) 
           &&  myAICharacter->pawnSensingComp->CouldSeePawn( testPawn ) 
           &&  myAICharacter->pawnSensingComp->HasLineOfSightTo( testPawn )
           ) 
			{
         if( GetObserveMap().Find( testPawn ) )
            {
            ( *( GetObserveMap().Find( testPawn ) ) )->AddUnique( myAICharacter );
            }
         else
            {
            GetObserveMap().Add( testPawn, new TArray< ABasicCharacter *> );
            ( *( GetObserveMap().Find( testPawn ) ) )->AddUnique( myAICharacter );
            }
			const float DistSq = ( testPawn->GetActorLocation() - myLoc ).SizeSquared();
			if ( DistSq < bestDistSq )
			   {
				bestDistSq = DistSq;
				bestTargetPawn = testPawn;
				}
			}
		}
   SetEnemy( bestTargetPawn );
   bool bGotEnemy = false;
   
 //  onSightDelegate = FTimerDelegate::CreateUObject( this, &ADemoAIController::SetEnemy, bestTargetPawn );
	if ( bestTargetPawn )
		{
      
      
      LOSAllianceBroadcast( bestTargetPawn );
     // GetLOSBroadcastDelegate().Broadcast( bestTargetPawn );
      /*
         if( !GetWorld()->GetTimerManager().IsTimerActive( onSightTimerHandle ) )
            {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ADDDDDDDDDD");
            lastSetPawn = bestTargetPawn;
            }
         else
            {
             GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "NOOOOOOOOOOOO");
            }*/
		bGotEnemy = true;
		}
   else
      {
         if( !GetWorld()->GetTimerManager().IsTimerActive( onSightTimerHandle ) )
            {
            GetWorld()->GetTimerManager().SetTimer( onSightTimerHandle, onSightDelegate, 1.f, false );
            lastSetPawn = bestTargetPawn;
            
            }
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
				   }
			   }
		   }  
	   }

	

	return bHasLOS;
}

void ADemoAIController::LOSAllianceBroadcast( APawn* otherPawn )
{
   static APawn* lastSetPawn = NULL;
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   for ( FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it )
		{
		AAIMilitaryCharacter* testPawn = Cast<AAIMilitaryCharacter>( *it );
		if ( testPawn && testPawn->IsAlive() && !testPawn->IsEnemyFor( this ) ) 
			{
         ADemoAIController* AllianceController = Cast<ADemoAIController>( testPawn->Controller );
         if( AllianceController )
            {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "calling");
            AllianceController->OnReceiveLOSBroadcast( otherPawn );
            }
			}
		}
}

void ADemoAIController::OnReceiveLOSBroadcast( APawn* otherPawn )
{
    // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "revecing");
   // FString message = TEXT("!!!!!!!!!!!!I know !Saw Actor ") + otherPawn->GetName();

   // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
    SetEnemy( otherPawn );
    GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "-------------" );
    for( TMap< ABasicCharacter *, TArray<ABasicCharacter *> * >::TIterator mapIT = GetObserveMap().CreateIterator(); mapIT; ++mapIT )
       {
       
       for( TArray<ABasicCharacter *>::TIterator arrayIT = (*mapIT).Value->CreateIterator(); arrayIT; ++arrayIT )
          {
          FString traversalmessage = (*mapIT).Key->GetName() + TEXT(" is obsvered by ") + (*arrayIT)->GetName();
          GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, traversalmessage );
          }
       }
    GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "-------------" );
}

TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & ADemoAIController::GetObserveMap()
{
    static TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > observeMap;
    return observeMap;
}
