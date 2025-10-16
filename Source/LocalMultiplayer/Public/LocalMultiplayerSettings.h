// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DeveloperSettings.h"
#include "LocalMultiplayerSettings.generated.h"

/**
 * 
 */

class UInputMappingContext;

UENUM()
enum class ELocalMultiplayerInputMappingType
{
	InGame,
	Menu
};


USTRUCT()
struct FLocalMultiplayerProfileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ProfileName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> IMCInGame;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> IMCInMenu;

	bool ContainsKey(const FKey& Key, ELocalMultiplayerInputMappingType MappingType) const;

	UInputMappingContext* GetIMCFromType( ELocalMultiplayerInputMappingType MappingType) const;
	
};

UCLASS(Config=Game, DefaultConfig,meta=(DisplayName= "Local Multiplayer Settings"))
class LOCALMULTIPLAYER_API ULocalMultiplayerSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere,Config,Category="Local Multiplayer Settings")
	TArray<FLocalMultiplayerProfileData> KeyboardProfilesData;

	int GetNbKeyboardProfiles() const;

	int FindKeyboardProfileIndexFromKey(const FKey& Key,ELocalMultiplayerInputMappingType InputMapping) const;

	UPROPERTY(Config,EditAnywhere,Category="Local Multiplayer")
	FLocalMultiplayerProfileData GamepadProfileData;

	UPROPERTY(Config,EditAnywhere,Category="Local Multiplayer")
	int NbMaxGamepads = 4;
};



