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
  
   void StopEngageMode();

   virtual void Tick( float DeltaSeconds ) override;

   virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

   virtual void Possess( APawn* inPawn ) override;

   void UpdateTraceMeter( float deltaSeconds );

   void SetEnemy( APawn* inPawn);

   void SetTracingEnemy( class APawn* inPawn );

   static void SetSearchMeter( float inMeterValue );

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool UpdateEnemyExistInfo();

   APawn* GetTracingEnemy();

   APawn* GetEnemy();

   static TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & GetObserveMap();

   static float GetSearchMeterVal();

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

   static float& GetTraceMeterRef();

   static float GetTraceMeterMax();

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBlackboardComponent* blackboardComp;

	/* Cached BT component */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBehaviorTreeComponent* behaviorComp;

   FTimerHandle onTraceTimerHandle;

   FTimerDelegate onTraceDelegate;

	int32 enemyKeyID;

	int32 needAmmoKeyID;

   int32 tracingEnemyKeyID;

   float traceTimeMeterMax;

   float traceTimeMeter;
};
