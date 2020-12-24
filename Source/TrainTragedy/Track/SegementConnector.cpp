// Fill out your copyright notice in the Description page of Project Settings.

#include "SegementConnector.h"
#include "TrackSegement.h"


// Sets default values
ASegementConnector::ASegementConnector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("PointCollision"));
	SetRootComponent(LocationComp);

	ChangePointsCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PointCollision"));
	ChangePointsCollision->AttachToComponent(LocationComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ChangePointsCollision->SetCollisionProfileName("PointTrigger");
	ChangePointsCollision->SetBoxExtent(FVector(500, 500, 100));
	ChangePointsCollision->SetRelativeLocation(FVector(1000, 0, 0));

}

void ASegementConnector::OnConstruction(const FTransform& Transform)
{
	RemoveBadSplinePoints();
	PlaceEndsOfTracks();
}

// Called when the game starts or when spawned
void ASegementConnector::BeginPlay()
{
	Super::BeginPlay();

	RemoveBadSplinePoints();
	
}

// Called every frame
void ASegementConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASegementConnector::ChangeDirection()
{
	InTrackIndex += 1;
	InTrackIndex = InTrackIndex % InTracks.Num();

	OutTrackIndex += 1;
	OutTrackIndex = OutTrackIndex % OutTracks.Num();
}

void ASegementConnector::RemoveBadSplinePoints()
{
	for (int i = 0; i < OutTracks.Num(); i++) {
		ATrackSegement* track = OutTracks[i];
		if (track == nullptr || track->OutConnector != this) {
			OutTracks.RemoveAt(i);
			i -= 1;
		}
	}

	for (int i = 0; i < InTracks.Num(); i++) {
		ATrackSegement* track = InTracks[i];
		if (track == nullptr || track->InConnector != this) {
			InTracks.RemoveAt(i);
			i -= 1;
		}
	}

}

void ASegementConnector::PlaceEndsOfTracks()
{

	for (ATrackSegement* Track : InTracks) {
		Track->PlaceEnds();
	}

	for (ATrackSegement* Track : OutTracks) {
		Track->PlaceEnds();
	}
}

