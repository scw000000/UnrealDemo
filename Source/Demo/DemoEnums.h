// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

UENUM( BlueprintType )		
enum class PlayerViews : uint8 
{
   PlayerViews_FirstPerson 	UMETA( DisplayName = "FirstPerson" ),
   PlayerViews_Aim        	UMETA( DisplayName = "Aim" ),
   PlayerViews_ThirdPerson 	UMETA( DisplayName = "ThirdPerson" )
};

UENUM( BlueprintType )		
enum class BodyMotions : uint8 
{
   BodyMotions_Idle        UMETA( DisplayName = "Idle" ),
   BodyMotions_Break    	UMETA( DisplayName = "Break" ),
   BodyMotions_Jog       	UMETA( DisplayName = "Jog" ),
   BodyMotions_Jump      	UMETA( DisplayName = "Jump" ),
   BodyMotions_JogJump   	UMETA( DisplayName = "JogJump" ),
   BodyMotions_CrouchJog   UMETA( DisplayName = "CrouchJog" ),
   BodyMotions_CrouchIdle  UMETA( DisplayName = "CrouchIdle" ),
   BodyMotions_Fall    	   UMETA( DisplayName = "Fall" ),
   BodyMotions_Prone    	UMETA( DisplayName = "Prone" ),
   BodyMotions_Die    	   UMETA( DisplayName = "Die" )
};

UENUM( BlueprintType )		
enum class ArmMotions : uint8 
{
   ArmMotions_Default          UMETA( DisplayName = "Default" ),
   ArmMotions_IronSight        UMETA( DisplayName = "IronSight" ),
   ArmMotions_IronSightFire    UMETA( DisplayName = "IronSightFire" ),
   ArmMotions_DefaultFire      UMETA( DisplayName = "DefaultFire" ),
   ArmMotions_DefaultReload    UMETA( DisplayName = "DefaultReload" ),
   ArmMotions_IronSightReload  UMETA( DisplayName = "IronSIghtReload" ),
   ArmMotions_Equip            UMETA( DisplayName = "Equip" )

};

UENUM( BlueprintType )		
enum class WeaponCategories : uint8
{
   WeaponCategories_BareHand       UMETA( DisplayName = "BareHand" ),
   WeaponCategories_Rifle          UMETA( DisplayName = "Rifle" ),
   WeaponCategories_ShotGun 	     UMETA( DisplayName = "ShotGun" )
};

UENUM( BlueprintType )		
enum class FireModes : uint8
{
   FireModes_Auto              UMETA( DisplayName = "Auto" ),
   FireModes_SemiAuto          UMETA( DisplayName = "SemiAuto" ),

};

enum CrosshairDirections : uint8
{
	CrosshairDirections_Left = 0,
	CrosshairDirections_Right = 1,
	CrosshairDirections_Top = 2,
	CrosshairDirections_Bottom = 3,
	CrosshairDirections_Center = 4
};

