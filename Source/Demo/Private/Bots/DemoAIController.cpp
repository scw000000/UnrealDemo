// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoAIController.h"
#include "DemoGameMode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BasicCharacter.h"
#include "Bots/AIMilitaryCharacter.h"
#include "GameInfo/DemoPlayerState.h"
#include "DemoGame.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > ADemoAIController::observeMap;
float ADemoAIController::searchMeter = 0.f;
float ADemoAIController::traceTimeMeterMax = 5.f;

ADemoAIController::ADemoAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
   PrimaryActorTick.bCanEverTick = true;

 	blackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = behaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp") );	

   traceTimeMeter = 0.f;

}

void ADemoAIController::PostInitializeComponents()
{
  Super::PostInitializeComponents();
  
}

void ADemoAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ADemoAIController::ShowObserverMAP( )
{
    GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "L-------------" );
    for( TMap< ABasicCharacter *, TArray<ABasicCharacter *> * >::TIterator mapIT = observeMap.CreateIterator(); mapIT; ++mapIT )
       {
       
       for( TArray<ABasicCharacter *>::TIterator arrayIT = (*mapIT).Value->CreateIterator(); arrayIT; ++arrayIT )
          {
          FString traversalmessage = (*mapIT).Key->GetName() + TEXT(" is obsvered by ") + (*arrayIT)->GetName();
          GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, traversalmessage );
          }
       }
    GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "^-------------" );
}

void ADemoAIController::StopEngageMode()
{
   DelObserverFromMap( Cast<ABasicCharacter>( GetEnemy() ) );
   SetEnemy( NULL );
}

void ADemoAIController::StartPatrol()
{
  bool canPatrol = patrolPathManager.SetStartPoint( Cast<AAIMilitaryCharacter>( GetPawn() ) );
   SetPatrolMode( canPatrol );
  if( canPatrol )
     {
     GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "Start Patrol" );
     SetDestination( patrolPathManager.GetCurrentDestination() );
     }
}

void ADemoAIController::Tick( float DeltaSeconds )
{
   Super::Tick( DeltaSeconds );
}

void ADemoAIController::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
   Super::EndPlay( EndPlayReason );
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
		enemyKeyID = blackboardComp->GetKeyID( "Enemy" );
		needAmmoKeyID = blackboardComp->GetKeyID( "NeedAmmo" );
      tracingEnemyKeyID = blackboardComp->GetKeyID( "TracingEnemy" );
      searchModeKeyID = blackboardComp->GetKeyID( "SearchMode" );
      patrolModeKeyID = blackboardComp->GetKeyID( "PatrolMode" );
      destinationKeyID = blackboardComp->GetKeyID( "Destination" );
		behaviorComp->StartTree( *( myCharacter->botBehavior ) );
	   }
}

void ADemoAIController::UpdateTraceMeter( float deltaSeconds )
{
   ABasicCharacter* tracingCharacter = Cast<ABasicCharacter>( GetTracingEnemy() );
   ABasicCharacter* enemyCharacter = Cast<ABasicCharacter>( GetEnemy() );
   if( tracingCharacter &&  CanTraceCharacter( tracingCharacter ) )
      {
      traceTimeMeter += deltaSeconds;
      
      }
   else
      {
      if( tracingCharacter )
         {
         }
      traceTimeMeter -= deltaSeconds;
      
      }
   if( traceTimeMeter >= traceTimeMeterMax )
      {
      traceTimeMeter = traceTimeMeterMax;
      StartEngageEnemy( tracingCharacter );
      }
   if( traceTimeMeter <= 0.f )
      {
      traceTimeMeter = 0.f;
      
      SetTracingEnemy( NULL );
        if( !IsAllianceSeeing( enemyCharacter ) && GetEnemy() )
           {
           GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "Stop Engage" );
           //SetEnemy( NULL );
          // SetSearchMeter( 6.f );
           StopEngageMode();
           //DelObserverFromMap( Cast<ABasicCharacter>( GetEnemy() ) );
           }
      }
}

