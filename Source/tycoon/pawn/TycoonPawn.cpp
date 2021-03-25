// Fill out your copyright notice in the Description page of Project Settings.


#include "TycoonPawn.h"


// Sets default values
ATycoonPawn::ATycoonPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATycoonPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATycoonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		mod++;
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	else
	{
		mod = HorizontalCameraSpeed;
	}
}

// Called to bind functionality to input
void ATycoonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveX", this, &ATycoonPawn::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATycoonPawn::MoveY);
	InputComponent->BindAxis("MoveUpDown", this, &ATycoonPawn::MoveZ);
}

void ATycoonPawn::MoveX(float value)
{
	CurrentVelocity.X = FMath::Clamp(value, -1.0f, 1.0f) * mod;
}

void ATycoonPawn::MoveY(float value)
{
	CurrentVelocity.Y = FMath::Clamp(value, -1.0f, 1.0f) * mod;
}

void ATycoonPawn::MoveZ(float value)
{
	CurrentVelocity.Z = FMath::Clamp(value, -1.0f, 1.0f) * VerticalCameraSpeed;
}
