// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "GameplayModMagnitudeCalculation.h"
#include "DPCostMagnitudeCalculation.generated.h"

/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPCostMagnitudeCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};