void ADemoAIController::SetEnemy( APawn* inPawn )
{
   blackboardComp->SetValue<UBlackboardKeyType_Object>( enemyKeyID, inPawn );
	SetFocus( inPawn );
}

void ADemoAIController::SetTracingEnemy( class APawn* inPawn )
{
   APawn* tracingPawn = GetTracingEnemy();
   if( tracingPawn != inPawn )
      {
      blackboardComp->SetValue<UBlackboardKeyType_Object>( tracingEnemyKeyID, inPawn );
      }
}

void ADemoAIController::SetSearchMeter( float inMeterValue )
{
   searchMeter = inMeterValue;
}

void ADemoAIController::SetSearchMode( bool isON )
{
   if( GetSearchMode() != isON )
      {
      blackboardComp->SetValue<UBlackboardKeyType_Bool>( searchModeKeyID, isON );
      }
}

void ADemoAIController::SetPatrolMode( bool isON )
{
   blackboardComp->SetValue<UBlackboardKeyType_Bool>( patrolModeKeyID, isON );
}

void ADemoAIController::SetDestination( FVector inDestination )
{ 
   blackboardComp->SetValue<UBlackboardKeyType_Vector>( destinationKeyID, inDestination );
}

bool ADemoAIController::UpdateEnemyExistInfo()
{

   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
  // TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > visionMap = observeMap;
   bool bGotEnemy = false;
   for ( FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it )
		{
		ABasicCharacter* testCharacter = Cast<ABasicCharacter>( *it );
      if( CanTraceCharacter( testCharacter ) )
         {
         OnSightOnEnemy( testCharacter );
         bGotEnemy = true;
         }
      else
         {
         OnLostSigntOnEnemy( testCharacter );
         }
		}
   if( !bGotEnemy )
      {
     // DecideEnemy();
      }
   return bGotEnemy;
}

void ADemoAIController::StartSearch()
{
   ADemoGameMode* myGameMode = Cast<ADemoGameMode>( GetWorld()->GetAuthGameMode() );
   if( myGameMode )
      {
      myGameMode->StartSearchMode();
      }
}

void ADemoAIController::SetNextPatrolPoint()
{
   if( GetPatrolMode() )
      {
      patrolPathManager.SetToNextDestination();
      SetDestination( patrolPathManager.GetCurrentDestination() );
      }
}

APawn* ADemoAIController::GetEnemy()
{
   return Cast<APawn>( blackboardComp->GetValueAsObject( FName( TEXT("Enemy") ) ) );
}

APawn* ADemoAIController::GetTracingEnemy()
{
   return Cast<APawn>( blackboardComp->GetValueAsObject( FName( TEXT("TracingEnemy") ) ) );
}

TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & ADemoAIController::GetObserveMap()
{
   return observeMap;
}

float ADemoAIController::GetSearchMeter()
{
  return searchMeter;
}

bool ADemoAIController::GetSearchMode()
{
   return blackboardComp->GetValueAsBool( FName( TEXT("SearchMode") ) );
}

bool ADemoAIController::GetPatrolMode()
{
   return blackboardComp->GetValueAsBool( FName( TEXT("PatrolMode") ) );
}

//decrepated now
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
   
	if ( bestTargetPawn )
		{
      
      
      LOSAllianceBroadcast( bestTargetPawn );
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
				   }
			   }
		   }  
	   }
	return bHasLOS;
}

//decrepated now
void ADemoAIController::DecideEnemy()
{
  // TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > &visionMap = GetObserveMap();
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   bool bGotEnemy = false;
   for( TMap< ABasicCharacter *, TArray<ABasicCharacter *> * >::TIterator mapIT = observeMap.CreateIterator(); mapIT; ++mapIT )
      {
      if( (*mapIT).Value->Num() > 0 )
         { 
         SetEnemy( (*mapIT).Key );
         bGotEnemy = true;
         }
      }
}

