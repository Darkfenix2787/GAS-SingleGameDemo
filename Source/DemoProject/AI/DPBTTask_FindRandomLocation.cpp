// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPBTTask_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPBTTask_FindRandomLocation::UDPBTTask_FindRandomLocation()
{
	NodeName = "Find Random Location";
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
EBTNodeResult::Type UDPBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (auto AIController = OwnerComp.GetAIOwner())
    {
        if (auto AIPawn = AIController->GetPawn())
        {
            UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
            UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(AIPawn);

            if (BlackboardComp && NavSys)
            {
                FNavLocation RandomNavLocation;
                if (NavSys->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), SearchRadius, RandomNavLocation))
                {
                    BlackboardComp->SetValueAsVector("RandomLocation", RandomNavLocation.Location);
                    return EBTNodeResult::Succeeded;
                }
            }
        }
    }

    return EBTNodeResult::Failed;
}
