// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPHUD.h"

#include "Characters/DPCharacter.h"
#include "Abilities/DPAttributeSet.h"
#include "Components/DPAbilitySystemComponent.h"
#include "Framework/DPPlayerController.h"
#include "UI/DPWCharacterOverlay.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::BeginPlay()
{
	Super::BeginPlay();

	AddCharacterOverlay();
	InitializeWidgets();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::AddCharacterOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if(PlayerController && CharacterOverlayWidgetClass)
	{
		CharacterOverlay = CreateWidget<UDPWCharacterOverlay>(PlayerController, CharacterOverlayWidgetClass);
		CharacterOverlay->AddToViewport();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::InitializeWidgets()
{
	if (auto PlayerController = Cast<ADPPlayerController>(GetOwningPlayerController()))
	{
		auto PlayerASC = PlayerController->GetAbilitySystemComponent();
		const auto AttributeSet = PlayerController->GetAttributeSet(); 		
		if (PlayerASC && AttributeSet)
		{
			//Bind Delegates
			HealthChangedDelegateHandle = PlayerASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ADPHUD::HealthChanged);
			StaminaChangedDelegateHandle = PlayerASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &ADPHUD::StaminaChanged);

			// Set Initial Values to Health and Stamina
			if (AttributeSet->GetMaxHealth() != 0)
			{
				SetHealth(AttributeSet->GetHealth() / AttributeSet->GetMaxHealth());
			}

			if (AttributeSet->GetMaxStamina() != 0)
			{
				SetStamina(AttributeSet->GetStamina() / AttributeSet->GetMaxStamina());
			}
		}
	}

	ToggleComboImageVisibility(false);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::HealthChanged(const FOnAttributeChangeData& Data)
{	
	if (auto PlayerController = Cast<ADPPlayerController>(GetOwningPlayerController()))
	{
		if (const auto AttributeSet = PlayerController->GetAttributeSet())
		{
			SetHealth(Data.NewValue/AttributeSet->GetMaxHealth());
		}			
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::StaminaChanged(const FOnAttributeChangeData& Data)
{
	if (auto PlayerController = Cast<ADPPlayerController>(GetOwningPlayerController()))
	{
		if (const auto AttributeSet = PlayerController->GetAttributeSet())
		{
			SetStamina(Data.NewValue/AttributeSet->GetMaxStamina());
		}			
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::SetHealth(const float Percent)
{
	CharacterOverlay->SetHealth(Percent);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::SetStamina(const float Percent)
{
	CharacterOverlay->SetStamina(Percent);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPHUD::ToggleComboImageVisibility(const bool bIsVisible) const
{
	CharacterOverlay->ToggleComboImageVisibility(bIsVisible);
}
