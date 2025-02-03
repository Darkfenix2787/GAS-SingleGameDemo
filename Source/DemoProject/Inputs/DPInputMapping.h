// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "DPInputMapping.generated.h"

class UInputMappingContext;

USTRUCT()
struct FDPInputMappingContext
{
	GENERATED_BODY()

public:
	/** The Input Mapping Context to be added to the supported platforms. */
	UPROPERTY(EditDefaultsOnly)
	const UInputMappingContext* InputMappingContext;

	/** The priority of this Input Mapping Context. */
	UPROPERTY(EditDefaultsOnly)
	int32 Priority;	

	/** Default constructor. */
	FDPInputMappingContext() {
		InputMappingContext = nullptr;
		Priority = 0;		
	}

	/** Returns if this Augmented Input Mapping Context has all of its data valid. */
	bool IsValid() const;
};

/**
 * Class to handle the differents Input Mappings
 */
UCLASS()
class DEMOPROJECT_API UDPInputMapping : public UDataAsset
{
	GENERATED_BODY()

public:
	// InputMappings Getter
	TArray<FDPInputMappingContext> GetInputMappings() { return InputMappings; }

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Input|Mappings", Meta = (TitleProperty = "InputMappingContext"))
	TArray<FDPInputMappingContext> InputMappings;
	
};
