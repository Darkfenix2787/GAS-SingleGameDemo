// This project belongs to Daniel Corredor, Use it only for study purposes.


#pragma once

#include "NativeGameplayTags.h"

// Declare Input gameplay tags.
namespace InputNativeTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Look);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Native_Crouch);
}

// Declare Input gameplay tags.
namespace SetByCallerTags
{	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Damage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Respawn);
}


/** Animation Tags */
namespace AnimationTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ANS_HandleCollision);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ANS_HandleCombo);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(ANS_FinalAttack);
}