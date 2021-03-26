// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelLogic.h"



AMainLevelLogic::AMainLevelLogic()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainLevelLogic::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	APlayerController* player = world->GetFirstPlayerController();
	loadingWidget = CreateWidget<ULoadingScreenUI>(player, LoadingScreenWidget);
	loadingWidget->AddToViewport();

	
	if (!IsValid(world))
	{
		UE_LOG(LogTemp, Log, TEXT("no world"));
	}

	world->GetTimerManager().SetTimer(RockTimerHandle, this, &AMainLevelLogic::generateRocks, 1.0, false);
	createUI(player);
	player->bShowMouseCursor = true;
	player->InputComponent->BindKey(EKeys::Q, IE_Released, this, &AMainLevelLogic::RecreateUI);
	player->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AMainLevelLogic::SpawnHouse);
	updateAvailableResource();
}


void AMainLevelLogic::generateRocks()
{
	for (int32 i = 0; i <= NumberOfRocks; i++)
	{
		loadingWidget->progress->SetPercent(i / float(NumberOfRocks));
		FVector2D random = UUtilLib::GetRandomPointCircleWithMinMax(MinRockGenRadius, MaxRockGenRadius);
		GetWorld()->SpawnActor<AStaticMeshActor>(RockBluerint, FVector(random, 0), FRotator::ZeroRotator);
	}
	loadingWidget->RemoveFromParent();
}

/*
*Восстанавливаю дефолтный курсор.
Более вменяемого способа это сделать я не нашел
*/
void AMainLevelLogic::RecreateUI()
{
	UWorld* world = GetWorld();
	UWidgetLayoutLibrary::RemoveAllWidgets(world);
	createUI(world->GetFirstPlayerController());
}

void AMainLevelLogic::createUI(APlayerController* player)
{
	ui = CreateWidget<UMainUI>(player, MainUI);
	ui->AddToViewport();
}

void AMainLevelLogic::SpawnHouse()
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
					house->killDelegate.BindUObject(this, &AMainLevelLogic::RemoveMe);
					housePrice = houses.Num() / 10 * 100 + 100;
					UE_LOG(LogTemp, Log, TEXT("house Location %f %f %d"), HouseLocation.X, HouseLocation.Y, idx);
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

void AMainLevelLogic::Tick(float DeltaSeconds)
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

int32 AMainLevelLogic::updateAvailableResource()
{
	int32 availableResource = 0;
	for (int i = 0; i < houses.Num(); i++)
	{
		availableResource += houses[i]->GetResource();
	}
	ui->setResources(availableResource);
	return availableResource;
}

bool AMainLevelLogic::checkFail()
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

void AMainLevelLogic::RemoveMe(AHouseMeshActor* house)
{
	house->killDelegate.Unbind();
	houses.Remove(house);
}