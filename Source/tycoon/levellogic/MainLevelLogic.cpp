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
	LoadingWidget = CreateWidget<ULoadingScreenUI>(player, LoadingScreenWidget);
	LoadingWidget->AddToViewport();


	world->GetTimerManager().SetTimer(RockTimerHandle, this, &AMainLevelLogic::GenerateRocks, 1.0, false);
	CreateUI(player);
	player->bShowMouseCursor = true;
	player->InputComponent->BindKey(EKeys::Q, IE_Released, this, &AMainLevelLogic::RecreateUI);
	player->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AMainLevelLogic::SpawnHouse);
	UpdateAvailableResources();
}


void AMainLevelLogic::GenerateRocks()
{
	for (int32 i = 0; i <= NumberOfRocks; i++)
	{
		LoadingWidget->ProgressBar->SetPercent(i / float(NumberOfRocks));
		FVector2D random = UUtilLib::GetRandomPointCircleWithMinMax(MinRockGenRadius, MaxRockGenRadius);
		GetWorld()->SpawnActor<AStaticMeshActor>(RockBluerint, FVector(random, 0), FRotator::ZeroRotator);
	}
	LoadingWidget->RemoveFromParent();
}

/*
*TODO find more clear way to reset default cursor
*/
void AMainLevelLogic::RecreateUI()
{
	UWorld* world = GetWorld();
	UWidgetLayoutLibrary::RemoveAllWidgets(world);
	CreateUI(world->GetFirstPlayerController());
}

void AMainLevelLogic::CreateUI(APlayerController* player)
{
	ui = CreateWidget<UMainUI>(player, MainUI);
	ui->AddToViewport();
	ui->SetHousePrice(HousePrice);
}

void AMainLevelLogic::NotifyAboutSpawnHouse()
{
	UWorld* World = GetWorld();
	APlayerController* player = World->GetFirstPlayerController();
	player->SetMouseCursorWidget(EMouseCursor::Default, CreateWidget<UUserWidget>(ui,
		                             CursorBlueprint));
	bAboutToSpawnHouse = true;
}

void AMainLevelLogic::SpawnHouse()
{
	if (bAboutToSpawnHouse)
	{
		UWorld* World = GetWorld();
		APlayerController* Player = World->GetFirstPlayerController();
		FHitResult HitResult;
		bool bRes = Player->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		                                                     HitResult);
		if (bRes)
		{
			if (bCanBuild)
			{
				int32 LocalHousePrice = HousePrice;
				Calculate(StartCredit, LocalHousePrice);
				for (AHouseMeshActor* House : Houses)
				{
					int32 Res = House->GetResource();
					Calculate(Res, LocalHousePrice);
					House->SetResource(Res);
					if (LocalHousePrice == 0)
					{
						break;
					}
				}


				FVector Location = HitResult.Location;
				//set Z axias  to 0, or house will be fly
				FVector HouseLocation = FVector(Location.X, Location.Y, 0.0);
				FRotator Rotator = FRotator(0.0, 270.0, 0.0);
				FTransform Transform =
					UKismetMathLibrary::MakeTransform(HouseLocation, Rotator, FVector::OneVector);
				AHouseMeshActor* HouseMeshActor = World->SpawnActor<AHouseMeshActor>(
					MyHouseBlueprint, Transform);
				int32 Idx = Houses.Add(HouseMeshActor);
				HouseMeshActor->MyIndex = Idx;
				HouseMeshActor->killDelegate.BindUObject(this, &AMainLevelLogic::RemoveMe);
				HousePrice = Houses.Num() / 10 * 100 + 100;
				ui->SetHousePrice(HousePrice);
				UE_LOG(LogTemp, Log, TEXT("house Location %f %f %d"), HouseLocation.X, HouseLocation.Y, Idx);
				bAboutToSpawnHouse = false;
				RecreateUI();
			}
			else
			{
				bAboutToSpawnHouse = false;
				RecreateUI();
			}
		}
	}
}


void AMainLevelLogic::Calculate(int32& Res, int32& Price)
{
	int32 NewResources = Res - Price;
	int32 NewLocalPriceHouse = Price - Res;
	Res = FMath::Clamp<int32>(NewResources, 0, NewResources);
	Price = FMath::Clamp<int32>(NewLocalPriceHouse, 0, NewLocalPriceHouse);
}

void AMainLevelLogic::Tick(float DeltaSeconds)
{
	if (bIsIheEnd)
	{
		return;
	}
	if (СheckFail())
	{
		UGameplayStatics::OpenLevel(GetWorld(), "EndGame");
		return;
	}
	if (bAboutToSpawnHouse)
	{
		UWorld* world = GetWorld();
		APlayerController* player = world->GetFirstPlayerController();
		FHitResult HitResult;
		bool bHitResult = player->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility),
		                                                           false,
		                                                           HitResult);
		if (bHitResult)
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

int32 AMainLevelLogic::UpdateAvailableResources()
{
	int32 LocalAvailableResources = StartCredit;
	for (int i = 0; i < Houses.Num(); i++)
	{
		LocalAvailableResources += Houses[i]->GetResource();
	}
	ui->SetResources(LocalAvailableResources);
	if (HousePrice > LocalAvailableResources)
	{
		ui->DisableSpawnButton();
	}
	else
	{
		ui->EnableSpawnButton();
	}
	return LocalAvailableResources;
}

bool AMainLevelLogic::СheckFail()
{
	int32 AvailableResources = UpdateAvailableResources();
	if (HousePrice > AvailableResources && Houses.Num() == 0)
	{
		UWorld* world = GetWorld();
		UWidgetLayoutLibrary::RemoveAllWidgets(world);

		PrimaryActorTick.bCanEverTick = false;
		bIsIheEnd = true;
		return true;
	}
	return false;
}

void AMainLevelLogic::RemoveMe(AHouseMeshActor* house)
{
	house->killDelegate.Unbind();
	Houses.Remove(house);
}
