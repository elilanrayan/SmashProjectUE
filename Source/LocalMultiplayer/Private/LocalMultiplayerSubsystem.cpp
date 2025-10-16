// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSubsystem.h"

#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayTypes.h"
#include "LocalMultiplayerSettings.h"
#include "Kismet/GameplayStatics.h"



void ULocalMultiplayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	MultiSettings = GetMutableDefault<ULocalMultiplayerSettings>();
}


void ULocalMultiplayerSubsystem::CreateAndInitPlayers(ELocalMultiplayerInputMappingType MappingType)
{

	for (int i = 1; i < MultiSettings->GetNbKeyboardProfiles(); i++)
	{
		APlayerController* NewController = UGameplayStatics::CreatePlayer(GetWorld(),i,true);
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	if (!PlayerIndexFromKeyboardProfileIndex.Contains(KeyboardProfileIndex))
	{
		return -1;
	}
	return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	 const uint8 CurrentIndex=LastAssignedPlayerIndex;
	PlayerIndexFromKeyboardProfileIndex.Add(KeyboardProfileIndex,CurrentIndex );
	LastAssignedPlayerIndex++;
	return CurrentIndex;
	
}

void ULocalMultiplayerSubsystem::AssignKeyboardMapping(int PlayerIndex, int KeyboardProfileIndex,ELocalMultiplayerInputMappingType MappingType) const
{
	APlayerController* LocalController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
	if (MultiSettings->GetNbKeyboardProfiles()<KeyboardProfileIndex+1)
	{
		return;
	}
	FLocalMultiplayerProfileData KeyboardProfileData = MultiSettings->KeyboardProfilesData[KeyboardProfileIndex];
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalController->GetLocalPlayer());
	FModifyContextOptions Options;
	Options.bForceImmediately = true;
	Subsystem->AddMappingContext(KeyboardProfileData.GetIMCFromType(MappingType),0, Options);
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceID)
{
	if (!PlayerIndexFromGamepadProfileIndex.Contains(DeviceID))
	{
		return -1;
	}
	return PlayerIndexFromGamepadProfileIndex[DeviceID];
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToGamepadDeviceID(int DeviceID)
{
	const uint8 CurrentIndex=LastAssignedPlayerIndex;
	PlayerIndexFromKeyboardProfileIndex.Add(DeviceID,CurrentIndex );
	LastAssignedPlayerIndex++;
	return CurrentIndex;
}

void ULocalMultiplayerSubsystem::AssignGamepadInputMapping(int PlayerIndex,ELocalMultiplayerInputMappingType MappingType) const
{
	if (MultiSettings->NbMaxGamepads<=0)
	{
		return;
	}
	FModifyContextOptions Options;
	Options.bForceImmediately = true;
	APlayerController* LocalController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
	FLocalMultiplayerProfileData GamePadProfileData = MultiSettings->GamepadProfileData;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalController->GetLocalPlayer());
	Subsystem->AddMappingContext(GamePadProfileData.GetIMCFromType(MappingType),0,Options);
	
}

