// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoGameMode.h"
#include "GameInfo/DemoPlayerState.h"
#include "BasicCharacter.h"

ADemoGameMode::ADemoGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

float ADemoGameMode::ModifyDamage( float damage, AActor* damagedActor, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser )
{
	float actualDamage = damage;
	ABasicCharacter* damagedCharacter = Cast<ABasicCharacter>( damagedActor );
   ABasicCharacter* damageCauserCharacter = Cast<ABasicCharacter>( damageCauser );
	if( damagedCharacter && damageCauserCharacter )
	{
		if (!CanDealDamage( damagedCharacter, damageCauserCharacter ) )
		{
			actualDamage = 0.0f;
		}

		// scale self instigated damage
		if ( damagedCharacter == damageCauserCharacter )
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
//		killerPlayerState->InformAboutKill( killerPlayerState, damageType, victimPlayerState );
	}

	if ( victimPlayerState )
	{
	//	victimPlayerState->BroadcastDeath( killerPlayerState, damageType, victimPlayerState );
	}
}

bool ADemoGameMode::CanDealDamage( ABasicCharacter* damagedCharacter, ABasicCharacter* damagedCauser )
{ 	  
   if( damagedCharacter->GetTeamNumber() != damagedCauser->GetTeamNumber() )
      {

      return true;
      }
   if( canFriendlyFire && damagedCharacter->GetTeamNumber() == damagedCauser->GetTeamNumber() && damagedCharacter->GetUniqueID() != damagedCauser->GetUniqueID() )
      {
      return true;
      }
   if( canDamageSelf && damagedCharacter->GetTeamNumber() == damagedCauser->GetTeamNumber() && damagedCharacter->GetUniqueID() == damagedCauser->GetUniqueID() )
      {
      return true;
      }
	return false;
}


