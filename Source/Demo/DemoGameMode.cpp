// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoGameMode.h"
#include "GameInfo/DemoPlayerState.h"
#include "BasicCharacter.h"

ADemoGameMode::ADemoGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

float ADemoGameMode::ModifyDamage(float damage, AActor* damagedActor, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	float actualDamage = damage;
	ABasicCharacter* damagedPawn = Cast<ABasicCharacter>( damagedActor );
	if( damagedPawn && eventInstigator )
	{
		ADemoPlayerState* damagedPlayerState = Cast< ADemoPlayerState >( damagedPawn->PlayerState );
		ADemoPlayerState* instigatorPlayerState = Cast< ADemoPlayerState >( eventInstigator->PlayerState );

		// disable friendly fire
      if( damagedPlayerState && instigatorPlayerState )
         {
         GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf( TEXT("palyer state null") ) );
         return 0.f;
         }
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
//		killerPlayerState->InformAboutKill( killerPlayerState, damageType, victimPlayerState );
	}

	if ( victimPlayerState )
	{
	//	victimPlayerState->BroadcastDeath( killerPlayerState, damageType, victimPlayerState );
	}
}

bool ADemoGameMode::CanDealDamage( ADemoPlayerState* damageInstigator, ADemoPlayerState* damagedPlayer )
{ 
    //  GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf( TEXT(" %d wants to attack %d"), damageInstigator->GetTeamNum(), damagedPlayer->GetTeamNum() ) );
 GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf( TEXT(" %d wants to attack "), damageInstigator->GetTeamNum() ) );
 return true;
/*
   if( damageInstigator->GetTeamNum() != damagedPlayer->GetTeamNum() )
      {

      return true;
      }
	return false;*/
}


