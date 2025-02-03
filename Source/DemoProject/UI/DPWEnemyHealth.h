// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DPWEnemyHealth.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPWEnemyHealth : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;

	void SetHealth(const float HealthPercentage) const;
};
