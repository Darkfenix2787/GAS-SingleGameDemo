// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DPWCharacterOverlay.generated.h"

class UProgressBar;
class UImage;
/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPWCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	UImage* ComboAlert;

	void SetHealth(const float HealthPercentage) const;

	void SetStamina(const float StaminaPercentage) const;

	void ToggleComboImageVisibility(const bool bIsVisible) const;
	
};
