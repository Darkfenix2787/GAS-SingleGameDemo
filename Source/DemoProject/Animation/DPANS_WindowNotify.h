// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "DPANS_WindowNotify.generated.h"

/**
 * Default AnimNotifyState for the project
 */
UCLASS()
class DEMOPROJECT_API UDPANS_WindowNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	FGameplayTag ANSWindowTag;
	
};
