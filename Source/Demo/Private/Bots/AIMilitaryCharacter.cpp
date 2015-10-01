// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "AIMilitaryCharacter.h"
#include "Bots/DemoAIController.h"

AAIMilitaryCharacter::AAIMilitaryCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AIControllerClass = ADemoAIController::StaticClass();

}


