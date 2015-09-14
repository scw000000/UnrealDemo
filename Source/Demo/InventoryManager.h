// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ABasicCharacter;
class AWeapon;
/**
 * 
 */

class DEMO_API InventoryManager
{
public:
  // static InventoryManager* GetInstance();
   InventoryManager();

	~InventoryManager();
   
   //virtual void PostInitializeComponents() override;

   void SetAttack( bool isAttackOn );

   void SetControllingCharacter( ABasicCharacter *const character );
   
   bool InitializeEquipWeapon( TSubclassOf<class AWeapon> weapon );

   void FinishEquipWeapon();

   void DestroyEquippedWeapon();

   TSubclassOf<class AWeapon> GetEquippedWeapon();

private:
   void SpawnAndAttachWeapon();
   
   ABasicCharacter* controllingCharacter;
   
   AWeapon* equippedWeapon;

   TSubclassOf<class AWeapon> bpEquippedWeapon;
   TSubclassOf<class AWeapon> bpEquippingWeapon;
};