// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

UENUM( BlueprintType )		//"BlueprintType" is essential to include
enum class PlayerViewTypes : uint8 
{
   PlayerViewTypes_FirstPerson 	UMETA( DisplayName = "FirstPerson" ),
   PlayerViewTypes_Aim 	UMETA( DisplayName = "Aim" ),
   PlayerViewTypes_ThirdPerson 	UMETA( DisplayName = "ThirdPerson" )
};

UENUM( BlueprintType )		//"BlueprintType" is essential to include
enum class PlayerMotionTypes : uint8 {
   PlayerMotionTypes_Stand 	UMETA( DisplayName = "Stand" ),
   PlayerMotionTypes_Crouch 	UMETA( DisplayName = "Crouch" ),
   PlayerMotionTypes_Prone 	UMETA( DisplayName = "Prone" ),
   PlayerMotionTypes_Jump   	UMETA( DisplayName = "Jump" )
};

UENUM( BlueprintType )		//"BlueprintType" is essential to include
enum class PlayerAimTypes : uint8 {
   PlayerAimTypes_BareHand       	UMETA( DisplayName = "BareHand" ),
   PlayerAimTypes_RifleHip 	      UMETA( DisplayName = "RifleHip" ),
   PlayerAimTypes_RifleIronSight 	UMETA( DisplayName = "RifleIronSight" )
};

