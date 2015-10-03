// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DemoAIController.generated.h"

class ABasicCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoAIController : public AAIController
{
	GENERATED_BODY()
public:
   ADemoAIController(const FObjectInitializer& ObjectInitializer);

   UFUNCTION( BlueprintCallable, Category = Behavior )
      void FindClosestEnemy();

   virtual void Possess( APawn* inPawn ) override;

   void SetEnemy(class APawn* inPawn);

   UFUNCTION( BlueprintCallable, Category = Behavior )
      bool FindClosestEnemyWithLOS( ABasicCharacter* excludeEnemy );

   bool HasWeaponLOSToEnemy( AActor* InEnemyActor, const bool bAnyEnemy ) const;

   

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBlackboardComponent* blackboardComp;

	/* Cached BT component */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = AIComp )
	   UBehaviorTreeComponent* behaviorComp;

	int32 enemyKeyID;

	int32 needAmmoKeyID;
	
};
