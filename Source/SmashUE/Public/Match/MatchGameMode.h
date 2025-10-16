// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"




class UInputMappingContext;

class AArenaPlayerStart;
class ASmashCharacter;
class USmashCharacterInputData;
UCLASS()
class SMASHUE_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
		virtual void BeginPlay() override;
private:
	void FindPlayerStartInArena(TArray<AArenaPlayerStart*>& ResultsActors);
	TSubclassOf<ASmashCharacter> GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;
	void SpawnCharacter(const TArray<AArenaPlayerStart*>& SpawnPoints);

	USmashCharacterInputData* LoadInputDataFromConfig();
	
	UInputMappingContext* LoadInputMappingContextFromConfig();

	void CreateAndInitPlayers() const;
	

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmashCharacter> SmashCharacterClassP0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmashCharacter> SmashCharacterClassP1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmashCharacter> SmashCharacterClassP2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASmashCharacter> SmashCharacterClassP3;

	UPROPERTY(EditAnywhere)
	TArray<ASmashCharacter*> CharactersInsideArena;
};
