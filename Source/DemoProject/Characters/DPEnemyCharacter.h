// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Characters/DPCharacter.h"
#include "Components/WidgetComponent.h"
#include "DPEnemyCharacter.generated.h"

class UWidgetComponent;
UCLASS()
class DEMOPROJECT_API ADPEnemyCharacter : public ADPCharacter
{
	GENERATED_BODY()

protected:

	ADPEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data) override;

	void UpdateHealthWidget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> EnemyHealthWidget;	
};