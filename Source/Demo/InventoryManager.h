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
   
   void SetbpEquippingWeapon( TSubclassOf<class AWeapon> weapon );

   void EquipWeapon();

   void DestroyEquippedWeapon();

   AWeapon* GetEquippedWeapon();

private:
   
   ABasicCharacter* controllingCharacter;
   AWeapon* equippedWeapon;
   TSubclassOf<class AWeapon> bpEquippingWeapon;
};