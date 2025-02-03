// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Engine/DataAsset.h"

#include "DPInputData.generated.h"

class UDPInputMapping;
class UDPInputConfig;

/**
 * Data Asset that contains the Input Data
 */
UCLASS(Const)
class DEMOPROJECT_API UDPInputData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	const TObjectPtr<UDPInputMapping> GetMappingContext() const { return InputMapping; }
	
	const TObjectPtr<UDPInputConfig> GetInputCofig() const { return InputConfig; }

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UDPInputMapping> InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UDPInputConfig> InputConfig;
	
};
