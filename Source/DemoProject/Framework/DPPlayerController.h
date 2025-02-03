// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DPPlayerController.generated.h"

class ADPHUD;
class UDPAbilitySystemComponent;
class UDPAttributeSet;

UCLASS()
class DEMOPROJECT_API ADPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UDPAbilitySystemComponent* GetAbilitySystemComponent();

	const UDPAttributeSet* GetAttributeSet();	
};
