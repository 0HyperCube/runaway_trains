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

	UPROPERTY(EditAnywhere, Category="In Connector")
		ASegementConnector* InConnector = nullptr;

	UPROPERTY(EditAnywhere, Category = "In Connector")
		int16 InConnectorIndex = 0;

	UPROPERTY(EditAnywhere, Category = "In Connector")
		bool InConnectorIsIn = true;

	UPROPERTY(EditAnywhere, Category = "Out Connector")
		ASegementConnector* OutConnector = nullptr;

	UPROPERTY(EditAnywhere, Category = "Out Connector")
		int16 OutConnectorIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Out Connector")
		bool OutConnectorIsOut = true;

	void PlaceEnds();

	UFUNCTION(BlueprintImplementableEvent)
		void RedrawGraphics();

	ATrackSegement* GetInTrack();
	
	ATrackSegement* GetOutTrack();
};
