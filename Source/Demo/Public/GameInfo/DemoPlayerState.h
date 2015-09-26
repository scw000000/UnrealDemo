// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "DemoPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

	// Begin APlayerState interface
	/** clear scores */
	virtual void Reset() override;

	/**
	 * Set new team and update pawn. Also updates player character team colors.
	 *
	 * @param	inTeamNumber	Team we want to be on.
	 */
	void SetTeamNum( int32 inTeamNumber );

	/** get current team */
	int32 GetTeamNum();

 //  UFUNCTION()
  //    void InformAboutKill( class ADemoPlayerState* killerPlayerState, const UDamageType* killerDamageType, class ADemoPlayerState* killedPlayerState );

	//virtual void CopyProperties( class APlayerState* playerState ) override;

protected:

	/** team number */
	UPROPERTY()
	   int32 teamNumber;
};
