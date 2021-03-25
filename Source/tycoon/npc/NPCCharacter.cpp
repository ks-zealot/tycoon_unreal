// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"

#include "tycoon/util/UtilLib.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FVector ANPCCharacter::GetRandomDestination()
{
	return FVector(UUtilLib::GetRandomPointOnCircle(startPoint, RanfomDestinationRadius), 0.0);
}