void ADemoAIController::OnSightOnEnemy( ABasicCharacter* targetCharacter )
{
   if( GetEnemy() )
      {
      AddObserverToMap( targetCharacter );
      SetTracingEnemy( NULL );
      traceTimeMeter = traceTimeMeterMax;
      }
   else
      {
      if( GetTracingEnemy() )
         {

         }
      else
         {
         SetTracingEnemy( targetCharacter );
         }
      }
}

void ADemoAIController::OnLostSigntOnEnemy( ABasicCharacter* targetCharacter )
{
   if( GetEnemy() && IsAllianceSeeing( targetCharacter ) )
      {
      DelObserverFromMap( targetCharacter );
      SetTracingEnemy( NULL );
      }
   else
      {
      if( GetTracingEnemy() )
         {

         }
      else
         {
         }
      }
}

void ADemoAIController::StartEngageEnemy( ABasicCharacter* otherCharacter )
{
   SetEnemy( otherCharacter );
   AddObserverToMap( otherCharacter );
   LOSAllianceBroadcast( otherCharacter );
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
            AllianceController->OnReceiveLOSBroadcast( otherPawn );
            }
			}
		}
}

void ADemoAIController::OnReceiveLOSBroadcast( APawn* otherPawn )
{
    FString message = TEXT("!!!!!!!!!!!!I know !Saw Actor ") + otherPawn->GetName();
    SetEnemy( otherPawn );
}

void ADemoAIController::AddObserverToMap( ABasicCharacter* targetCharacter )
{
   //TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > &visionMap = observeMap;
   TArray<ABasicCharacter *> * pawnObserveArray =  observeMap.Find( targetCharacter )? *( observeMap.Find( targetCharacter ) ) : NULL;
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   
   //the ovserve array already exist
   if( myAICharacter )
      {
      if( pawnObserveArray )
         {
         pawnObserveArray->AddUnique( myAICharacter );
         }
      else
         {
         observeMap.Add( targetCharacter, new TArray< ABasicCharacter *> );
         ( *( observeMap.Find( targetCharacter ) ) )->AddUnique( myAICharacter );
         }
      }
}

void ADemoAIController::DelObserverFromMap( ABasicCharacter* targetCharacter )
{
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > &visionMap = observeMap;
   TArray<ABasicCharacter *> * pawnObserveArray =  visionMap.Find( targetCharacter )? *( visionMap.Find( targetCharacter ) ) : NULL;
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   
   if( myAICharacter )
      {
      //if my character is not observer, delete directly
      if( pawnObserveArray )
         {
            if( pawnObserveArray->Num() > 1 )
            {
            pawnObserveArray->Remove( myAICharacter );
            }
            else if( pawnObserveArray->Find( myAICharacter ) != INDEX_NONE )
            {
            pawnObserveArray->Remove( myAICharacter );
            GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, myAICharacter->GetName() + ": im The Last One!!!!" );
            }
         }
      }
}

bool ADemoAIController::IsAllianceSeeing( ABasicCharacter* tracingCharacter )
{
   TArray<ABasicCharacter *> * observerArray =  observeMap.Find( tracingCharacter )? *( observeMap.Find( tracingCharacter ) ) : NULL;
   ABasicCharacter* myAICharacter = Cast<ABasicCharacter>( GetPawn() );
   if( observerArray )
      {
      for( TArray<ABasicCharacter *>::TIterator arrayIT = observerArray->CreateIterator(); arrayIT; ++arrayIT )
         {
         if( (*arrayIT) != myAICharacter )
            {
            return true;
            }
         }
      }
   return false;
}

bool ADemoAIController::CanTraceCharacter( ABasicCharacter* otherCharacter )
{
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
  return  ( myAICharacter 
   && otherCharacter 
   && otherCharacter->IsAlive()  
   && otherCharacter->IsEnemyFor( this ) 
   && myAICharacter->pawnSensingComp->CouldSeePawn( otherCharacter ) 
   && myAICharacter->pawnSensingComp->HasLineOfSightTo( otherCharacter ) );
}
