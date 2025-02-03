// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "AbilitySystemComponent.h"
#include "DPAbilitySystemComponent.generated.h"

/**
 * Character's AbilitySystem Component
 */
UCLASS()
class DEMOPROJECT_API UDPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInputTagTrigger(const FGameplayTag& inputTag, const bool bValue);
	
};
