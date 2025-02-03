// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "DPBTTask_Attack.generated.h"

class UDPGameplayAbility;

UCLASS()
class DEMOPROJECT_API UDPBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UDPBTTask_Attack();

protected:

	UPROPERTY(EditAnywhere, Category = "Ability")
	TSubclassOf<UDPGameplayAbility> AbilityToActivate;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
