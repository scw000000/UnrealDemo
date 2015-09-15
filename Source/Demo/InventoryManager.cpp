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

void InventoryManager::FinishEquipWeapon()
{
   if( GetEquippedWeapon() )
      {
      AddItem( equippedWeapon );
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

void InventoryManager::ShowBackpack()
{
  for( TMap< TSubclassOf<class AItem>, BackpackItem >::TIterator it = backpack.CreateIterator(); it; ++it )
     {
     GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, it->Key->GetName() );
     GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, FString::Printf( TEXT(" x %d "), it->Value.GetQuantity() ) );
     }
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

void InventoryManager::AddItem( AItem *const inItem )
{
   BackpackItem *searchItem = backpack.Find( inItem->GetClass() );
   if( inItem ){
      if( searchItem )
         {
         searchItem->SetQuantity( searchItem->GetQuantity() + inItem->GetQuantity() );
    //  backpack[ inItem->GetClass()].SetQuantity( 0 );
    //  searchItem->SetQuantity( searchItem->GetQuantity() + inItem->GetQuantity() );
         }
      else
         {
         backpack.Add( inItem->GetClass(), BackpackItem( inItem->GetIcon( ), inItem->GetName(), inItem->GetQuantity() ) ); 
         }
   }
   
}
/*
void InventoryManager::AddItem( TSubclassOf<class AItem> inItem, int32 quantity )
{
   BackpackItem *searchItem = backpack.Find( inItem );
   if( inItem ){
      if( searchItem )
         {
         searchItem->SetQuantity( searchItem->GetQuantity() + quantity );
         }
      else
         {
       //  backpack.Add( inItem->GetClass(), BackpackItem( inItem->GetIcon( ), inItem->GetName(), inItem->GetQuantity() ) ); 
         }
   }
   
}*/

TSubclassOf<class AWeapon> InventoryManager::GetEquippedWeapon()
{
   return bpEquippedWeapon;
}

BackpackItem * InventoryManager::FindItem( TSubclassOf<class AItem> searchItem )
{
   return backpack.Find( searchItem );
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

