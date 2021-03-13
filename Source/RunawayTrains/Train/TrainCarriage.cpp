// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainCarriage.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
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
	// changes current distance
	float mul = (*isBackwards) ? -1.f : 1.f;
	*distance += movement * mul;

	// Get len of current segement
	float currentLen = (*segement)->SplineComponent->GetSplineLength();

	while (*distance > currentLen || *distance < 0) {
		// If gone over the end of the track
		if (*distance > currentLen) {

			// If no more tracks in this direction
			if ((*segement)->GetInTrack() == nullptr) {
				Derail();
				return;
			}
			else {
				// If the train should keep going in the same direction
				if ((*segement)->OutConnectorIsOut && ((*segement)->GetInTrack()->OutConnectorIsOut || (*segement)->GetInTrack()->InConnector==(*segement)->OutConnector)) {
					*distance -= currentLen;
					(*segement) = (*segement)->GetInTrack();
				}
				// Reverse the train's direction
				else {
					*distance -= currentLen;
					(*segement) = (*segement)->GetInTrack();
					currentLen = (*segement)->SplineComponent->GetSplineLength();
					*distance = currentLen -*distance;
					*isBackwards = !*isBackwards;
				}
			}
		}
		// If gone over the start of the track
		else {
			// If no more tracks in this direction
			if ((*segement)->GetOutTrack() == nullptr) {
				Derail();
				return;
			}
			// Go to next track
			else {
				(*segement) = (*segement)->GetOutTrack();
				currentLen = (*segement)->SplineComponent->GetSplineLength();
				*distance += currentLen;
			}
		}
		currentLen = (*segement)->SplineComponent->GetSplineLength();
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