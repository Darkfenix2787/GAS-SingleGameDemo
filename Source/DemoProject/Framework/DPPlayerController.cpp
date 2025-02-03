// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "Framework/DPPlayerController.h"

#include "Abilities/DPAttributeSet.h"
#include "Characters/DPCharacter.h"
#include "Components/DPAbilitySystemComponent.h"
// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
const UDPAttributeSet* ADPPlayerController::GetAttributeSet()
{
	if (auto PlayerCharacter = Cast<ADPCharacter>(GetPawn()))
	{
		return PlayerCharacter->GetAttributeSet();
	}
	
	return nullptr;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPAbilitySystemComponent* ADPPlayerController::GetAbilitySystemComponent()
{
	if (const auto PlayerCharacter = Cast<ADPCharacter>(GetPawn()))
	{
		return Cast<UDPAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent());
	}
	
	return nullptr;
}
