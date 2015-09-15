// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class DEMO_API BackpackItem
{
public:
   BackpackItem( UTexture2D * iIcon, const FString &  iName, int32 iQuantity );

	~BackpackItem();

   void SetName( const FString & aName );

   void SetQuantity( int32 aQuantity );

   UTexture2D * const GetIcon( );

   FString GetName();

   int32 GetQuantity();

   

private:
   UTexture2D *icon;
   FString name;
   int32 quantity;
};
