// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SegementConnector.generated.h"

class ATrackSegement;

UCLASS()
class TRAINTRAGEDY_API ASegementConnector : public AActor
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


	UPROPERTY(EditAnywhere, Category = "Point Flow")
		TArray<ATrackSegement*> InTracks = { nullptr };

	UPROPERTY(EditAnywhere, Category = "Point Flow")
		int InTrackIndex = 0;

	UPROPERTY(EditAnywhere)
		TArray<ATrackSegement*> OutTracks = { nullptr };

	UPROPERTY(EditAnywhere, Category = "Point Flow")
		int OutTrackIndex = 0;


	ATrackSegement* GetInTrack() { return InTracks[InTrackIndex]; };
	ATrackSegement* GetOutTrack() { return OutTracks[OutTrackIndex]; }


	UFUNCTION(BlueprintCallable, Category = "Point Control")
	void ChangeDirection();

	void RemoveBadSplinePoints();

	void PlaceEndsOfTracks();

};
