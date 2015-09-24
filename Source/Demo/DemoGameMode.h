// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "DemoGameMode.generated.h"
class ADemoPlayerState;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	/** prevents friendly fire */
	virtual float ModifyDamage( float damage, AActor* damagedActor, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser ) const;

	/** notify about kills */
	virtual void Killed( AController* killer, AController* killedPlayer, APawn* killedPawn, const UDamageType* damageType );

	///** can players damage each other? */
	virtual bool CanDealDamage( ADemoPlayerState* damageInstigator, ADemoPlayerState* damagedPlayer ) const;

	/** hides the onscreen hud and restarts the map */
//	virtual void RestartGame() override;

	/** Creates AIControllers for all bots */
	void CreateBotControllers();

protected:
//	UPROPERTY()
//	TArray<AShooterAIController*> BotControllers;
   UPROPERTY(config)
	   float damageSelfScale;

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
