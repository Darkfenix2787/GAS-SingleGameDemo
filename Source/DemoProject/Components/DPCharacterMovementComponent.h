// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DPCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()	

public:

	UDPCharacterMovementComponent();

	UFUNCTION(BlueprintCallable, Category = "CharacterMovement")
	void SetAdditionalJumpZVelocity(const float AdditionalValue);

	UFUNCTION(BlueprintCallable, Category = "CharacterMovement")
	void ClearAdditionalJumpZVelocity(const float AdditionalValue);	
	
};
