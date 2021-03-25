// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "HouseResourceTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class TYCOON_API UHouseResourceTextWidget : public UUserWidget
{
	GENERATED_BODY()
	private:
	int32 value = 0;
	public:
	void set(int32 val, float maxVal);
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* text;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* ResourceBar;
 
};
