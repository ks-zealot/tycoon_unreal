// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseSpawnButton.h"

#include "Kismet/GameplayStatics.h"
#include "tycoon/tycoonGameModeBase.h"

UHouseSpawnButton::UHouseSpawnButton()
{
	OnClicked.AddDynamic(this, &UHouseSpawnButton::SpawnHouse);
	 
}

void UHouseSpawnButton::SpawnHouse()
{
	GetOwningPlayer()->SetMouseCursorWidget(EMouseCursor::Default, CreateWidget<UUserWidget>(this->GetParent(),
		                                        CursorBlueprint));
	AtycoonGameModeBase* tycoonMode = Cast< AtycoonGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	tycoonMode->bAboutToSpawnHouse = true;
}
