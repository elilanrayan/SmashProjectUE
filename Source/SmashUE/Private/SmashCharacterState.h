// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SmashCharacterState.generated.h"


class USmashCharacterStateMachine;
class ASmashCharacter;
class USmashCharacterSettings;
class UCharacterMovementComponent;
enum class ESmashCharacterStateID : uint8;
UCLASS(Abstract)
class SMASHUE_API USmashCharacterState : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USmashCharacterState();

	virtual ESmashCharacterStateID GetStateID();
	
	virtual void StateInit(USmashCharacterStateMachine* InState);

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID);
	
	virtual void StateExit(ESmashCharacterStateID NextStateID);

	virtual void StateTick(float Deltatime);

	protected:
	UPROPERTY()
	TObjectPtr<ASmashCharacter> Character;

	UPROPERTY()
	TObjectPtr<USmashCharacterStateMachine> StateMachine;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

	//UPROPERTY()
	//TObjectPtr<USmashCharacterSettings> Settings;
};
