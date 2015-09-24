// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoPlayerController.h"
#include "GameInfo/DemoPlayerState.h"

ADemoPlayerState::ADemoPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	teamNumber = 0;
}

void ADemoPlayerState::Reset()
{

}

void ADemoPlayerState::SetTeamNum( int32 inTeamNumber )
{
	teamNumber = inTeamNumber;
}

int32 ADemoPlayerState::GetTeamNum() const
{
	return teamNumber;
}

void ADemoPlayerState::InformAboutKill( class ADemoPlayerState* killerPlayerState, const UDamageType* killerDamageType, class ADemoPlayerState* killedPlayerState )
{
   for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{		
			ADemoPlayerController* testPC = Cast<ADemoPlayerController>(*It);
			if ( testPC )
			{
				// a local player might not have an ID if it was created with CreateDebugPlayer.
				ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>( testPC->Player );
				TSharedPtr<FUniqueNetId> LocalID = LocalPlayer->GetCachedUniqueNetId();
				if (LocalID.IsValid() &&  *LocalPlayer->GetCachedUniqueNetId() == *killerPlayerState->UniqueId)
				{			
			//		testPC->OnKill();
				}
			}
		}
}

void ADemoPlayerState::CopyProperties( APlayerState* playerState )
{	
	Super::CopyProperties( playerState );

	ADemoPlayerState* dempPlayer = Cast<ADemoPlayerState>( playerState );
	if( dempPlayer )
	{
		dempPlayer->teamNumber = teamNumber;
	}	
}
