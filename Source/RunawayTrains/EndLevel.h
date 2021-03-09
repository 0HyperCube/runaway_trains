// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "EndLevel.generated.h"

UCLASS()
class RUNAWAYTRAINS_API AEndLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	

	// Sets default values for this actor's properties
	AEndLevel();

	
	UFUNCTION(BlueprintCallable)
	void LoseLevel();

	UFUNCTION(BlueprintCallable)
	void WinLevel();

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Level End"))
		void EndLevelUI();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Win"))
		void WinUI();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Lose"))
		void LoseUI();

private:
	bool Ended;

};
