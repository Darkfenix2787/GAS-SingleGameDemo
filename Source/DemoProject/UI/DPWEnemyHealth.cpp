// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPWEnemyHealth.h"

#include "Components/ProgressBar.h"

void UDPWEnemyHealth::SetHealth(const float HealthPercentage) const
{
	HealthBar->SetPercent(HealthPercentage);
}
