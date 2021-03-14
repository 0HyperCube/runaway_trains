// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevel.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GetActors.h"
#include "SoundController.h"
#include "Train/TrainCarriage.h"

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
	EndLevel();
	LoseUI();
}

void AEndLevel::WinLevel()
{
	if (Ended) { return; }
	EndLevel();
	WinUI();
	
}

void AEndLevel::EndLevel()
{
	TArray<ASoundController*> out;
	FindAllActors(GetWorld(), out);
	for (ASoundController* var : out)
	{
		if (var->EngineSound->IsPlaying()) {
			var->EngineSound->FadeOut(1, 0, EAudioFaderCurve::Sin);
		}
	}


	EndLevelUI();
	Ended = true;
}

