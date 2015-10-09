// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_UpdateTraceMeter.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UBTService_UpdateTraceMeter : public UBTService
{
	GENERATED_BODY()
	
	virtual void TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) override;

};
