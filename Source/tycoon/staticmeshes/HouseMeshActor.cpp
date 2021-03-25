// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseMeshActor.h"


#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "tycoon/ui/HouseBuildingWidget.h"
#include "tycoon/ui/HouseResourceTextWidget.h"
#include "tycoon/util/UtilLib.h"

AHouseMeshActor::AHouseMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	resourceWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ResourceWidget"));
	notCompleteResourceWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildingWidget"));
	notCompleteResourceWidget->SetVisibility(true);
	springArm->SetupAttachment(RootComponent);
	resourceWidget->SetupAttachment(springArm);
	notCompleteResourceWidget->SetupAttachment(springArm);
	 
}

void AHouseMeshActor::BeginPlay()
{
	Super::BeginPlay();
	resourceWidget->SetVisibility(false);
	GetStaticMeshComponent()->SetStaticMesh(NotCompleteHouse);
	UHouseResourceTextWidget* widgetPtr = Cast<UHouseResourceTextWidget>(resourceWidget->GetUserWidgetObject());
    widgetPtr->set(0, static_cast<float>(KillResourcesValue));
}

void AHouseMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (resource >= KillResourcesValue)
	{
		return;
	}
	tick += DeltaTime;
	if (tick >= 1.0)
	{
		tick = 0.0;
		if (bNotCompleted)
		{
			BuildingTime += 1.0;
			UHouseBuildingWidget* widgetPtr = Cast<UHouseBuildingWidget>(notCompleteResourceWidget->GetUserWidgetObject());
			widgetPtr->set(BuildingTime * 20   );
			if (BuildingTime == 5.0)
			{
				bNotCompleted = false;
				notCompleteResourceWidget->SetVisibility(false);
				resourceWidget->SetVisibility(true);
				GetStaticMeshComponent()->SetStaticMesh(CompleteHouse);
			}
		} else
		{
			resource += IncomePerSecond;
			if (resource % SpawnNpcResourcesValue == 0)
			{
				SpawnNpc();
			}
			UHouseResourceTextWidget* widgetPtr = Cast<UHouseResourceTextWidget>(resourceWidget->GetUserWidgetObject());
			widgetPtr->set(resource, static_cast<float>(KillResourcesValue));
			if (resource == KillResourcesValue)
			{
				killDelegate.ExecuteIfBound(myIndex);
				KillMe();
			}
		}
		
		
	}
}


void AHouseMeshActor::SpawnNpc()
{
	FVector location = GetActorLocation();
	FVector2D random = UUtilLib::GetRandomPointTwoCircles(UKismetMathLibrary::Conv_VectorToVector2D(location), SpawnNpcMinRadius, SpawnNpcMaxRadius);
	ANPCCharacter* npc = GetWorld()->SpawnActor<ANPCCharacter>(NPCBlueprint, FVector(random, 30), FRotator::ZeroRotator);
	if (npc)
	{
		npc->GetMesh()->SetCollisionProfileName(FName("CharacterMesh"), false);
		npc->startPoint = UKismetMathLibrary::Conv_VectorToVector2D(GetActorLocation());
		npcs.Add(npc);
	}
}

 

int32 AHouseMeshActor::GetResource()
{
	return resource;
}

void AHouseMeshActor::SetResource(int32 val)
{
	resource = val;
	UHouseResourceTextWidget* widgetPtr = Cast<UHouseResourceTextWidget>(resourceWidget->GetUserWidgetObject());
	widgetPtr->set(resource, static_cast<float>(KillResourcesValue));
}
