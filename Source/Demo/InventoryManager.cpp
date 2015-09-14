// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "InventoryManager.h"
#include "Weapon.h"
#include "RangedWeapon.h"
#include "BasicCharacter.h"

InventoryManager::InventoryManager()
{
   equippedWeapon = NULL;
   bpEquippedWeapon = NULL;
   bpEquippingWeapon = NULL;
}

InventoryManager::~InventoryManager()
{
}

void InventoryManager::SetAttack( bool isAttackOn )
{
   ARangedWeapon *const rangedWeapon= Cast<ARangedWeapon>( equippedWeapon );
   if( rangedWeapon )
      {
      rangedWeapon->SetisTriggerOn( isAttackOn );
    //  rangedWeapon->Fire();
      }
}

void InventoryManager::SetControllingCharacter( ABasicCharacter *const character )
{
   controllingCharacter = character;
}

bool InventoryManager::InitializeEquipWeapon( TSubclassOf<class AWeapon> weapon )
{
   bpEquippingWeapon = weapon;
   if( weapon && bpEquippedWeapon != weapon )
      {
      return true;
      }
   return false;
}

void InventoryManager::FinishEquipWeapon()
{
   if( GetEquippedWeapon() )
      {
      DestroyEquippedWeapon();
      }
   SpawnAndAttachWeapon();
}

void InventoryManager::DestroyEquippedWeapon()
{
   if( equippedWeapon && controllingCharacter)
      {
      equippedWeapon->Destroy();
      equippedWeapon = NULL;
      bpEquippedWeapon = NULL;
      }
}

TSubclassOf<class AWeapon> InventoryManager::GetEquippedWeapon()
{
   return bpEquippedWeapon;
}

void InventoryManager::SpawnAndAttachWeapon()
{ 
   if( bpEquippingWeapon && controllingCharacter)
      {
      bpEquippedWeapon = bpEquippingWeapon;
      equippedWeapon = ( AWeapon * ) controllingCharacter->GetWorld()->SpawnActor<AWeapon>( bpEquippedWeapon, controllingCharacter->GetActorLocation(), controllingCharacter->GetActorRotation() );
      if( equippedWeapon )
         {
         const USkeletalMeshSocket *socket = controllingCharacter->GetMesh()->GetSocketByName( "hand_rSocket" );
         socket->AttachActor( equippedWeapon, controllingCharacter->GetMesh() );
         bpEquippingWeapon = NULL;
         }
      else
         {
         GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "spawnfailed" );
         }
      }
}  