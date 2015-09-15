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

   int32 GetQuantity();

   UTexture2D * GetIcon();
   
   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Item )
      FString name;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Item )
      UTexture2D *icon;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Item)
		UStaticMeshComponent* mesh;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Item )
      bool pickedUpable;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Item)
      float pickUpDistance;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Item)
      int32 quantity;
};
