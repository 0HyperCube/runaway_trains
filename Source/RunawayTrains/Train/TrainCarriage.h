// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <tuple>
#include "GameFramework/Actor.h"
#include <RunawayTrains\Track\TrackSegement.h>
#include "Components/BoxComponent.h"
#include "TrainCarriage.generated.h"


#define TrackSegementT ATrackSegement*

UCLASS()
class RUNAWAYTRAINS_API ATrainCarriage : public AActor
{
	GENERATED_BODY()

public:

	// Height in CM above spline
	UPROPERTY(EditDefaultsOnly)
		float Height = 200;

	// Speed in cm / second
	UPROPERTY(EditAnywhere)
		float Speed = 3000;
	
	// The segement of track on which the back bugie rests.
	UPROPERTY(EditAnywhere)
		ATrackSegement* BackSegement;

	UPROPERTY(EditAnywhere)
	bool BackIsBackwards = false;

	// The distance along the segment the back bugie rests.
	UPROPERTY(EditAnywhere)
		float BackDistance;


	UPROPERTY(EditAnywhere)
		ATrackSegement* FrontSegement;

	UPROPERTY(EditAnywhere)
	bool FrontIsBackwards = false;

	UPROPERTY(EditAnywhere)
		float FrontDistance;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UBoxComponent* CarriageCollider;

	UFUNCTION(BlueprintImplementableEvent)
	void FindPositionFromActorLocation();
	

	//UFUNCTION(BlueprintImplementableEvent)
	//	void Derail();
	

private:
	bool IsOnTrack = true;

	float CarrageLength;

	void Derail();

	
	
	FVector  LastLoc= FVector::ZeroVector;
	FVector MovementSpeed = FVector::ZeroVector;

public:
	// Sets default values for this actor's properties
	ATrainCarriage();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//// Move a distance along the track. When reaching the end of a track go to the next one.
	void UpdatePosition(ATrackSegement** segement, float* distance, float movement, bool* isBackwards);

	// When collides
	UFUNCTION(BlueprintCallable)
		void OnCompHit(const FHitResult& Hit);



	bool stopped = false;
};
