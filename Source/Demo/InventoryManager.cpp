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

void InventoryManager::Fire( bool trigger )
{
   ARangedWeapon *const rangedWeapon= Cast<ARangedWeapon>( equippedWeapon );
   if( rangedWeapon )
      {
      rangedWeapon->SetisTriggerOn( trigger );
    //  rangedWeapon->Fire();
      }
}

void InventoryManager::SetControllingCharacter( ABasicCharacter *const character )
{
   controllingCharacter = character;
}

void InventoryManager::EquipWeapon( TSubclassOf<class AWeapon> weapon )
{ 
   if( weapon && controllingCharacter)
      {
      equippedWeapon = ( AWeapon * ) controllingCharacter->GetWorld()->SpawnActor<AWeapon>( weapon, controllingCharacter->GetActorLocation(), controllingCharacter->GetActorRotation() );
      if( equippedWeapon )
         {
         const USkeletalMeshSocket *socket = controllingCharacter->GetMesh()->GetSocketByName( "hand_rSocket" );
         socket->AttachActor( equippedWeapon, controllingCharacter->GetMesh() );
         }
      }
}  