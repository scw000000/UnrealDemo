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
   BodyMotions_Prone    	UMETA( DisplayName = "Prone" )
};

UENUM( BlueprintType )		
enum class ArmMotions : uint8 
{
   ArmMotions_Default   UMETA( DisplayName = "Default" ),
   ArmMotions_IronSight UMETA( DisplayName = "IronSight" ),
   ArmMotions_Fire      UMETA( DisplayName = "Fire" ),
   ArmMotions_Reload    UMETA( DisplayName = "Reload" )
};

UENUM( BlueprintType )		
enum class WeaponCategories : uint8
{
   WeaponCategories_BareHand       UMETA( DisplayName = "BareHand" ),
   WeaponCategories_Rifle          UMETA( DisplayName = "Rifle" ),
   WeaponCategories_ShotGun 	      UMETA( DisplayName = "ShotGun" )
};

