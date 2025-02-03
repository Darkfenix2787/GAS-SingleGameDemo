// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "Logging/LogMacros.h"

#include "DPCharacter.generated.h"

class ADPBaseWeapon;

struct FGameplayTag;
struct FInputActionValue;
class UCameraComponent;
class UDPAbilitySystemComponent;
class UDPAbilitySet;
class UDPAttributeSet;
class UDPInputData;
class UDPCharacterMovementComponent;
class UGameplayEffect;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);

/* Base Character class */
UCLASS(config = Game)
class DEMOPROJECT_API ADPCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;	
	
	/** Character AbilitySystem Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDPAbilitySystemComponent> AbilitySystemComponent;

	/** Character Weapon*/	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADPBaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName WeaponSocketName = NAME_None;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AbilityComponent")
	const TObjectPtr<UDPAbilitySet> AbilitySet = nullptr;

	/** Sets default values for the Inputs. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	const TObjectPtr<UDPInputData> InputData = nullptr;

	UPROPERTY()
	TObjectPtr<ADPBaseWeapon> EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	TSubclassOf<UGameplayEffect> RespawnEffect = nullptr;

	UPROPERTY()
	float RespawnTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death")
	TObjectPtr<UAnimMontage> DeathAnimationMontage = nullptr;

	// Change Attributes Delegates	
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;

protected:

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	void RegisterMappingContexts(APlayerController* PlayerController) const;

	void BindInputs(APlayerController* PlayerController);

	void BindAttributeEvents();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for crouch input */
	void Crouching(const FInputActionValue& Value);

	// Attribute changed callbacks	
	virtual void HealthChanged(const FOnAttributeChangeData& Data);	
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);

	//Called when the character dies
	void OnDeath();

	// Called when the character should respawn
	UFUNCTION()
	void Respawn();

	// Handle blocking/unblocking input
	void SetInputBlocked(const bool bIsEnabled);

public:
	// Sets default values for this character's properties
	ADPCharacter(const FObjectInitializer& ObjectInitializer);
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void AbilityInputTag_Trigger(FGameplayTag InputTag, bool bInputVal);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	const UDPAttributeSet* GetAttributeSet();

	TObjectPtr<ADPBaseWeapon> GetEquippedWeapon() { return EquippedWeapon; }

	// Handle blocking/unblocking Character Movement
	void ToggleMovement(const bool bIsEnabled);

	void SetComboAlertVisibility(const bool bIsVisible);
	
};
