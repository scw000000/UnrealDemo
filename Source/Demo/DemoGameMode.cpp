// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoGameMode.h"
#include "GameInfo/DemoPlayerState.h"
#include "BasicCharacter.h"
#include "Bots/DemoAIController.h"

ADemoGameMode::ADemoGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ADemoGameMode::BeginPlay()
{
   ADemoAIController::GetObserveMap().Reset();
   ADemoAIController::SetSearchMeter( 0.f );
}

void ADemoGameMode::Tick( float DeltaSeconds )
{
   UpdateSearchMeter( DeltaSeconds );
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

void ADemoGameMode::UpdateSearchMeter( float deltaSeconds )
{
   static float prevAISearchMeterVal = 0.f;
   static float curAISearchMeterVal = 0.f;
   curAISearchMeterVal = ADemoAIController::GetSearchMeterVal();
   if( curAISearchMeterVal > 0.f )
      {
      float newAISearchMeterVal = curAISearchMeterVal - deltaSeconds;
      ADemoAIController::SetSearchMeter( newAISearchMeterVal );
     // GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, FString::Printf( TEXT("%f"), newAISearchMeterVal ) );
      //on search End
      if( newAISearchMeterVal <= 0.f )
         {
         GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "Stop Search" );
         }
      }
   if( prevAISearchMeterVal <= 0.f && curAISearchMeterVal > 0.f )
      {
      GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, "Start Search" );
      }
   prevAISearchMeterVal = ADemoAIController::GetSearchMeterVal();
}


