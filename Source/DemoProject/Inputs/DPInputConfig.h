// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "DPInputConfig.generated.h"

class UInputAction;

USTRUCT()
struct FDPTaggedInput
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "Input"))
	FGameplayTag InputTag;
	
	bool IsValid() const;
};


UCLASS(Const)
class DEMOPROJECT_API UDPInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag) const;

	
	TArray<const UInputAction*> GetInputActions() const;

	
	TArray<FDPTaggedInput> GetAbilityActions() const;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", Meta = (TitleProperty = "InputAction"))
	TArray<FDPTaggedInput> TaggedInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", Meta = (TitleProperty = "InputAction"))
	TArray<FDPTaggedInput> AbilityInputActions;
	
};
