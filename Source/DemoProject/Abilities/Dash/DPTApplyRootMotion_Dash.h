// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Abilities/Tasks/AbilityTask_ApplyRootMotion_Base.h"
#include "DPTApplyRootMotion_Dash.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDashTask, Log, All);

class UDPCharacterMovementComponent;
struct FRootMotionSource_ConstantForce;
enum class ERootMotionFinishVelocityMode : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FApplyRootMotionDashDelegate, bool, bTimedOut, bool, bBlockingImpact);
/**
 * Root motion dash class
 */
UCLASS()
class DEMOPROJECT_API UDPTApplyRootMotion_Dash : public UAbilityTask_ApplyRootMotion_Base
{
	GENERATED_BODY()

	TWeakObjectPtr<UDPCharacterMovementComponent> DPCharacterMovementComponent;

	TSharedPtr<FRootMotionSource_ConstantForce> RootMotionsource_Dash;

	ERootMotionAccumulateMode AccumulateMode;

	bool bSetNewMovementMode;

	TEnumAsByte<EMovementMode> NewMovementMode;

	EMovementMode PreviousMovementMode;

	uint8 PreviousCustomMode;

	float Duration;

	TObjectPtr<UCurveFloat> StrengthOverTime;

	bool bEnableGravity;

	FVector DashDirection = FVector::ZeroVector;

	float DashStrength = 0.f;	

public:

	UPROPERTY(BlueprintAssignable)
	FApplyRootMotionDashDelegate OnFinish;

	UDPTApplyRootMotion_Dash(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UDPTApplyRootMotion_Dash* ApplyRootMotionDash(UGameplayAbility* OwningAbility, FName TaskInstanceName,
		const FVector& inDashDirection, const float inDashStrength, const bool bInEndTaskOnImpact,
		const float inDuration, UCurveFloat* inStrengthOverTime, const bool bInEnableGravity,
		ERootMotionAccumulateMode inAccumulateMode, bool bInSetNewMovementMode, EMovementMode inMovementMode,
		ERootMotionFinishVelocityMode inVelocityOnFinishMode, FVector inSetVelocityOnFinish, float inClampVelocityOnFinish);

	virtual void SharedInitAndApply() override;	
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool AbilityIsEnding) override;
	
};
