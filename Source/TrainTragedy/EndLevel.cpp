// Fill out your copyright notice in the Description page of Project Settings.



#include "Engine/World.h"
#include "EndLevel.h"
#include <TrainTragedy/TrainTragedyGameModeBase.h>
#include "Engine/Engine.h"

// Sets default values
AEndLevel::AEndLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (GetWorld()) {
		Cast<ATrainTragedyGameModeBase>(GetWorld()->GetAuthGameMode())->EndLevel = this;
	}

}

void AEndLevel::LoseLevel()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Loss!"));
	UGameplayStatics::SetGamePaused(this, true);
	EndLevelUI();
	LoseUI();
}

void AEndLevel::WinLevel()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Wyn!"));
	UGameplayStatics::SetGamePaused(this, true);
	EndLevelUI();
	WinUI();
}

