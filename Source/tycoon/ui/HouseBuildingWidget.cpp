// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseBuildingWidget.h"

void UHouseBuildingWidget::Set(int32 val)
{
	 BuildingBar->SetPercent(val / 100.0f);
}
