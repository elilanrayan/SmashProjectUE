// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSettings.h"

#include "InputMappingContext.h"

#pragma region Structs
bool FLocalMultiplayerProfileData::ContainsKey(const FKey& Key, ELocalMultiplayerInputMappingType MappingType) const
{
	switch (MappingType)
	{
	case ELocalMultiplayerInputMappingType::InGame :
		for (FEnhancedActionKeyMapping keyMap :IMCInGame->GetMappings())
		{
			if (Key == keyMap.Key)
			{
				return true;
			}
		}
		break;
	
	case ELocalMultiplayerInputMappingType::Menu :
		for (FEnhancedActionKeyMapping keyMap :IMCInGame->GetMappings())
		{
			if (Key == keyMap.Key)
			{
				return true;
			}
		}
		break;
	}
	return false;
}

UInputMappingContext* FLocalMultiplayerProfileData::GetIMCFromType(ELocalMultiplayerInputMappingType MappingType) const
{
	switch (MappingType)
	{
		case ELocalMultiplayerInputMappingType::InGame :
		return IMCInGame;
		case ELocalMultiplayerInputMappingType::Menu :
		return IMCInMenu;
	}
	return nullptr;
}

#pragma endregion Structs


#pragma region Class
int ULocalMultiplayerSettings::GetNbKeyboardProfiles() const
{
	return KeyboardProfilesData.Num();
}

int ULocalMultiplayerSettings::FindKeyboardProfileIndexFromKey(const FKey& Key,ELocalMultiplayerInputMappingType InputMapping) const
{
	for (int i = 0; i < GetNbKeyboardProfiles(); i++)
	{
		if (KeyboardProfilesData[i].ContainsKey(Key,InputMapping))
		{
			return i;
		}
	}
	return -1;
}
#pragma endregion Class