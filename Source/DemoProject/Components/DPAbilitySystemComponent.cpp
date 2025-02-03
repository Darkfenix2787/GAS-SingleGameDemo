// This project belongs to Daniel Corredor, Use it only for study purposes.

#include "DPAbilitySystemComponent.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPAbilitySystemComponent::AbilityInputTagTrigger(const FGameplayTag& inputTag, const bool bValue)
{
    ABILITYLIST_SCOPE_LOCK();

    if (inputTag.IsValid())
    {
        for (FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
        {
            if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(inputTag)))
            {
                const bool bWasPressed = AbilitySpec.InputPressed;
                AbilitySpec.InputPressed = bValue;

                const bool bTryActivation = !AbilitySpec.IsActive() && (bValue);
                if (bTryActivation)
                {
                    TryActivateAbility(AbilitySpec.Handle);
                }
                else if (bWasPressed != AbilitySpec.InputPressed)
                {
                    const bool bSendServerEvents = (AbilitySpec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false);
                    if (AbilitySpec.InputPressed)
                    {
                        if (bSendServerEvents)
                        {
                            ServerSetInputPressed(AbilitySpec.Handle);
                        }

                        AbilitySpecInputPressed(AbilitySpec);
                        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
                    }
                    else
                    {
                        if (bSendServerEvents)
                        {
                            ServerSetInputReleased(AbilitySpec.Handle);
                        }

                        AbilitySpecInputReleased(AbilitySpec);
                        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
                    }
                }
            }
        }
    }
}
