// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "GameFramework/HUD.h"
#include "GameplayEffectTypes.h"
#include "DPHUD.generated.h"

class UDPAttributeSet;

/**
 * Simple Character Hud 
 */

class UDPWCharacterOverlay;

UCLASS()
class DEMOPROJECT_API ADPHUD : public AHUD
{
	GENERATED_BODY()

protected:	

	virtual void BeginPlay() override;	

	/** Adds the HUD to player */
	void AddCharacterOverlay();

	void InitializeWidgets();

	// Attribute changed callbacks	
	void HealthChanged(const FOnAttributeChangeData& Data);
	void StaminaChanged(const FOnAttributeChangeData& Data);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDPWCharacterOverlay> CharacterOverlayWidgetClass = nullptr;
	
	TObjectPtr<UDPWCharacterOverlay> CharacterOverlay = nullptr;

	const TObjectPtr<UDPAttributeSet> HUDAttributeSet;

	// Change Attributes Delegates	
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;

public:

	/** Hud Setters */
	void SetHealth(const float Percent);

	void SetStamina(const float Percent);

	void ToggleComboImageVisibility(const bool bIsVisible) const;
};
