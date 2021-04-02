// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseMeshActor.h"


#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "tycoon/ui/HouseBuildingWidget.h"
#include "tycoon/ui/HouseResourceTextWidget.h"
#include "tycoon/util/UtilLib.h"

AHouseMeshActor::AHouseMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	ResourceWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ResourceWidget"));
	NotCompleteResourceWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildingWidget"));
	NotCompleteResourceWidget->SetVisibility(true);
	SpringArm->SetupAttachment(RootComponent);
	ResourceWidget->SetupAttachment(SpringArm);
	NotCompleteResourceWidget->SetupAttachment(SpringArm);
}

void AHouseMeshActor::BeginPlay()
{
	Super::BeginPlay();
	ResourceWidget->SetVisibility(false);
	GetStaticMeshComponent()->SetStaticMesh(NotCompleteHouse);
	UHouseResourceTextWidget* widgetPtr = Cast<UHouseResourceTextWidget>(ResourceWidget->GetUserWidgetObject());
	widgetPtr->Set(0, static_cast<float>(KillResourcesValue));
	GetWorld()->GetTimerManager().SetTimer(UpdateResourcesTimerHandle, this, &AHouseMeshActor::UpdateResources, 1.0,
	                                       true);
}


void AHouseMeshActor::UpdateResources()
{
	if (bNotCompleted)
	{
		BuildingTime += 1.0;
		UHouseBuildingWidget* widgetPtr = Cast<UHouseBuildingWidget>(
			NotCompleteResourceWidget->GetUserWidgetObject());
		widgetPtr->Set(BuildingTime * 20);
		if (BuildingTime == 5.0)
		{
			bNotCompleted = false;
			NotCompleteResourceWidget->SetVisibility(false);
			ResourceWidget->SetVisibility(true);
			GetStaticMeshComponent()->SetStaticMesh(CompleteHouse);
		}
	}
	else
	{
		Resource += IncomePerSecond;
		if (Resource % SpawnNpcResourcesValue == 0)
		{
			SpawnNpc();
		}
		UHouseResourceTextWidget* widgetPtr = Cast<UHouseResourceTextWidget>(ResourceWidget->GetUserWidgetObject());
		widgetPtr->Set(Resource, static_cast<float>(KillResourcesValue));
		if (Resource == KillResourcesValue)
		{
			killDelegate.ExecuteIfBound(this);
			KillMe();
		}
	}
}

void AHouseMeshActor::SpawnNpc()
{
	FVector location = GetActorLocation();
	FVector2D random = UUtilLib::GetRandomPointTwoCircles(UKismetMathLibrary::Conv_VectorToVector2D(location),
	                                                      SpawnNpcMinRadius, SpawnNpcMaxRadius);
	FTransform transform = UKismetMathLibrary::MakeTransform(FVector(random, 30), FRotator::ZeroRotator,
	                                                         FVector::OneVector);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	ANPCCharacter* npc = GetWorld()->SpawnActor<ANPCCharacter>(NPCBlueprint, transform, SpawnParameters);
	if (npc)
	{
		npc->GetMesh()->SetCollisionProfileName(FName("CharacterMesh"), false);
		npc->startPoint = UKismetMathLibrary::Conv_VectorToVector2D(GetActorLocation());
		NPCs.Add(npc);
	}
}


int32 AHouseMeshActor::GetResource()
{
	return Resource;
}

void AHouseMeshActor::SetResource(int32 val)
{
	Resource = val;
	UHouseResourceTextWidget* widgetPtr = Cast<UHouseResourceTextWidget>(ResourceWidget->GetUserWidgetObject());
	widgetPtr->Set(Resource, static_cast<float>(KillResourcesValue));
}
