// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "TrackSegement.generated.h"

class ASegementConnector;

UCLASS()
class RUNAWAYTRAINS_API ATrackSegement : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrackSegement();


	virtual void OnConstruction(const FTransform& Transform);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere)
		ASegementConnector* InConnector = nullptr;

	UPROPERTY(EditAnywhere)
		bool InConnectorIsIn = true;

	UPROPERTY(EditAnywhere)
		ASegementConnector* OutConnector = nullptr;

	UPROPERTY(EditAnywhere)
		bool OutConnectorIsOut = true;

	void PlaceEnds();

	UFUNCTION(BlueprintImplementableEvent)
		void RedrawGraphics();

	ATrackSegement* GetInTrack();
	
	ATrackSegement* GetOutTrack();
};
