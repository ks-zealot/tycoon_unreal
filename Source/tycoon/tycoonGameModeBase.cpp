// Copyright Epic Games, Inc. All Rights Reserved.


#include "tycoonGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "staticmeshes/HouseMeshActor.h"
#include "ui/LoadingScreenUI.h"
#include "util/UtilLib.h"


AtycoonGameModeBase::AtycoonGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}
 