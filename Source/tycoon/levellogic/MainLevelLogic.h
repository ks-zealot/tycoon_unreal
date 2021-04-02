// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "tycoon/ui/LoadingScreenUI.h"
#include "tycoon/ui/MainUI.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "../staticmeshes/HouseMeshActor.h"
#include "../util/UtilLib.h"
#include "MainLevelLogic.generated.h"

/**
 * 
 */
UCLASS()
class TYCOON_API AMainLevelLogic : public ALevelScriptActor
{
	GENERATED_BODY()
public:

	AMainLevelLogic();
public:
	UPROPERTY(BlueprintReadWrite)
	bool bAboutToSpawnHouse = false;

protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void RemoveMe(AHouseMeshActor* house);
	void CreateUI(APlayerController* player);
	void RecreateUI();
	void SpawnHouse();
	void GenerateRocks();
	void Calculate(int32& Res,int32& Price);
	bool СheckFail();
	int32 UpdateAvailableResources();

	//UI
	UMainUI* ui;
	ULoadingScreenUI* LoadingWidget;

	//bool switches
	bool bCanBuild = true;
	bool bFlip = false;
	bool bIsIheEnd = false;

	//houses
	TArray<AHouseMeshActor*> Houses;
	//current house price
	int32 HousePrice = 100;
	//handler for timer
	FTimerHandle RockTimerHandle;

public:
	//widget BPs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> MainUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> CursorBlockingBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> CursorBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> LoadingScreenWidget;

	//mesh BPs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class AHouseMeshActor> MyHouseBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class AStaticMeshActor> RockBluerint;

	//properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 NumberOfRocks = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 StartCredit = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	float MinRockGenRadius = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 MaxRockGenRadius = 100000.0;

	virtual void Tick(float DeltaSeconds) override;
	void NotifyAboutSpawnHouse();
};
