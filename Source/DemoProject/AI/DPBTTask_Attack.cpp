// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPBTTask_Attack.h"

#include "AIController.h"
#include "Characters/DPCharacter.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "Abilities/DPGameplayAbility.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPBTTask_Attack::UDPBTTask_Attack()
{
    NodeName = "Attack To Target";
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
EBTNodeResult::Type UDPBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (AAIController* AIController = OwnerComp.GetAIOwner())
    {

        ACharacter* AIPawn = Cast<ACharacter>(AIController->GetPawn());
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

        if (AIPawn && BlackboardComp)
        {
            if (auto TargetActor = Cast<ADPCharacter>(BlackboardComp->GetValueAsObject("TargetActor")))
            {
                FVector TargetLocation = TargetActor->GetActorLocation();
                FVector Direction = TargetLocation - AIPawn->GetActorLocation();
                Direction.Z = 0.0f;

                if (!Direction.IsNearlyZero())
                {
                    FRotator NewRotation = Direction.Rotation();
                    AIPawn->SetActorRotation(NewRotation);
                }
                
                UAbilitySystemComponent* AbilitySystem = AIPawn->FindComponentByClass<UAbilitySystemComponent>();
                if (AbilitySystem && AbilityToActivate)
                {
                    FGameplayAbilitySpec* AbilitySpec = AbilitySystem->FindAbilitySpecFromClass(AbilityToActivate);
                    if (AbilitySpec)
                    {
                        AbilitySystem->TryActivateAbility(AbilitySpec->Handle);
                    }
                }

                return EBTNodeResult::Succeeded;
            }
        }
    }

    return EBTNodeResult::Failed;
}
