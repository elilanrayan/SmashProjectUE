// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SmashCharacterStateMachine.generated.h"
class ASmashCharacter;
class USmashCharacterState;
/**
 * 
 */
UCLASS()
class SMASHUE_API USmashCharacterStateMachine : public UObject
{
	GENERATED_BODY()
	public:
	void Init(ASmashCharacter* InCharacter);
	ASmashCharacter* GetCharacter() const;

	protected:
	UPROPERTY()
	TObjectPtr<ASmashCharacter> Character;
	UPROPERTY()
	TArray<USmashCharacterState*> AllStates;

	void FindStates();
	void InitStates();
	
};
