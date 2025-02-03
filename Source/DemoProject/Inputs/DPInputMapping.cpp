// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPInputMapping.h"

#include "InputMappingContext.h"

bool FDPInputMappingContext::IsValid() const
{
	return InputMappingContext->IsValidLowLevelFast();
}
