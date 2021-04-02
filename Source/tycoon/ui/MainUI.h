// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HouseSpawnButton.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class TYCOON_API UMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Resources;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* HousePrice;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHouseSpawnButton* HouseSpawnButton;
	
	void SetResources(int32 val);
	void SetHousePrice(int32 val);
	void DisableSpawnButton();
	void EnableSpawnButton();
};
