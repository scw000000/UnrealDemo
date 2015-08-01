// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BasicCharacter.h"
#include "BasicAIController.generated.h"
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FBindableEvent_AttackAnimation );

UCLASS()
class DEMO_API ABasicAIController : public AAIController
{
GENERATED_BODY()
/*
	
public:
   virtual void BeginPlay( ) override;
	
   ABasicAIController( const FObjectInitializer& ObjectInitializer );

   void Tick( float DeltaTime ) override;
	
  // float getDistanceToCharacter( ABasicChracter* target );

   bool isInSightRange( ABasicCharacter* targetCharacter );

   bool isInAttackRange( ABasicCharacter* targetCharacter );

   UFUNCTION( BlueprintCallable, Category = EnemyAI )
      void AttackDetectionStart( );

   UFUNCTION( BlueprintCallable, Category = EnemyAI )
      void AttackDetectionEnd( );

   UFUNCTION( BlueprintCallable, Category = EnemyAI )
      void CleanAttackTimer( );

   void Attack( );

   UPROPERTY( BlueprintAssignable, Category = "Animation Delegate" )
      FBindableEvent_AttackAnimation AttackAnimationStart;

   UPROPERTY( BlueprintAssignable, Category = "Animation Delegate" )
      FBindableEvent_AttackAnimation AttackAnimationEnd;

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
      USphereComponent* AttackRangeSphere;*/
};
