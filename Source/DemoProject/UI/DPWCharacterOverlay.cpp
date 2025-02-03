// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPWCharacterOverlay.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPWCharacterOverlay::SetHealth(const float HealthPercentage) const
{
	if(HealthBar)
	{
		HealthBar->SetPercent(HealthPercentage);
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPWCharacterOverlay::SetStamina(const float StaminaPercentage) const
{
	if(StaminaBar)
	{
		StaminaBar->SetPercent(StaminaPercentage);
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPWCharacterOverlay::ToggleComboImageVisibility(const bool bIsVisible) const
{
	ComboAlert->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
