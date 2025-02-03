
// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DPAIController.generated.h"

class ADPEnemyCharacter;
class UBehaviorTree;
class UBlackboardComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class DEMOPROJECT_API ADPAIController : public AAIController
{
	GENERATED_BODY()

protected:

	ADPAIController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* EnemyBehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* EnemyBlackBoard = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig = nullptr;

	TObjectPtr<ADPEnemyCharacter> TargetCharacter = nullptr;
	
};
