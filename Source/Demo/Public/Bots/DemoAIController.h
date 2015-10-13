// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "PatrolPathManager.h"
#include "DemoAIController.generated.h"

class ABasicCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLOSBroadcastDelegate, APawn*, Pawn );
/**
 * 
 */
UCLASS()
class DEMO_API ADemoAIController : public AAIController
{
	GENERATED_BODY()
public:
   ADemoAIController(const FObjectInitializer& ObjectInitializer);

   virtual void PostInitializeComponents() override;

   virtual void BeginPlay() override;

   void ShowObserverMAP( );
  
   void StopEngageMode();
   
   UFUNCTION( BlueprintCallable, Category = Behavior )
      void StartPatrol();

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool UpdateEnemyExistInfo();

   UFUNCTION( BlueprintCallable, Category = Behavior )
      void StartSearch();

   UFUNCTION( BlueprintCallable, Category = Behavior )
      void StopSearch();

   UFUNCTION( BlueprintCallable, Category = Behavior )
      void SetNextPatrolPoint();

   virtual void Tick( float DeltaSeconds ) override;

   virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

   virtual void Possess( APawn* inPawn ) override;

   void UpdateTraceMeter( float deltaSeconds );

   void SetEnemy( APawn* inPawn);

   void SetTracingEnemy( class APawn* inPawn );

   static void SetSearchMeter( float inMeterValue );

   void SetSearchMode( bool isON );

   void SetDestination( FVector inDestination );

   UFUNCTION( BlueprintCallable, Category = Behavior )
      void SetPatrolMode( bool isON );

   APawn* GetTracingEnemy();

   APawn* GetEnemy();

   static TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & GetObserveMap();

   static float GetSearchMeter();

   bool GetSearchMode();

   bool GetPatrolMode();

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool FindClosestEnemyWithLOS( ABasicCharacter* excludeEnemy );

   bool HasWeaponLOSToEnemy( AActor* InEnemyActor, const bool bAnyEnemy ) const;



protected:

   //decrepated now
   void DecideEnemy();

   void OnSightOnEnemy( ABasicCharacter* targetCharacter );

   void OnLostSigntOnEnemy( ABasicCharacter* targetCharacter );

   void StartEngageEnemy( ABasicCharacter* otherCharacter );

   void AddObserverToMap( ABasicCharacter* targetCharacter );

   void DelObserverFromMap( ABasicCharacter* targetCharacter );

   void LOSAllianceBroadcast( APawn* otherPawn );

   void OnReceiveLOSBroadcast( APawn* otherPawn );

   bool IsAllianceSeeing( ABasicCharacter* tracingCharacter );

   bool CanTraceCharacter( ABasicCharacter* otherCharacter );

   static float GetTraceMeterMax();

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBlackboardComponent* blackboardComp;

	/* Cached BT component */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBehaviorTreeComponent* behaviorComp;

   static TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > observeMap;

   FTimerHandle onTraceTimerHandle;

   FTimerDelegate onTraceDelegate;

   PatrolPathManager patrolPathManager;

	int32 enemyKeyID;

	int32 needAmmoKeyID;

   int32 tracingEnemyKeyID;

   int32 searchModeKeyID;

   int32 patrolModeKeyID;

   int32 destinationKeyID;

   static float traceTimeMeterMax;

   float traceTimeMeter;

   static float searchMeter;
};
