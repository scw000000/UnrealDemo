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
    //  for( TArray<ABasicCharacter *>::TIterator arrayIT = (*mapIT).Value->CreateIterator(); arrayIT; ++arrayIT )
      //   {
         
        // }
      }
   if( !bGotEnemy )
      {
      SetEnemy( NULL );
      }
}

void ADemoAIController::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
   Super::EndPlay( EndPlayReason );
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
       //  GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "new array added" );
         }
      }
}

void ADemoAIController::DelObserverFromMap( ABasicCharacter* targetCharacter )
{
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > &visionMap = GetObserveMap();
   TArray<ABasicCharacter *> * pawnObserveArray =  visionMap.Find( targetCharacter )? *( visionMap.Find( targetCharacter ) ) : NULL;
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
   //the observer array already exist
   
   if( myAICharacter )
      {
      //if my character is not observer, delete derectly
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

bool ADemoAIController::UpdateEnemyExistInfo()
{
  // ShowObserverMAP( );
   AAIMilitaryCharacter* myAICharacter = Cast<AAIMilitaryCharacter>( GetPawn() );
 //  APawn* bestTargetPawn = NULL;
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > visionMap = GetObserveMap();
   bool bGotEnemy = false;
   for ( FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it )
		{
		ABasicCharacter* testCharacter = Cast<ABasicCharacter>( *it );
      //should be test for enemy
      if( testCharacter && testCharacter->IsAlive()  && testCharacter->IsEnemyFor( this ) )
         {
         //can be seen
         if( myAICharacter->pawnSensingComp->CouldSeePawn( testCharacter ) && myAICharacter->pawnSensingComp->HasLineOfSightTo( testCharacter ) )
            {
            TArray<ABasicCharacter *> * pawnObserveArray = *( visionMap.Find( testCharacter ) );
            //the ovserve array already exist
            AddObserverToMap( testCharacter );
            bGotEnemy = true;
            }
         else
            {
            DelObserverFromMap( testCharacter );
            }
         }
		}
   DecideEnemy();
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
		behaviorComp->StartTree( *( myCharacter->botBehavior ) );
	   }
}

void ADemoAIController::SetEnemy( APawn* inPawn )
{
   blackboardComp->SetValue<UBlackboardKeyType_Object>( enemyKeyID, inPawn );
	SetFocus( inPawn );
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
