// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "GameFramework/Actor.h"
#include "SegementConnector.generated.h"

class UBoxComponent;
class ATrackSegement;
class USplineMeshComponent;
class USceneComponent;

UCLASS()
class RUNAWAYTRAINS_API ASegementConnector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASegementConnector();


	virtual void OnConstruction(const FTransform& Transform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USceneComponent* LocationComp;


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UBoxComponent* ChangePointsCollision;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USplineMeshComponent* DirectionArrow;

	UPROPERTY(EditAnywhere, Category = "Point Flow")
		TMap <int16, ATrackSegement*> InTracks = {};

	UPROPERTY(EditAnywhere, Category = "Point Flow")
		int InTrackIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Point Flow")
		TMap<int16, ATrackSegement*> OutTracks = {};

	UPROPERTY(EditAnywhere, Category = "Point Flow")
		int OutTrackIndex = 0;


	ATrackSegement* GetInTrack() { 
		if (InTracks.Num() < 1) { return nullptr; }
		return InTracks[InTrackIndex];
	};
	ATrackSegement* GetOutTrack() { 
		if (OutTracks.Num() < 1) { return nullptr; }
		return OutTracks[OutTrackIndex];
	}


	UFUNCTION(BlueprintCallable, Category = "Point Control")
	void ChangeDirection();

	void RemoveBadSplinePoints();

	void PlaceEndsOfTracks();

	void PlaceDirectionArrow();

	// Allow train to go in a different direction along a piece of track
	float FindNewDirection(float currentDirection, ATrackSegement* currentTrack);

private:
	float LerpAlpha = 1.001f;

	FVector InPosition;
	FVector InTangent;
	FVector OutPosition;
	FVector OutTangent;

	FVector OldInPosition;
	FVector OldInTangent;
	FVector OldOutPosition;
	FVector OldOutTangent;

	bool Initalised = false;

};
