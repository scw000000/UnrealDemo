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

   UFUNCTION( BlueprintCallable, Category = Behavior )
      void FindClosestEnemy();

   virtual void Possess( APawn* inPawn ) override;

   void SetEnemy(class APawn* inPawn);

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool FindClosestEnemyWithLOS( ABasicCharacter* excludeEnemy );

   bool HasWeaponLOSToEnemy( AActor* InEnemyActor, const bool bAnyEnemy ) const;

   

protected:
   TMap< ABasicCharacter *, TArray<ABasicCharacter *> * > & GetObserveMap();

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
