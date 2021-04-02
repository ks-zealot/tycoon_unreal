// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class TYCOON_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Tycoon")
	FVector2D startPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	float RanfomDestinationRadius = 100.0;

	
	UFUNCTION(BlueprintCallable)
	FVector GetRandomDestination();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
