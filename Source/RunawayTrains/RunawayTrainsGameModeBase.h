// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunawayTrainsGameModeBase.generated.h"

/**
 * 
 */

class AEndLevel;

UCLASS()
class RUNAWAYTRAINS_API ARunawayTrainsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEndLevel* EndLevel;
	
};
