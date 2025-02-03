// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "Abilities/DPAttributeSet.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	ClampAttributePreChange(Attribute, NewValue);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttributePreChange(Attribute, NewValue);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPAttributeSet::ClampAttributePreChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
}