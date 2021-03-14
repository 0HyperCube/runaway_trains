#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "SoundController.generated.h"

/*
 * This class handles the sounds of the birds and the trains
 */

UCLASS()
class RUNAWAYTRAINS_API ASoundController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UAudioComponent* EngineSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UAudioComponent* Ambience;

	// Is there a moving train in the level
	bool bIsTrain = true;

};
