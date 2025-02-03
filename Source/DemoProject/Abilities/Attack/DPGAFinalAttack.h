// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Attack/DPGAAttack.h"
#include "DPGAFinalAttack.generated.h"

/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPGAFinalAttack : public UDPGAAttack
{
	GENERATED_BODY()

public:
	
	virtual void BindComboTagCallbacks() override;
	virtual void OnComboTagAdded() override;	

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float AttackRadius = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float PushForce = 1500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float PushZDirection = 10.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float DamageAmount = 50.f;	

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UGameplayEffect> DamageEffect = nullptr;
	
};
