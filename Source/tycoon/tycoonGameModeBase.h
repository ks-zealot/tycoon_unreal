// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ui/MainUI.h"
#include "staticmeshes/HouseMeshActor.h"
#include "tycoonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TYCOON_API AtycoonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AtycoonGameModeBase();
	public:
	UPROPERTY(BlueprintReadWrite)
	bool bAboutToSpawnHouse = false;
	
protected:
	virtual void BeginPlay() override;
private:
	
	bool bCanBuild = true;
	bool bFlip = false;
	void createUI(  APlayerController* player);
	void RecreateUI();
	void SpawnHouse();
	void generateRocks();
	
	UMainUI* ui;
	TArray<AHouseMeshActor*> houses;
	int32 housePrice = 0;
	int32 updateAvailableResource();
	bool checkFail( );
	bool theEnd = false;
	UFUNCTION()
	void RemoveMe(int32 idx);
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
	 
	virtual void Tick(float DeltaSeconds) override;
};
