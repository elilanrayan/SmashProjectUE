// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateWalk.generated.h"


UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateWalk : public USmashCharacterState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USmashCharacterStateWalk();
	virtual ESmashCharacterStateID GetStateID() override;

	UFUNCTION()
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;

	UFUNCTION()
	void OnInputMoveXFast(float InputMoveXFast);

	UFUNCTION()
	void OnInputJump(bool isJumping);

	UFUNCTION()
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;

	virtual void StateTick(float Deltatime) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AnimMontageWalk;

	UPROPERTY(EditAnywhere)
	float MaxWalkSpeed;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
