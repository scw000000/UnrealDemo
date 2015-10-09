// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BTService_UpdateTraceMeter.h"
#include "Bots/DemoAIController.h"

void UBTService_UpdateTraceMeter::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) 
{
   ADemoAIController* myController = Cast<ADemoAIController>( OwnerComp.GetAIOwner() );

   myController->UpdateTraceMeter( DeltaSeconds );
}



