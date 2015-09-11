// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicCharacter.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AItem(const FObjectInitializer& ObjectInitializer );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

   virtual void Tick( float DeltaSeconds ) override;

	//virtual void Used();

   void PickedUp( ABasicCharacter *const character );

   void Dropped( const FVector& location, const FRotator& rotation );
   
   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = Item )
      FString name;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = Item)
		UStaticMeshComponent* mesh;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = Item )
      bool pickedUpable;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = Item)
      float pickUpDistance;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = Item)
      int32 quantity;
};
