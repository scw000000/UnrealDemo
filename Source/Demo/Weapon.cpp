// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "Weapon.h"

AWeapon::AWeapon( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

   minCrossHairSize = 30.f;
   maxCrossHairSize = 100.f;
   crossHairSize = 3.f;
   crossHairSizeDecrSpeed = 70.f;
   crossHairSizeIncrSpeed = 30.f;
}

//this function is abandoned right now
void AWeapon::Initialize( ABasicCharacter *const character, const FName &socketName )
{
   const USkeletalMeshSocket *socket = character->GetMesh()->GetSocketByName( socketName );
   socket->AttachActor( this, character->GetMesh() );  
}


