// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPCharacter.h"

#include "Abilities/DPAttributeSet.h"
#include "Abilities/DPAbilitySet.h"
#include "Abilities/DPGameplayTags.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DPAbilitySystemComponent.h"
#include "Components/DPEnhancedInputComponent.h"
#include "Components/DPCharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Inputs/DPInputData.h"
#include "Inputs/DPInputMapping.h"
#include "UI/DPHUD.h"
#include "Weapons/DPBaseWeapon.h"



DEFINE_LOG_CATEGORY(LogCharacter);

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
ADPCharacter::ADPCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;	

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AbilitySystemComponent = CreateDefaultSubobject<UDPAbilitySystemComponent>(TEXT("AbilitySystemComponent"));	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponClass)
	{
		EquippedWeapon = GetWorld()->SpawnActor<ADPBaseWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);

		if (EquippedWeapon)
		{
			EquippedWeapon->SetOwner(this);
			EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent);
	}

	// Add Input Mapping Context
	if (InputData)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(NewController))
		{
			RegisterMappingContexts(PlayerController);
			BindInputs(PlayerController);
		}
	}

	BindAttributeEvents();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UAbilitySystemComponent* ADPCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
const UDPAttributeSet* ADPCharacter::GetAttributeSet()
{
	return Cast<UDPAttributeSet>(AbilitySystemComponent->GetAttributeSet(UDPAttributeSet::StaticClass()));
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::RegisterMappingContexts(APlayerController* PlayerController) const
{

	if (UEnhancedInputLocalPlayerSubsystem* newLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		if (UDPInputMapping* mappingContextData = InputData->GetMappingContext())
		{
			const TArray<FDPInputMappingContext>& inputMappingContexts = mappingContextData->GetInputMappings();

			for (const auto& mappingContext : inputMappingContexts)
			{
				newLocalPlayerSubsystem->AddMappingContext(mappingContext.InputMappingContext, mappingContext.Priority);
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::BindInputs(APlayerController* PlayerController)
{
	// Set up action bindings
	if (UDPEnhancedInputComponent* EnhancedInputComponent = Cast<UDPEnhancedInputComponent>(PlayerController->InputComponent))
	{
		EnhancedInputComponent->BindActionByTag(InputData->GetInputCofig(), InputNativeTags::Input_Native_Move, ETriggerEvent::Triggered, this, &ADPCharacter::Move);
		EnhancedInputComponent->BindActionByTag(InputData->GetInputCofig(), InputNativeTags::Input_Native_Look, ETriggerEvent::Triggered, this, &ADPCharacter::Look);
		EnhancedInputComponent->BindActionByTag(InputData->GetInputCofig(), InputNativeTags::Input_Native_Crouch, ETriggerEvent::Triggered, this, &ADPCharacter::Crouching);
		EnhancedInputComponent->BindAbilityByTag(InputData->GetInputCofig(), this, &ADPCharacter::AbilityInputTag_Trigger);
	}
	else
	{
		UE_LOG(LogCharacter, Error, TEXT("Failed to find an Enhanced Input component!."));
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::BindAttributeEvents()
{
	if (AbilitySystemComponent)
	{
		const UDPAttributeSet* AttributeSet = Cast<UDPAttributeSet>(AbilitySystemComponent->GetAttributeSet(UDPAttributeSet::StaticClass()));
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ADPCharacter::HealthChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &ADPCharacter::StaminaChanged);
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::AbilityInputTag_Trigger(FGameplayTag InputTag, bool bInputVal)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityInputTagTrigger(InputTag, bInputVal);
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::Crouching(const FInputActionValue& Value)
{
	bool bIsPressed = Value.Get<bool>();
	
	if (bIsPressed)
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;	

	if (Health <= 0)
	{
		OnDeath();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::StaminaChanged(const FOnAttributeChangeData& Data)
{
	// Do Stamina stuff
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::OnDeath()
{
	if (AbilitySystemComponent)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(RespawnEffect, 1.0f, AbilitySystemComponent->MakeEffectContext());

		if (EffectSpecHandle.IsValid())
		{	
			EffectSpecHandle.Data->SetSetByCallerMagnitude(SetByCallerTags::SetByCaller_Respawn, RespawnTime);			
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}

	// Disable Player Input
	SetInputBlocked(true);

	if (DeathAnimationMontage)
	{	
		RespawnTime = DeathAnimationMontage->GetPlayLength();
		PlayAnimMontage(DeathAnimationMontage);
	}

	FTimerHandle TimerHandle_Respawn;	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Respawn,	this, &ADPCharacter::Respawn, RespawnTime, false);

		
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::Respawn()
{
	if (AbilitySystemComponent)
	{
		if (const UDPAttributeSet* AttributeSet = Cast<UDPAttributeSet>(AbilitySystemComponent->GetAttributeSet(UDPAttributeSet::StaticClass())))
		{
			AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetHealthAttribute(), AttributeSet->GetMaxHealth());
			AbilitySystemComponent->SetNumericAttributeBase(AttributeSet->GetHealthAttribute(), AttributeSet->GetMaxHealth());			

			// Remove the blocking Gameplay Effect
			AbilitySystemComponent->RemoveActiveEffectsWithSourceTags(FGameplayTagContainer(SetByCallerTags::SetByCaller_Respawn));			

			// Enable Player Input
			SetInputBlocked(false);
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::SetInputBlocked(const bool bIsEnabled)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		if (bIsEnabled)
		{
			ToggleMovement(false);			
			PC->SetIgnoreLookInput(true);
		}
		else
		{
			ToggleMovement(true);
			PC->SetIgnoreLookInput(false);
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::ToggleMovement(const bool bIsEnabled)
{
	if (auto CharacterMovementComp = GetCharacterMovement())
	{
		if (!bIsEnabled)
		{
			CharacterMovementComp->DisableMovement();
			CharacterMovementComp->StopMovementImmediately();
		}
		else
		{
			CharacterMovementComp->SetMovementMode(MOVE_Walking);
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPCharacter::SetComboAlertVisibility(const bool bIsVisible)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (auto CharacterHUD = Cast<ADPHUD>(PC->GetHUD()))
		{
			CharacterHUD->ToggleComboImageVisibility(bIsVisible);
		}
	}	
}
