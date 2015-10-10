// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "DemoGameMode.generated.h"
class ADemoPlayerState;
class ABasicCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

   virtual void BeginPlay() override;

   virtual void Tick( float DeltaSeconds ) override;

	/** prevents friendly fire */
	float ModifyDamage( float damage, AActor* damagedActor, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser );

	/** notify about kills */
	virtual void Killed( AController* killer, AController* killedPlayer, APawn* killedPawn, const UDamageType* damageType );

	///** can players damage each other? */
	bool CanDealDamage( ABasicCharacter* damagedCharacter, ABasicCharacter* damagedCauser );

	/** hides the onscreen hud and restarts the map */
//	virtual void RestartGame() override;

	/** Creates AIControllers for all bots */
	//void CreateBotControllers();
//UPROPERTY(config)
   
protected:
   void UpdateSearchMeter( float deltaSeconds );

   void BroadCastSearchMode( bool isOn );

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Damage )
	   float damageSelfScale;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Damage )
	   bool canDamageSelf;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Damage )
	   bool canFriendlyFire;

//	/** initialization for bot after creation */
//	virtual void InitBot(AShooterAIController* AIC, int32 BotNum);

public:	

	/** finish current match and lock players */
//	UFUNCTION(exec)
//	   void FinishMatch();

	/*Finishes the match and bumps everyone to main menu.*/
	/*Only GameInstance should call this function */
//	void RequestFinishAndExitToMainMenu();

//	UPROPERTY()
//	TArray<AShooterPickup*> LevelPickups;
	
};
