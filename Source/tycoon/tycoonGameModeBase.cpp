// Copyright Epic Games, Inc. All Rights Reserved.


#include "tycoonGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "staticmeshes/HouseMeshActor.h"
#include "util/UtilLib.h"


AtycoonGameModeBase::AtycoonGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AtycoonGameModeBase::BeginPlay()
{
	generateRocks();
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	createUI(player);
	player->bShowMouseCursor = true;
	player->InputComponent->BindKey(EKeys::Q, IE_Released, this, &AtycoonGameModeBase::RecreateUI);
	player->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AtycoonGameModeBase::SpawnHouse);
	updateAvailableResource();
}


void AtycoonGameModeBase::generateRocks()
{
	for (int32 i = 0; i < 100; i++)
	{
		FVector2D random = UUtilLib::GetRandomPointCircleWithMinMax(100.0, 100000.0);
		GetWorld()->SpawnActor<AStaticMeshActor>(RockBluerint, FVector(random, 0), FRotator::ZeroRotator);
	}
}

/*
*Восстанавливаю дефолтный курсор.
Более вменяемого способа это сделать я не нашел
*/
void AtycoonGameModeBase::RecreateUI()
{
	UWorld* world = GetWorld();
	UWidgetLayoutLibrary::RemoveAllWidgets(world);
	createUI(world->GetFirstPlayerController());
}

void AtycoonGameModeBase::createUI(APlayerController* player)
{
	ui = Cast<UMainUI>(CreateWidget(player, MainUI));
	ui->AddToViewport();
}

void AtycoonGameModeBase::SpawnHouse()
{
	if (bAboutToSpawnHouse)
	{
		UWorld* world = GetWorld();
		APlayerController* player = world->GetFirstPlayerController();
		FHitResult HitResult;
		bool bRes = player->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		                                                     HitResult);
		if (bRes)
		{
			if (bCanBuild)
			{
				int32 availableResource = 0;
				for (int i = 0; i < houses.Num(); i++)
				{
					availableResource += houses[i]->GetResource();
				}
				if (availableResource < housePrice)
				{
					UE_LOG(LogTemp, Log, TEXT("need more gold!"));
					bAboutToSpawnHouse = false;
					RecreateUI();
				}
				else
				{
					int32 localHousePrice = housePrice;

					for (AHouseMeshActor* house : houses)
					{
						int32 res = house->GetResource();
						house->SetResource(FMath::Clamp(res, 0, res - localHousePrice));
						localHousePrice = FMath::Clamp(localHousePrice, 0, localHousePrice - res);
						if (localHousePrice == 0)
						{
							break;
						}
					}


					FVector location = HitResult.Location;
					//надо занулить Z ось иначе домик повиснет в воздухе.
					FVector HouseLocation = FVector(location.X, location.Y, 0.0);
					FRotator Rotator = FRotator(0.0, 270.0, 0.0);
					// если передавать в функцию транформ вместо локации и ротатора, то моделька меняется. Да, я тоже не знаю.
					FTransform transform = UKismetMathLibrary::MakeTransform(HouseLocation, Rotator, FVector());
					AHouseMeshActor* house = world->SpawnActor<AHouseMeshActor>(
						MyHouseBlueprint, HouseLocation, Rotator);
					int32 idx = houses.Add(house);
					house->myIndex = idx;
					house->killDelegate.BindUObject(this, &AtycoonGameModeBase::RemoveMe);
					housePrice = houses.Num() / 10 * 100 + 100;
					UE_LOG(LogTemp, Log, TEXT("house Location %f %f"), HouseLocation.X, HouseLocation.Y);
					bAboutToSpawnHouse = false;
					RecreateUI();
				}
			}
			else
			{
				bAboutToSpawnHouse = false;
				RecreateUI();
			}
		}
	}
}

void AtycoonGameModeBase::Tick(float DeltaSeconds)
{
	if (theEnd)
	{
		return;
	}
	updateAvailableResource();
	if (checkFail())
	{
		UGameplayStatics::OpenLevel(GetWorld(), "EndGame");
		return;
	}
	if (bAboutToSpawnHouse)
	{
		UWorld* world = GetWorld();
		APlayerController* player = world->GetFirstPlayerController();
		FHitResult HitResult;
		bool bRes = player->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		                                                     HitResult);
		if (bRes)
		{
			FVector location = HitResult.Location;
			bool bSphereRes = UKismetSystemLibrary::SphereTraceSingle(world, location, location, 40.0f,
			                                                          UEngineTypes::ConvertToTraceType(
				                                                          ECC_PhysicsBody), false,
			                                                          TArray<AActor*>(), EDrawDebugTrace::None,
			                                                          HitResult,
			                                                          true,
			                                                          FLinearColor::Red, FLinearColor::Green, 5.0);

			if (bFlip != bSphereRes)
			{
				bFlip = bSphereRes;
				bCanBuild = !bFlip;
				if (bSphereRes)
				{
					player->SetMouseCursorWidget(EMouseCursor::Default, CreateWidget<UUserWidget>(ui,
						                             CursorBlockingBlueprint));
				}
				else
				{
					player->SetMouseCursorWidget(EMouseCursor::Default, CreateWidget<UUserWidget>(ui,
						                             CursorBlueprint));
				}
			}
		}
	}
}

int32 AtycoonGameModeBase::updateAvailableResource()
{
	int32 availableResource = 0;
	for (int i = 0; i < houses.Num(); i++)
	{
		availableResource += houses[i]->GetResource();
	}
	ui->setResources(availableResource);
	return availableResource;
}

bool AtycoonGameModeBase::checkFail()
{
	if (housePrice > 0 && houses.Num() == 0)
	{
		UWorld* world = GetWorld();
		UWidgetLayoutLibrary::RemoveAllWidgets(world);

		PrimaryActorTick.bCanEverTick = false;
		theEnd = true;
		return true;
	}
	return false;
}

void AtycoonGameModeBase::RemoveMe(int32 idx)
{
	AHouseMeshActor* house = houses[idx];
	house->killDelegate.Unbind();
	houses.RemoveAt(idx);
}
