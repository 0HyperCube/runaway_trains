// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include <TrainTragedy/Track/TrackSegement.h>
#include "GameLevelBase.generated.h"


/* 
 * 
 */
UCLASS()
class TRAINTRAGEDY_API AGameLevelBase : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void DoSomething();
	
public:
	UPROPERTY(BlueprintReadWrite, Category = LevelBlueprint)
	TArray<ATrackSegement*> Tracks;
};
