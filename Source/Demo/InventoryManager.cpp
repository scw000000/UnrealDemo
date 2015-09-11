// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "InventoryManager.h"
#include "Weapon.h"
#include "RangedWeapon.h"
#include "BasicCharacter.h"

InventoryManager::InventoryManager()
{
   equippedWeapon = NULL;
}

InventoryManager::~InventoryManager()
{
}

void InventoryManager::Fire()
{
   ARangedWeapon *const rangedWeapon= Cast<ARangedWeapon>( equippedWeapon );
   if( rangedWeapon )
      {
      rangedWeapon->Fire();
      }
}

void InventoryManager::SetControllingCharacter( ABasicCharacter *character )
{
   controllingCharacter = character;
}

void InventoryManager::EquipWeapon( UClass* bpWeapon )
{ 
   if( bpWeapon && controllingCharacter)
      {
      equippedWeapon = ( AWeapon * ) controllingCharacter->GetWorld()->SpawnActor<AWeapon>( bpWeapon, controllingCharacter->GetActorLocation(), controllingCharacter->GetActorRotation() );
      if( equippedWeapon )
         {
         const USkeletalMeshSocket *socket = controllingCharacter->GetMesh()->GetSocketByName( "hand_rSocket" );
         socket->AttachActor( equippedWeapon, controllingCharacter->GetMesh() );
         }
      }
}  