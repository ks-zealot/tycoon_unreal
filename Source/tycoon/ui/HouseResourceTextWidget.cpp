// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseResourceTextWidget.h"

#include "Kismet/KismetMathLibrary.h"


void UHouseResourceTextWidget::Set(int32 val, float maxVal)
{
	Text->SetText(FText::FromString(FString::FromInt(val).Append("/").Append(FString::FromInt(maxVal))));
	float percentToKill = val / maxVal;
	Text->SetColorAndOpacity(
		FSlateColor(UKismetMathLibrary::LinearColorLerp(FLinearColor::White, FLinearColor::Red, percentToKill)));
	ResourceBar->SetPercent(val / maxVal);
}
