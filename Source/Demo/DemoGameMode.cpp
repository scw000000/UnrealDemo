// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoGameMode.h"
#include "GameInfo/DemoPlayerState.h"
#include "BasicCharacter.h"

ADemoGameMode::ADemoGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

float ADemoGameMode::ModifyDamage(float damage, AActor* damagedActor, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser) const
{
	float actualDamage = damage;
	ABasicCharacter* damagedPawn = Cast<ABasicCharacter>( damagedActor );
	if( damagedPawn && eventInstigator )
	{
		ADemoPlayerState* damagedPlayerState = Cast< ADemoPlayerState >( damagedPawn->PlayerState );
		ADemoPlayerState* instigatorPlayerState = Cast< ADemoPlayerState >( eventInstigator->PlayerState );

		// disable friendly fire
		if (!CanDealDamage( instigatorPlayerState, damagedPlayerState ) )
		{
			actualDamage = 0.0f;
		}

		// scale self instigated damage
		if ( instigatorPlayerState == damagedPlayerState )
		{
			actualDamage *= damageSelfScale;
		}
	}

	return actualDamage;
}

void ADemoGameMode::Killed(AController* killer, AController* killedPlayer, APawn* killedPawn, const UDamageType* damageType)
{
	ADemoPlayerState* killerPlayerState = killer ? Cast<ADemoPlayerState>( killer->PlayerState ) : NULL;
	ADemoPlayerState* victimPlayerState = killedPlayer ? Cast<ADemoPlayerState>( killedPlayer->PlayerState ) : NULL;

	if( killerPlayerState && killerPlayerState != victimPlayerState )
	{
		killerPlayerState->InformAboutKill( killerPlayerState, damageType, victimPlayerState );
	}

	if ( victimPlayerState )
	{
	//	victimPlayerState->BroadcastDeath( killerPlayerState, damageType, victimPlayerState );
	}
}

bool ADemoGameMode::CanDealDamage(class ADemoPlayerState* damageInstigator, class ADemoPlayerState* damagedPlayer) const
{
	return true;
}


