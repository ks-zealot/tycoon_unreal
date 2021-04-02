// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseSpawnButton.h"

#include "Kismet/GameplayStatics.h"
#include "tycoon/tycoonGameModeBase.h"
#include "tycoon/levellogic/MainLevelLogic.h"

UHouseSpawnButton::UHouseSpawnButton()
{
	OnClicked.AddDynamic(this, &UHouseSpawnButton::SpawnHouse);
	 
}

void UHouseSpawnButton::SpawnHouse()
{
	Cast<AMainLevelLogic>(GetWorld()->GetLevelScriptActor())->NotifyAboutSpawnHouse() ;
}
