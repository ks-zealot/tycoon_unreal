// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

void UMainUI::SetResources(int32 val)
{
	if (Resources)
	{
		Resources->SetText(FText::AsNumber(val));
	}
}

void UMainUI::SetHousePrice(int32 val)
{
	if (HousePrice)
	{
		HousePrice->SetText(FText::AsNumber(val));
	}
}

void UMainUI::DisableSpawnButton()
{
	 HouseSpawnButton->SetIsEnabled(false);
}

void UMainUI::EnableSpawnButton()
{
	HouseSpawnButton->SetIsEnabled(true);
}
