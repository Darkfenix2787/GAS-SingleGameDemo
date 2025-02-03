// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPEnemyCharacter.h"

#include "Abilities/DPAttributeSet.h"
#include "Components/DPAbilitySystemComponent.h"
#include "UI/DPWEnemyHealth.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
ADPEnemyCharacter::ADPEnemyCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	EnemyHealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	EnemyHealthWidget->SetupAttachment(RootComponent);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateHealthWidget();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPEnemyCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	UpdateHealthWidget();
	Super::HealthChanged(Data);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPEnemyCharacter::UpdateHealthWidget()
{
	if (AbilitySystemComponent)
	{
		if (const UDPAttributeSet* AttributeSet = Cast<UDPAttributeSet>(AbilitySystemComponent->GetAttributeSet(UDPAttributeSet::StaticClass())))
		{
			const float CurrentHealth = AttributeSet->GetHealth();
			const float MaxHealth = AttributeSet->GetMaxHealth();

			auto HealthWidget = Cast<UDPWEnemyHealth>( EnemyHealthWidget->GetWidget());

			if (HealthWidget && MaxHealth != 0)
			{
				HealthWidget->SetHealth(CurrentHealth / MaxHealth);
			}
		}
	}
}

