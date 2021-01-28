// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainCarriage.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
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

		UpdatePosition(&BackSegement, &BackDistance, Speed * DeltaTime);
		FVector BackLoc = BackSegement->SplineComponent->GetLocationAtDistanceAlongSpline(BackDistance, ESplineCoordinateSpace::World);
		DrawDebugPoint(GetWorld(), BackLoc, 5, FColor(52, 220, 239), false);


		UpdatePosition(&FrontSegement, &FrontDistance, Speed * DeltaTime);
		FVector FrontLoc = FrontSegement->SplineComponent->GetLocationAtDistanceAlongSpline(FrontDistance, ESplineCoordinateSpace::World);
		DrawDebugPoint(GetWorld(), FrontLoc, 5, FColor(52, 220, 239), false);

		LastLoc = GetActorLocation();
		SetActorLocation((BackLoc + FrontLoc) / 2 + FVector(0, 0, 300));
		MovementSpeed = (GetActorLocation() - LastLoc) / DeltaTime;

		SetActorRotation((BackLoc - FrontLoc).Rotation());

		if (FVector::Dist(BackLoc, FrontLoc) > 1400) {
			Derail();
		}
	}
	
}

void ATrainCarriage::UpdatePosition(ATrackSegement** segement, float* distance, float movement)
{
	*distance += movement;
	while (*distance > (*segement)->SplineComponent->GetSplineLength()) {
		if ((*segement)->GetInTrack()==nullptr) {
			Derail();
			return;
		}
		else {
			*distance -= (*segement)->SplineComponent->GetSplineLength();
			*distance += movement;
			*segement = (*segement)->GetInTrack();
		}
	}

	while (*distance < 0) {
		if ((*segement)->GetOutTrack() == nullptr) {
			Derail();
			return;
		}
		else {
			*distance += movement;
			*segement = (*segement)->GetOutTrack();
			*distance += (*segement)->SplineComponent->GetSplineLength();
		}
	}
}

void ATrainCarriage::OnCompHit(const FHitResult& Hit)
{

	if ((Hit.Actor != NULL) && (Hit.Actor != this) && (Hit.Component != NULL) && (Hit.Actor->IsA<ATrainCarriage>()))
	{
		Cast<ATrainCarriage>(Hit.Actor)->Derail();
		Derail();
	}
	
}