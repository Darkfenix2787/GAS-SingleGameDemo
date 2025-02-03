// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "EnhancedInputComponent.h"
#include "Inputs/DPInputConfig.h"

#include "DPEnhancedInputComponent.generated.h"

class UDPInputConfig;

/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	
	template<class UserClass, typename FuncType>
	void BindActionByTag(const UDPInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
	
	template<class UserClass, typename FuncType>
	void BindAbilityByTag(const UDPInputConfig* InputConfig, UserClass* Object, FuncType Func);
	

};

template<class UserClass, typename FuncType>
inline void UDPEnhancedInputComponent::BindActionByTag(const UDPInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	if (InputConfig && InputTag.IsValid())
	{
		if (const UInputAction* InputAction = InputConfig->FindInputActionForTag(InputTag))
		{
			BindAction(InputAction, TriggerEvent, Object, Func);
		}
	}
}

template<class UserClass, typename FuncType>
inline void UDPEnhancedInputComponent::BindAbilityByTag(const UDPInputConfig* InputConfig, UserClass* Object, FuncType Func)
{
	for (const FDPTaggedInput& Action : InputConfig->GetAbilityActions())
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (Func)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, Func, Action.InputTag, true);
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, Func, Action.InputTag, false);
			}
		}
	}
}
