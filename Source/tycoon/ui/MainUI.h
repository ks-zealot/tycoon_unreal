// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UTextBlock* resources;
	void setResources(int32 val);
};
