// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "InventoryManager.h"
#include "BasicCharacter.h"
#include "Weapon.h"
#include "RangedWeapon.h"
#include "Projectile.h"

InventoryManager::InventoryManager()
{
   equippedWeapon = NULL;
   bpEquippedWeapon = NULL;
   bpEquippingWeapon = NULL;
}

InventoryManager::~InventoryManager()
{
}

void InventoryManager::EquipWeapon()
{
   if( GetEquippedWeapon() )
      {
      AddBackpackItemByInstance( equippedWeapon );
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

void InventoryManager::ReloadWeapon()
{
   if( CanReload() )
      {
      ARangedWeapon* rangedWeapon = Cast< ARangedWeapon >( equippedWeapon );

      BackpackItem* backpackAmmo = FindItem( rangedWeapon->bpProjectile );

      int32 backpackAmmoNum = backpackAmmo->GetQuantity();

      int32 reloadAmmoNum = rangedWeapon->maxAmmo - rangedWeapon->ammo;

      reloadAmmoNum = FMath::Clamp<int32>( reloadAmmoNum, 0, backpackAmmoNum );

      RemoveBackpackItemByClass( rangedWeapon->bpProjectile, reloadAmmoNum );

      rangedWeapon->Reload( reloadAmmoNum );
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

void InventoryManager::SetEquippingWeapon( TSubclassOf<class AWeapon> weapon )
{
   bpEquippingWeapon = weapon;
}

void InventoryManager::AddBackpackItemByInstance( AItem *const inItemInstance )
{
   BackpackItem *searchItem = backpack.Find( inItemInstance->GetClass() );
   if( inItemInstance ){
      if( searchItem )
         {
         searchItem->SetQuantity( searchItem->GetQuantity() + inItemInstance->GetQuantity() );
    //  backpack[ inItem->GetClass()].SetQuantity( 0 );
    //  searchItem->SetQuantity( searchItem->GetQuantity() + inItem->GetQuantity() );
         }
      else
         {
         backpack.Add( inItemInstance->GetClass(), BackpackItem( inItemInstance->GetIcon( ), inItemInstance->GetName(), inItemInstance->GetQuantity() ) ); 
         }
   }
   
}

void InventoryManager::AddBackpackItemByClass( TSubclassOf<class AItem> inItemClass, int32 itemNum )
{

   BackpackItem *backpackItem = FindItem( inItemClass );
   GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "add by ckass" );
   if( inItemClass && itemNum > 0 ){
      AItem* defaultObject = Cast<AItem>( inItemClass->GetDefaultObject() ); 
      if( backpackItem && defaultObject )
         {
         backpackItem->SetQuantity( backpackItem->GetQuantity() + defaultObject->GetQuantity() * itemNum );
         }
      else
         {
            if( defaultObject )
               {
               backpack.Add( inItemClass, BackpackItem( defaultObject->GetIcon( ), defaultObject->GetName(), defaultObject->GetQuantity() * itemNum ) ); 
               }
         }
   }
}

void InventoryManager::RemoveBackpackItemByClass( TSubclassOf<class AItem> inItemClass, int32 itemNum )
{
   BackpackItem *backpackItem = backpack.Find( inItemClass );
   
   if( inItemClass && itemNum > 0 ){
      AItem* defaultObject = Cast<AItem>( inItemClass->GetDefaultObject() ); 
      if( backpackItem && defaultObject )
         {
         backpackItem->SetQuantity( backpackItem->GetQuantity() - itemNum );
         }
      if( backpackItem->GetQuantity() <= 0 )
         {
         backpack.Remove( inItemClass );
         }
   }
}

bool InventoryManager::CanReload()
{
   ARangedWeapon* rangedWeapon = Cast< ARangedWeapon >( equippedWeapon );
   if( rangedWeapon && rangedWeapon->CanReload() )
      {
      BackpackItem* projectile = FindItem( rangedWeapon->bpProjectile );
         if( projectile && projectile->GetQuantity() > 0 )
            {
            return true;
            }
      }
   return false;
}

AWeapon* InventoryManager::GetEquippedWeapon()
{
   return equippedWeapon;
}

bool InventoryManager::CanEquipWeapon( TSubclassOf<class AWeapon> weapon )
{
   if( weapon && bpEquippedWeapon != weapon )
      {
      return true;
      }
   return false;
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
      FActorSpawnParameters spawnParams = FActorSpawnParameters();
      spawnParams.Owner = controllingCharacter;
      spawnParams.Instigator = controllingCharacter;
      equippedWeapon = ( AWeapon * ) controllingCharacter->GetWorld()->SpawnActor<AWeapon>( bpEquippedWeapon, controllingCharacter->GetActorLocation(), controllingCharacter->GetActorRotation(), spawnParams );
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

