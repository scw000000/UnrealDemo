// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

class ABasicCharacter;
UCLASS()
class DEMO_API APatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPoint( const FObjectInitializer& ObjectInitializer );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   class UBillboardComponent* billboardComponent;

   UPROPERTY( EditInstanceOnly, BlueprintReadOnly, Category = Path )
      ABasicCharacter* pointOwner;

   UPROPERTY( EditInstanceOnly, BlueprintReadOnly, Category = Path )
	   APatrolPoint* nextPoint;

    UPROPERTY( EditInstanceOnly, BlueprintReadOnly, Category = Path )
      bool isHead;
	
};
