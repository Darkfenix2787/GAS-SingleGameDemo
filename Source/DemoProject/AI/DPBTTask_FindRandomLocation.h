// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "DPBTTask_FindRandomLocation.generated.h"

/**
 * AI Task to Find a random location
 */
UCLASS()
class DEMOPROJECT_API UDPBTTask_FindRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UDPBTTask_FindRandomLocation();

protected:

	UPROPERTY(EditAnywhere, Category = "Search")
	float SearchRadius = 5000.0f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
