// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPTApplyRootMotion_Dash.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/RootMotionSource.h"
#include "Characters/DPCharacter.h"
#include "Components/DPCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogDashTask);

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPTApplyRootMotion_Dash::UDPTApplyRootMotion_Dash(const FObjectInitializer& ObjectInitializer)
{
	bSetNewMovementMode = false;
	NewMovementMode = EMovementMode::MOVE_Walking;
	PreviousMovementMode = EMovementMode::MOVE_None;
	PreviousCustomMode = 0;
	bSimulatedTask = false;

	bEnableGravity = false;

	DashDirection = FVector::ZeroVector;
	DashStrength = 0.f;		
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPTApplyRootMotion_Dash* UDPTApplyRootMotion_Dash::ApplyRootMotionDash(UGameplayAbility* OwningAbility, FName TaskInstanceName, const FVector& inDashDirection, const float inDashStrength, const bool bInEndTaskOnImpact, const float inDuration, UCurveFloat* inStrengthOverTime, const bool bInEnableGravity, ERootMotionAccumulateMode inAccumulateMode, bool bInSetNewMovementMode, EMovementMode inMovementMode, ERootMotionFinishVelocityMode inVelocityOnFinishMode, FVector inSetVelocityOnFinish, float inClampVelocityOnFinish)
{
	UDPTApplyRootMotion_Dash* AbilityTask = NewAbilityTask<UDPTApplyRootMotion_Dash>(OwningAbility, TaskInstanceName);

	AbilityTask->ForceName = TaskInstanceName;
	AbilityTask->AccumulateMode = inAccumulateMode;
	AbilityTask->bSetNewMovementMode = bInSetNewMovementMode;
	AbilityTask->NewMovementMode = inMovementMode;
	AbilityTask->FinishVelocityMode = inVelocityOnFinishMode;
	AbilityTask->FinishSetVelocity = inSetVelocityOnFinish;
	AbilityTask->FinishClampVelocity = inClampVelocityOnFinish;
	AbilityTask->Duration = inDuration;
	AbilityTask->StrengthOverTime = inStrengthOverTime;
	AbilityTask->bEnableGravity = bInEnableGravity;
	AbilityTask->RootMotionSourceID = (uint16)ERootMotionSourceID::Invalid;

	AbilityTask->DashDirection = inDashDirection;
	AbilityTask->DashStrength = inDashStrength;	

	AbilityTask->SharedInitAndApply();	

	return AbilityTask;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPTApplyRootMotion_Dash::SharedInitAndApply()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC && ASC->AbilityActorInfo->MovementComponent.IsValid())
	{
		MovementComponent = Cast<UCharacterMovementComponent>(ASC->AbilityActorInfo->MovementComponent.Get());
		DPCharacterMovementComponent = Cast<UDPCharacterMovementComponent>(MovementComponent);		

		if (MovementComponent && DPCharacterMovementComponent.IsValid())
		{
			if (bSetNewMovementMode)
			{
				PreviousMovementMode = MovementComponent->MovementMode;
				PreviousCustomMode = MovementComponent->CustomMovementMode;
				MovementComponent->SetMovementMode(NewMovementMode);
			}

			ForceName = ForceName.IsNone() ? FName("RootMotionDash") : ForceName;
			RootMotionsource_Dash = MakeShared<FRootMotionSource_ConstantForce>();
			RootMotionsource_Dash->InstanceName = ForceName;
			RootMotionsource_Dash->AccumulateMode = AccumulateMode;
			RootMotionsource_Dash->Priority = 5;
			RootMotionsource_Dash->Force = DashDirection * DashStrength;
			RootMotionsource_Dash->Duration = Duration;
			RootMotionsource_Dash->StrengthOverTime = StrengthOverTime;
			RootMotionsource_Dash->FinishVelocityParams.Mode = FinishVelocityMode;
			RootMotionsource_Dash->FinishVelocityParams.SetVelocity = FinishSetVelocity;
			RootMotionsource_Dash->FinishVelocityParams.ClampVelocity = FinishClampVelocity;			

			if (bEnableGravity)
			{
				RootMotionsource_Dash->Settings.SetFlag(ERootMotionSourceSettingsFlags::IgnoreZAccumulate);
			}

			RootMotionSourceID = MovementComponent->ApplyRootMotionSource(RootMotionsource_Dash);			
		}
	}
	else
	{
		UE_LOG(LogDashTask, Warning, TEXT("%s called in Ability %s with null MovementComponent; Task Instance Name %s."),
			ANSI_TO_TCHAR(__FUNCTION__),
			Ability ? *Ability->GetName() : TEXT("NULL"),
			*InstanceName.ToString());
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPTApplyRootMotion_Dash::Activate()
{
	Super::Activate();
	SetWaitingOnAvatar();
	bTickingTask = true;	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPTApplyRootMotion_Dash::TickTask(float DeltaTime)
{	
	if (bIsFinished)
	{
		return;
	}

	Super::TickTask(DeltaTime);

	if (AActor* avatarActor = GetAvatarActor())
	{
		const bool bTimedOut = HasTimedOut();
		const bool bIsInfiniteDuration = Duration < 0.f;

		if ((!bIsInfiniteDuration && bTimedOut))
		{
			// Task has finished
			bIsFinished = true;
			if (!bIsSimulating)
			{
				if (ShouldBroadcastAbilityTaskDelegates())
				{
					OnFinish.Broadcast(bTimedOut,false);
				}
				EndTask();
			}
		}
	}
	else
	{
		bIsFinished = true;
		EndTask();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPTApplyRootMotion_Dash::OnDestroy(bool AbilityIsEnding)
{	
	if (DPCharacterMovementComponent.IsValid())
	{
		DPCharacterMovementComponent->RemoveRootMotionSourceByID(RootMotionSourceID);

		if (bSetNewMovementMode)
		{
			DPCharacterMovementComponent->SetMovementMode(PreviousMovementMode, PreviousCustomMode);
		}
	}
	else
	{
		UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
		if (ASC && ASC->AbilityActorInfo->MovementComponent.IsValid())
		{
			if (const auto movementComp = Cast<UCharacterMovementComponent>(ASC->AbilityActorInfo->MovementComponent))
			{
				movementComp->RemoveRootMotionSourceByID(RootMotionSourceID);
			}
		}
	}

	if (RootMotionsource_Dash.IsValid() && !RootMotionsource_Dash->Status.HasFlag(ERootMotionSourceStatusFlags::MarkedForRemoval))
	{
		RootMotionsource_Dash->Status.SetFlag(ERootMotionSourceStatusFlags::MarkedForRemoval);
	}

	RootMotionsource_Dash.Reset();

	Super::OnDestroy(AbilityIsEnding);
}