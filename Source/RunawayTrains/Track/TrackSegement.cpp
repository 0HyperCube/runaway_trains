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
	// Assigns the references to the connectors
	if (InConnector != nullptr) {
		if (InConnectorIsIn)
			InConnector->InTracks.Add(InConnectorIndex, this);
		else
			InConnector->OutTracks.Add(InConnectorIndex, this);
	}
	if (OutConnector != nullptr) {
		if (OutConnectorIsOut)
			OutConnector->OutTracks.Add(OutConnectorIndex, this);
		else
			OutConnector->InTracks.Add(OutConnectorIndex, this);
	}

	Super::BeginPlay();
	PlaceEnds();
}

void ATrackSegement::PlaceEnds()
{
	// Set the end points of the spline to the position of the connectors

	if (InConnector != nullptr) {
		int pointToChange = 0;
		SplineComponent->SetWorldLocationAtSplinePoint(pointToChange, InConnector->GetActorLocation());
		SplineComponent->UpdateSpline();
	}

	if (OutConnector != nullptr) {
		int pointToChange = SplineComponent->GetNumberOfSplinePoints() - 1;
		SplineComponent->SetWorldLocationAtSplinePoint(pointToChange, OutConnector->GetActorLocation());
		SplineComponent->UpdateSpline();
	}

	RedrawGraphics();
}

ATrackSegement* ATrackSegement::GetInTrack()
{
	if (OutConnector == nullptr)
		return nullptr;

	return OutConnectorIsOut ?
		OutConnector->GetInTrack():
		OutConnector->GetOutTrack();
}

ATrackSegement* ATrackSegement::GetOutTrack()
{
	
	if (InConnector == nullptr)
		return nullptr;

	return InConnectorIsIn ?
		InConnector->GetOutTrack():
		InConnector->GetInTrack();
	
}
