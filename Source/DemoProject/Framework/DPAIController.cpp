// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "Framework/DPAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/DPPlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
ADPAIController::ADPAIController()
{
    EnemyBlackBoard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));    
    SetPerceptionComponent(*AIPerceptionComponent);

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    if (SightConfig)
    {
        SightConfig->SightRadius = 2000.0f;
        SightConfig->LoseSightRadius = 2500.0f;
        SightConfig->PeripheralVisionAngleDegrees = 90.0f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

        AIPerceptionComponent->ConfigureSense(*SightConfig);
        AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
    }

    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ADPAIController::OnTargetPerceptionUpdated);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPAIController::BeginPlay()
{
	Super::BeginPlay();

    if (EnemyBehaviorTree)
    {   
        if (UseBlackboard(EnemyBehaviorTree->BlackboardAsset, EnemyBlackBoard))
        {   
            RunBehaviorTree(EnemyBehaviorTree);
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (auto TargetPlayer = Cast<ADPPlayerCharacter>(Actor))
    {
        if (EnemyBlackBoard)
        {
            if (Stimulus.WasSuccessfullySensed())
            {
                EnemyBlackBoard->SetValueAsObject(TEXT("TargetActor"), TargetPlayer);
            }
            else
            {
                EnemyBlackBoard->ClearValue(TEXT("TargetActor"));
            }
        }
    }    
}
