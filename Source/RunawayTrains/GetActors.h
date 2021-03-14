#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// A utility function to find actors
template<typename T>
inline void FindAllActors(UWorld* World, TArray<T*>& Out)
{
    for (TActorIterator<T> It(World); It; ++It)
    {
        Out.Add(*It);
    }
}
