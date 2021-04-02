// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/NoExportTypes.h"
#include "UtilLib.generated.h"

/**
 * 
 */
UCLASS()
class TYCOON_API UUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure,
		meta=(DisplayName = "Random point within two circles", CompactNodeTitle = "Random Point Two Circles"),
		Category="Math|Trig")
	static FVector2D GetRandomPointTwoCircles(FVector2D origin, float min, float max);
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Random point within circle", CompactNodeTitle = "Random Point "),
		Category="Math|Trig")
	static FVector2D GetRandomPointCircle(float radius);
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Random point on circle", CompactNodeTitle = "Random Point On Circle"),
		Category="Math|Trig")
	static FVector2D GetRandomPointOnCircle(FVector2D origin, float radius);
	UFUNCTION(BlueprintPure,
		meta=(DisplayName = "Random point in circle", CompactNodeTitle = "Random Point On Circle with origin 0.0"),
		Category="Math|Trig")
	static FVector2D GetRandomPointCircleWithMinMax(float min, float max);
};
