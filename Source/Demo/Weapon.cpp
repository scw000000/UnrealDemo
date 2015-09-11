// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "Weapon.h"

void AWeapon::Initialize( ABasicCharacter *const character, const FName &socketName )
{
   const USkeletalMeshSocket *socket = character->GetMesh()->GetSocketByName( socketName );
   socket->AttachActor( this, character->GetMesh() );  
}


