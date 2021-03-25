// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseResourceTextWidget.h"


 

void UHouseResourceTextWidget::set(int32 val, float maxVal)
{
	text->SetText(FText::AsNumber(val));
	ResourceBar->SetPercent(val / maxVal);
}
