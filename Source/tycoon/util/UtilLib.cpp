// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilLib.h"

FVector2D UUtilLib::GetRandomPointTwoCircles(FVector2D origin, float min, float max)
{
	float angle = UKismetMathLibrary::RandomFloatInRange(0.0, 2 * UKismetMathLibrary::GetPI());
	FVector2D randomDirection = FVector2D(UKismetMathLibrary::Cos(angle),
	                                      UKismetMathLibrary::Sin(angle)) * origin;
	randomDirection.Normalize();
	const float randomDistance = UKismetMathLibrary::RandomFloatInRange(min, max);
	FVector2D res = origin + randomDirection * randomDistance;
	return res;
}

FVector2D UUtilLib::GetRandomPointCircle(float radius)
{
	float angle = UKismetMathLibrary::RandomFloatInRange(0.0, 2 * UKismetMathLibrary::GetPI());
	FVector2D randomDirection = FVector2D(UKismetMathLibrary::Cos(angle),
	                                      UKismetMathLibrary::Sin(angle));
	randomDirection.Normalize();
	const float randomDistance = UKismetMathLibrary::RandomFloatInRange(0, radius);
	return randomDirection * randomDistance;
}

FVector2D UUtilLib::GetRandomPointOnCircle(FVector2D origin, float radius)
{
	float angle = UKismetMathLibrary::RandomFloatInRange(0.0, 2 * UKismetMathLibrary::GetPI());
	FVector2D randomDirection = FVector2D(UKismetMathLibrary::Cos(angle),
	                                      UKismetMathLibrary::Sin(angle));
	randomDirection.Normalize();
	return randomDirection * radius;
}

FVector2D UUtilLib::GetRandomPointCircleWithMinMax(float min, float max)
{
	float angle = UKismetMathLibrary::RandomFloatInRange(0.0, 2 * UKismetMathLibrary::GetPI());
	FVector2D randomDirection = FVector2D(UKismetMathLibrary::Cos(angle),
	                                      UKismetMathLibrary::Sin(angle));
	randomDirection.Normalize();
	const float randomDistance = UKismetMathLibrary::RandomFloatInRange(min, max);
	return randomDirection * randomDistance;
}
