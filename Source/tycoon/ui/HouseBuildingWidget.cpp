// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseBuildingWidget.h"

void UHouseBuildingWidget::set(int32 val)
{
	 BuildingBar->SetPercent(val / 100.0f);
}
