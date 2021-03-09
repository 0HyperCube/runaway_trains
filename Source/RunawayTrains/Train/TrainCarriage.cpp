// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainCarriage.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "RunawayTrains/EndLevel.h"
#include <RunawayTrains/RunawayTrainsGameModeBase.h>
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

// Sets default values
ATrainCarriage::ATrainCarriage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CarriageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(CarriageCollider);
	CarriageCollider->SetNotifyRigidBodyCollision(true);
	CarriageCollider->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
}

void ATrainCarriage::Derail()
{
	if (IsOnTrack) {
		IsOnTrack = false;
		CarriageCollider->SetEnableGravity(true);
		CarriageCollider->AddImpulse(MovementSpeed, NAME_None, true);

		auto world = GetWorld();
		auto GameMode = world->GetAuthGameMode();
		if (GameMode) {
			
			auto MyGameMode = Cast<ARunawayTrainsGameModeBase>(GameMode);
			if (MyGameMode) {
				if (MyGameMode->EndLevel) {
					MyGameMode->EndLevel->LoseLevel();
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ATrainCarriage::BeginPlay()
{
	Super::BeginPlay();

	// if not on track to start with
	if (!(BackSegement)) {
		Derail();
		return;
	}
	else {
		
	}
	
}

// Called every frame
void ATrainCarriage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (stopped) { return; }

	if (IsOnTrack) {

		UpdatePosition(&BackSegement, &BackDistance, (Speed * DeltaTime), &BackIsBackwards);
		FVector BackLoc = BackSegement->SplineComponent->GetLocationAtDistanceAlongSpline(BackDistance, ESplineCoordinateSpace::World);
		DrawDebugPoint(GetWorld(), BackLoc, 5, FColor(52, 220, 239), false);

		UpdatePosition(&FrontSegement, &FrontDistance, (Speed * DeltaTime), &FrontIsBackwards);
		FVector FrontLoc = FrontSegement->SplineComponent->GetLocationAtDistanceAlongSpline(FrontDistance, ESplineCoordinateSpace::World);
		DrawDebugPoint(GetWorld(), FrontLoc, 5, FColor(52, 220, 239), false);

		LastLoc = GetActorLocation();
		SetActorLocation((BackLoc + FrontLoc) / 2 + FVector(0, 0, Height));
		MovementSpeed = (GetActorLocation() - LastLoc) / DeltaTime;

		SetActorRotation((BackLoc - FrontLoc).Rotation());

		if (FVector::Dist(BackLoc, FrontLoc) > 1400) {
			Derail();
		}
	}
	
}

void ATrainCarriage::UpdatePosition(ATrackSegement** segement, float* distance, float movement, bool* isBackwards)
{
	if (stopped) { return; }

	*distance += movement;// *(*isBackwards) ? -1 : 1;

	float currentLen = (*segement)->SplineComponent->GetSplineLength();

	int i = 0;

	while (*distance > currentLen || *distance < 0) {
		if (stopped) { return; }

		if (*distance > currentLen) {

			if ((*segement)->GetInTrack() == nullptr) {
				Derail();
				return;
			}
			else {
				*distance -= currentLen;
				(*segement) = (*segement)->GetInTrack();
			}
				
				
			
		}
		else {
			stopped = true;
		}
		currentLen = (*segement)->SplineComponent->GetSplineLength();

		i++;
		if (i > 10) {
			stopped = true; 
			//UGameplayStatics::SetGamePaused(GetWorld(), true);
			return; 
		}
	}
	return;
}

void ATrainCarriage::OnCompHit(const FHitResult& Hit)
{

	if ((Hit.Actor != NULL) && (Hit.Actor != this) && (Hit.Component != NULL) && (Hit.Actor->IsA<ATrainCarriage>()))
	{
		Cast<ATrainCarriage>(Hit.Actor)->Derail();
		Derail();
	}
	
}