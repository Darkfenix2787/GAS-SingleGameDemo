// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPInputConfig.h"

#include "InputAction.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DPInputConfig)

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
bool FDPTaggedInput::IsValid() const
{
	return InputAction->IsValidLowLevelFast() && InputTag.IsValid();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
const UInputAction* UDPInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FDPTaggedInput& taggedInputAction : TaggedInputActions)
	{
		if (taggedInputAction.InputAction && taggedInputAction.InputTag == InputTag)
		{
			return taggedInputAction.InputAction;
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
TArray<const UInputAction*> UDPInputConfig::GetInputActions() const
{
	TArray<const UInputAction*> inputActions;

	for (const FDPTaggedInput& taggedInput : TaggedInputActions)
	{
		inputActions.Add(taggedInput.InputAction);
	}

	for (const FDPTaggedInput& taggedInput : AbilityInputActions)
	{
		inputActions.Add(taggedInput.InputAction);
	}

	inputActions.Shrink();

	return inputActions;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
TArray<FDPTaggedInput> UDPInputConfig::GetAbilityActions() const
{
	return AbilityInputActions;
}
