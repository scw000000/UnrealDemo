// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "Weapon.h"

AWeapon::AWeapon( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

  // float minCrossHairSize;
 //  float maxCrossHairSize;
   crossHairSize = 0.f;
  // float crossHairSizeDecrRate;
 //  float crossHairSizeIncrRate;
}

//this function is abandoned right now
void AWeapon::Initialize( ABasicCharacter *const character, const FName &socketName )
{
   const USkeletalMeshSocket *socket = character->GetMesh()->GetSocketByName( socketName );
   socket->AttachActor( this, character->GetMesh() );  
}


