// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicCharacter.h"
#include "NPCCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ANPCCharacter : public ABasicCharacter
{
	GENERATED_BODY()
	
	
   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      float Speed;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      float HitPoints;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      float BaseAttackDamage;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      float AttackTimeout;

   // UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
   //    float TimeSinceLastStrike;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      int32 Experience;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = EnemyProperties )
      UClass* BPLoot;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Collision )
      USphereComponent* SightSphere;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Collision )
      USphereComponent* AttackRangeSphere; */
	
};
