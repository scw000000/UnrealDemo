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

