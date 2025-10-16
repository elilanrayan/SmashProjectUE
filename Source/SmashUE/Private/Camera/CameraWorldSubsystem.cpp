// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraPosition(DeltaTime);
}

void UCameraWorldSubsystem::AddFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubsystem::RemoveFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	CameraMain->SetWorldLocation(CalculateAveragePositionBetweenTargets());
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector NewLocation = FVector::ZeroVector;
	for (AActor* FollowTarget : FollowTargets)
	{
		float CurrentX = FollowTarget->GetActorLocation().X;
		float CurrentZ = FollowTarget->GetActorLocation().Z;
		
		FVector CurrentLocation(CurrentX,0 ,CurrentZ );
		NewLocation += CurrentLocation;
		
	}
	 NewLocation /= FollowTargets.Num();
	NewLocation = FVector(NewLocation.X,CameraMain->GetOwner()->GetActorLocation().Y, NewLocation.Z);
	return  NewLocation;
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> Cameras; 
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag,Cameras);
	UCameraComponent* CameraComp = Cameras[0]->FindComponentByClass<UCameraComponent>();
	return CameraComp;
	
}

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain = FindCameraByTag(TEXT("CameraMain"));
}
