// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPGameplayTags.h"

// Define and expose the gameplay tags to other modules and code.

/** Gameplay Tags */
namespace InputNativeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Native_Move, "Input.Native.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Native_Look, "Input.Native.Look");
	UE_DEFINE_GAMEPLAY_TAG(Input_Native_Crouch, "Input.Native.Crouch");
}

/** Gameplay Tags */
namespace SetByCallerTags
{
	UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Damage, "SetByCaller.Damage");
	UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Respawn, "SetByCaller.Respawn");
}

/** Animation Tags */
namespace AnimationTags
{
	UE_DEFINE_GAMEPLAY_TAG(ANS_HandleCollision, "ANS.HandleCollision");
	UE_DEFINE_GAMEPLAY_TAG(ANS_HandleCombo, "ANS.HandleCombo");
	UE_DEFINE_GAMEPLAY_TAG(ANS_FinalAttack, "ANS.FinalAttack");
	
}