// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "tycoon/npc/NPCCharacter.h"
#include "tycoon/ui/HouseResourceTextWidget.h"

#include "HouseMeshActor.generated.h"


/**
 * 
 */
DECLARE_DELEGATE_OneParam(FKillDelegate, AHouseMeshActor* );
UCLASS()
class TYCOON_API AHouseMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()
	AHouseMeshActor();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tycoon")
	USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tycoon")
	UWidgetComponent* resourceWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tycoon")
	UWidgetComponent* notCompleteResourceWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tycoon")
	TArray<ANPCCharacter*> npcs;
	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCharacter")
	void KillMe();
	int32 GetResource();
	void SetResource(int32 val);
	int32 myIndex;
	FKillDelegate killDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class AActor> NPCBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	UStaticMesh* NotCompleteHouse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	UStaticMesh* CompleteHouse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget> NotCompleteWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	TSubclassOf<class UUserWidget>  CompleteWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 IncomePerSecond = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 KillResourcesValue = 150;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	int32 SpawnNpcResourcesValue = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	float SpawnNpcMinRadius = 70;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	float SpawnNpcMaxRadius = 100;
protected:
	virtual void BeginPlay() override;
private:
	float BuildingTime = 0.0;
	int32 resource = 0;
	void SpawnNpc();
	void UpdateResources();
	bool bNotCompleted = true;
	FTimerHandle UpdateResourcesTimerHandle;
};
