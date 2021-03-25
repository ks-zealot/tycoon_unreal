// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "../staticmeshes/HouseMeshActor.h"
#include "HouseSpawnButton.generated.h"

/**
 * 
 */
UCLASS()
class TYCOON_API UHouseSpawnButton : public UButton
{
	GENERATED_BODY()
	UHouseSpawnButton();
	public:
	UFUNCTION()
	void SpawnHouse();
	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> CursorBlueprint;
};
