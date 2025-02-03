// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "DPAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDPAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDPAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UDPAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UDPAttributeSet, MaxStamina);

protected:

	// Function to clamp the attribute base value before it changes
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Function to clamp the attribute value before it changes
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// Function Called each Attribute reaches PreChange (Both Base and Current). Min and Max Clamps should happen.
	virtual void ClampAttributePreChange(const FGameplayAttribute& Attribute, float& NewValue) const;
};
