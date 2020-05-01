// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "TrackNode.generated.h"

/**
 * 
 */
UCLASS()
class TRAINTRAGEDY_API ATrackNode : public ATargetPoint
{
	GENERATED_BODY()
	
public:
	ATrackNode* NextTrack = nullptr;
	ATrackNode* PreviousTrack = nullptr;
};
