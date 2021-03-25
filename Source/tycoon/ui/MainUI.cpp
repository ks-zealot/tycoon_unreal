// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

void UMainUI::setResources(int32 val)
{
	if (resources)
	{
		resources->SetText(FText::AsNumber(val));
	}
}
