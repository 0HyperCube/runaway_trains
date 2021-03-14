#include "PlayerPawn.h"
#include "Components/InputComponent.h"


#include "Engine/World.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	

	InputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &APlayerPawn::SelectPoints);

}

void APlayerPawn::SelectPoints()
{
    UE_LOG(LogTemp, Warning, TEXT("You clicked!"));
    // get the camera transform
    FVector CameraLoc;
    FRotator CameraRot;
    GetActorEyesViewPoint(CameraLoc, CameraRot);

    FVector Start = CameraLoc;
    FVector End = CameraLoc + (CameraRot.Vector() * MAX_int32);

    FHitResult HitResult;
    

    //  do the line trace
    bool DidTrace = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, FCollisionObjectQueryParams::AllObjects);

    if (DidTrace)
        UE_LOG(LogTemp, Warning, TEXT("You clicked on a % s at pos (% d,% d,% d )"));
    //, AActor::GetDebugName(HitResult.GetActor()), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z
}

