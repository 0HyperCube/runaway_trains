// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackSegement.h"
#include "SegementConnector.h"

// Sets default values
ATrackSegement::ATrackSegement()
{


	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	SetRootComponent(SplineComponent);

	


}

void ATrackSegement::OnConstruction(const FTransform& Transform)
{
	PlaceEnds();

	if (InConnector != nullptr) {
		InConnector->RemoveBadSplinePoints();
	}

	if (OutConnector != nullptr) {
		OutConnector->RemoveBadSplinePoints();
	}

}

void ATrackSegement::BeginPlay()
{
	Super::BeginPlay();
	PlaceEnds();
	
	
}

void ATrackSegement::PlaceEnds()
{
	// checking connectors

	if (InConnector != nullptr) {
		int pointToChange = 0;
		SplineComponent->SetWorldLocationAtSplinePoint(pointToChange, InConnector->GetActorLocation());
		SplineComponent->UpdateSpline();
		InConnector->InTracks.AddUnique(this);
	}

	if (OutConnector != nullptr) {
		int pointToChange = SplineComponent->GetNumberOfSplinePoints() - 1;
		SplineComponent->SetWorldLocationAtSplinePoint(pointToChange, OutConnector->GetActorLocation());
		SplineComponent->UpdateSpline();
		OutConnector->OutTracks.AddUnique(this);
	}

	RedrawGraphics();
}

ATrackSegement* ATrackSegement::GetInTrack()
{
	if (OutConnector == nullptr)
		return nullptr;
	return OutConnector->GetInTrack();
}

ATrackSegement* ATrackSegement::GetOutTrack()
{
	
	if (InConnector == nullptr)
		return nullptr;
	return InConnector->GetOutTrack();
	
}
