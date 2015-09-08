// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "InventoryManager.h"
#include "Weapon.h"
#include "BasicCharacter.h"

InventoryManager* InventoryManager::instance;

InventoryManager::InventoryManager()
{
}

InventoryManager::~InventoryManager()
{
}

void InventoryManager::EquipWeapon( UClass* bpWeapon )
{
   if( bpWeapon )
      {
      AWeapon *weapon = ( AWeapon * ) controllingCharacter->GetWorld()->SpawnActor<AWeapon>( bpWeapon, FVector::ZeroVector, FRotator::ZeroRotator );
    //  MeleeWeapon = NULL;
      if( weapon )
         {
         const USkeletalMeshSocket *socket = controllingCharacter->GetMesh()->GetSocketByName( "RightHandSocket" );
         socket->AttachActor( weapon, controllingCharacter->GetMesh() );
         }
      }
}  