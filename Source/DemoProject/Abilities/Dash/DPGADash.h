// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Abilities/DPGameplayAbility.h"
#include "DPGADash.generated.h"

class UDPTApplyRootMotion_Dash;

/**
 * GameplayAbility Dash Class
 */
UCLASS()
class DEMOPROJECT_API UDPGADash : public UDPGameplayAbility
{
	GENERATED_BODY()

public:

	UDPGADash();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UFUNCTION()
	void OnTaskFinished(bool bTimedOut, bool bBlockingImpact);

private:

	UPROPERTY()
	TObjectPtr<UDPTApplyRootMotion_Dash> DashAbilityTask = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DashStrenght = 2000.f;

	UPROPERTY(EditDefaultsOnly)
	float DashDuration = 1.f;
	
};
