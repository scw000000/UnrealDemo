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

   UFUNCTION( BlueprintCallable, Category = Behavior )
      void FindClosestEnemy();

   virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

   void AddObserverToMap( ABasicCharacter* targetCharacter );

   void DelObserverFromMap( ABasicCharacter* targetCharacter );

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool UpdateEnemyExistInfo();

   virtual void Possess( APawn* inPawn ) override;

   void SetEnemy(class APawn* inPawn);

   static TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & GetObserveMap();

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool FindClosestEnemyWithLOS( ABasicCharacter* excludeEnemy );

   bool HasWeaponLOSToEnemy( AActor* InEnemyActor, const bool bAnyEnemy ) const;

   

protected:
   

   void LOSAllianceBroadcast( APawn* otherPawn );

   void OnReceiveLOSBroadcast( APawn* otherPawn );

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBlackboardComponent* blackboardComp;

	/* Cached BT component */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBehaviorTreeComponent* behaviorComp;


   //FLOSBroadcastDelegate losBroadcastDelegate;

   FTimerHandle onSightTimerHandle;

   FTimerDelegate onSightDelegate;

	int32 enemyKeyID;

	int32 needAmmoKeyID;
	
};
