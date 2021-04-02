// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "HouseBuildingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TYCOON_API UHouseBuildingWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* BuildingBar;
	
	
	void Set(int32 val);
};
