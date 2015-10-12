// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Bots/PatrolPoint.h"

class APatrolPoint;
class ABasicCharacter;
/**
 * 
 */
class DEMO_API PatrolPathManager
{
public:
	PatrolPathManager();

	~PatrolPathManager();

   void SetToNextDestination();

   bool SetStartPoint( ABasicCharacter* pathOwner );

   FVector GetCurrentDestination();

   

protected:

   APatrolPoint* currentPoint;

   TDoubleLinkedList<APatrolPoint*> partolPath;
};
