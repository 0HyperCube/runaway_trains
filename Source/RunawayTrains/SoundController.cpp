// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundController.h"

// Sets default values
ASoundController::ASoundController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EngineSound = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineSound"));
	Ambience = CreateDefaultSubobject<UAudioComponent>(TEXT("Ambience"));

	SetRootComponent(Root);
	EngineSound->SetupAttachment(Root);
	Ambience->SetupAttachment(Root);

	EngineSound->bAutoActivate = false;
	Ambience->bAutoActivate = false;

	Ambience->bIsUISound = true;
}

// Called when the game starts or when spawned
void ASoundController::BeginPlay()
{
	Super::BeginPlay();

	EngineSound->FadeIn(1, 1, 0, EAudioFaderCurve::Sin);
	Ambience->FadeIn(1, 1, 0, EAudioFaderCurve::Sin);
	
}

// Called every frame
void ASoundController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

