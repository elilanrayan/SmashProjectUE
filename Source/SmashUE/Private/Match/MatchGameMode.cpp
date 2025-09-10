// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/MatchGameMode.h"

#include "SmashCharacter.h"
#include "Arena/ArenaPlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMatchGameMode::FindPlayerStartInArena(TArray<AArenaPlayerStart*>& ResultsActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AArenaPlayerStart::StaticClass(),FoundActors);

	for ( int i = 0; i < FoundActors.Num(); i++)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart>(FoundActors[i]);
		if (ArenaPlayerStartActor==nullptr) continue;

		ResultsActors.Add(ArenaPlayerStartActor);
	}
}

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AArenaPlayerStart*> PlayerStartsPoints;
	FindPlayerStartInArena(PlayerStartsPoints);

	for (AArenaPlayerStart* PlayerStartActor : PlayerStartsPoints)
	{
		EAutoReceiveInput::Type InputType = PlayerStartActor->AutoReceiveInput.GetValue();
		TSubclassOf<ASmashCharacter> SmashCharacterClass = GetSmashCharacterClassFromInputType(InputType);
		if (SmashCharacterClass == nullptr) continue;
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red,SmashCharacterClass->GetFName().ToString());
		
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red,PlayerStartActor->GetFName().ToString());
	}
}

TSubclassOf<ASmashCharacter> AMatchGameMode::GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const
{
	switch (InputType)
	{
	case EAutoReceiveInput::Player0:
		return SmashCharacterClassP0;
		
	case EAutoReceiveInput::Player1:
		return SmashCharacterClassP1;

	case EAutoReceiveInput::Player2:
		return SmashCharacterClassP2;

	case EAutoReceiveInput::Player3:
		return SmashCharacterClassP3;

	default:
		return nullptr;
		
	}
	
}

