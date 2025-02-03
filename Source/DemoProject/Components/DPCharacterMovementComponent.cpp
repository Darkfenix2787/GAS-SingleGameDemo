// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPCharacterMovementComponent.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPCharacterMovementComponent::UDPCharacterMovementComponent()
{
	//Constructor
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPCharacterMovementComponent::SetAdditionalJumpZVelocity(const float AdditionalValue)
{
	JumpZVelocity += AdditionalValue;	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPCharacterMovementComponent::ClearAdditionalJumpZVelocity(const float AdditionalValue)
{
	JumpZVelocity -= AdditionalValue;
}
