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

	bool bCanBuild = true;
	bool bFlip = false;
	void createUI(APlayerController* player);
	void RecreateUI();
	void SpawnHouse();
	void generateRocks();

	UMainUI* ui;
	TArray<AHouseMeshActor*> houses;
	int32 housePrice = 0;
	int32 updateAvailableResource();
	bool checkFail();
	bool theEnd = false;
	UFUNCTION()
	void RemoveMe(AHouseMeshActor* house);
	FTimerHandle RockTimerHandle;
	ULoadingScreenUI* loadingWidget;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> MainUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class AHouseMeshActor> MyHouseBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class AStaticMeshActor> RockBluerint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> CursorBlockingBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> CursorBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> LoadingScreenWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 NumberOfRocks = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	float MinRockGenRadius = 100.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 MaxRockGenRadius = 100000.0;
	virtual void Tick(float DeltaSeconds) override;
};
