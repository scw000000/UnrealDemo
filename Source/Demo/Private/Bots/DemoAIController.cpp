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
   PrimaryActorTick.bCanEverTick = true;

 	blackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = behaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp") );	

   traceTimeMeterMax = 5.0f;

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
      traceTimeMeter -= deltaSeconds;
      
      }
 // GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, FString::Printf( TEXT("%f"), traceTimeMeter ) );
   if( traceTimeMeter >= traceTimeMeterMax )
      {
      traceTimeMeter = traceTimeMeterMax;
      StartEngageEnemy( tracingCharacter );
      }
   if( traceTimeMeter <= 0.f )
      {
      traceTimeMeter = 0.f;
      SetTracingEnemy( NULL );
        if( !IsAllianceSeeing( enemyCharacter ) )
           {
           GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "Stop Engage" );
           //SetEnemy( NULL );
           StopEngageMode();
           //DelObserverFromMap( Cast<ABasicCharacter>( GetEnemy() ) );
           }
      }
}

void ADemoAIController::ShowObserverMAP( )
{
    GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "L-------------" );
    for( TMap< ABasicCharacter *, TArray<ABasicCharacter *> * >::TIterator mapIT = GetObserveMap().CreateIterator(); mapIT; ++mapIT )
       {
       
       for( TArray<ABasicCharacter *>::TIterator arrayIT = (*mapIT).Value->CreateIterator(); arrayIT; ++arrayIT )
          {
          FString traversalmessage = (*mapIT).Key->GetName() + TEXT(" is obsvered by ") + (*arrayIT)->GetName();
          GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, traversalmessage );
          }
       }
    GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "^-------------" );
}

void ADemoAIController::DecideEnemy()
{
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > &visionMap = GetObserveMap();
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   bool bGotEnemy = false;
   for( TMap< ABasicCharacter *, TArray<ABasicCharacter *> * >::TIterator mapIT = visionMap.CreateIterator(); mapIT; ++mapIT )
      {
      if( (*mapIT).Value->Num() > 0 )
         { 
         SetEnemy( (*mapIT).Key );
         bGotEnemy = true;
         }
      }
}

void ADemoAIController::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
   Super::EndPlay( EndPlayReason );
}

void ADemoAIController::Tick( float DeltaSeconds )
{
   Super::Tick( DeltaSeconds );
}

void ADemoAIController::AddObserverToMap( ABasicCharacter* targetCharacter )
{
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > &visionMap = GetObserveMap();
   TArray<ABasicCharacter *> * pawnObserveArray =  visionMap.Find( targetCharacter )? *( visionMap.Find( targetCharacter ) ) : NULL;
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
         visionMap.Add( targetCharacter, new TArray< ABasicCharacter *> );
         ( *( visionMap.Find( targetCharacter ) ) )->AddUnique( myAICharacter );
         }
      }
}

void ADemoAIController::DelObserverFromMap( ABasicCharacter* targetCharacter )
{
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > &visionMap = GetObserveMap();
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

void ADemoAIController::OnSeeEnemy( ABasicCharacter* targetCharacter )
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

bool ADemoAIController::UpdateEnemyExistInfo()
{

   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > visionMap = GetObserveMap();
   bool bGotEnemy = false;
   for ( FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it )
		{
		ABasicCharacter* testCharacter = Cast<ABasicCharacter>( *it );
      if( CanTraceCharacter( testCharacter ) )
         {
         OnSeeEnemy( testCharacter );
         bGotEnemy = true;
         }
      else
         {
         DelObserverFromMap( testCharacter );
         }
		}
   if( !bGotEnemy )
      {
     // DecideEnemy();
      }
   return bGotEnemy;
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
		behaviorComp->StartTree( *( myCharacter->botBehavior ) );
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

APawn* ADemoAIController::GetTracingEnemy()
{
   return Cast<APawn>( blackboardComp->GetValueAsObject( FName( TEXT("TracingEnemy") ) ) );
}

APawn* ADemoAIController::GetEnemy()
{
   return Cast<APawn>( blackboardComp->GetValueAsObject( FName( TEXT("Enemy") ) ) );
}

TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & ADemoAIController::GetObserveMap()
{
    static TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > observeMap;
    return observeMap;
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

void ADemoAIController::StopEngageMode()
{
   DelObserverFromMap( Cast<ABasicCharacter>( GetEnemy() ) );
   SetEnemy( NULL );
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

bool ADemoAIController::IsAllianceSeeing( ABasicCharacter* tracingCharacter )
{
   TArray<ABasicCharacter *> * observerArray =  GetObserveMap().Find( tracingCharacter )? *( GetObserveMap().Find( tracingCharacter ) ) : NULL;
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