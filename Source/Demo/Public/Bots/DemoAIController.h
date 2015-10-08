// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
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

   void DecideEnemy();

   virtual void Tick( float DeltaSeconds ) override;

   virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

   virtual void Possess( APawn* inPawn ) override;

   void UpdateTraceMeter( float deltaSeconds );

   void AddObserverToMap( ABasicCharacter* targetCharacter );

   void DelObserverFromMap( ABasicCharacter* targetCharacter );

   void OnSeeEnemy( ABasicCharacter* targetCharacter );

   void SetEnemy( APawn* inPawn);

   void SetTracingEnemy( class APawn* inPawn );

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool UpdateEnemyExistInfo();

   APawn* GetTracingEnemy();

   APawn* GetEnemy();

   static TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & GetObserveMap();

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool FindClosestEnemyWithLOS( ABasicCharacter* excludeEnemy );

   bool HasWeaponLOSToEnemy( AActor* InEnemyActor, const bool bAnyEnemy ) const;

   bool GetShouldTraceEmemy();

protected:
   void StopEngageMode();

   void StartEngageEnemy( ABasicCharacter* otherCharacter );

   void LOSAllianceBroadcast( APawn* otherPawn );

   void OnReceiveLOSBroadcast( APawn* otherPawn );

   bool IsAllianceSeeing( ABasicCharacter* tracingCharacter );

   bool CanTraceCharacter( ABasicCharacter* otherCharacter );

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBlackboardComponent* blackboardComp;

	/* Cached BT component */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBehaviorTreeComponent* behaviorComp;


   //FLOSBroadcastDelegate losBroadcastDelegate;

   FTimerHandle onTraceTimerHandle;

   FTimerDelegate onTraceDelegate;

	int32 enemyKeyID;

	int32 needAmmoKeyID;
	
   int32 engageModeKeyID;

   int32 tracingEnemyKeyID;

   float traceTimeMeterMax;

   float traceTimeMeter;
};
