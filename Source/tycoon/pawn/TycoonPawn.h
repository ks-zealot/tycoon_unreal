// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Misc/App.h"
#include "TycoonPawn.generated.h"

UCLASS()
class TYCOON_API ATycoonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATycoonPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	float VerticalCameraSpeed = 1000.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tycoon")
	float HorizontalCameraSpeed = 100.0;
	
private:
	void MoveX(float value);
	void MoveY(float value);
	void MoveZ(float value);
	FVector CurrentVelocity;
	float mod =HorizontalCameraSpeed;
	
 };
