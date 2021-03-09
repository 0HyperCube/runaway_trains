// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevel.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
AEndLevel::AEndLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//if (GetWorld()) {
	//	Cast<ARunawayTrainsGameModeBase>(GetWorld()->GetAuthGameMode())->EndLevel = this;
	//}
	Ended = false;

}

void AEndLevel::LoseLevel()
{
	if (Ended) { return; }

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Loss!"));
	EndLevelUI();
	LoseUI();
	Ended = true;
}

void AEndLevel::WinLevel()
{
	if (Ended) { return; }

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Wyn!"));
	EndLevelUI();
	WinUI();
	Ended = true;
}

