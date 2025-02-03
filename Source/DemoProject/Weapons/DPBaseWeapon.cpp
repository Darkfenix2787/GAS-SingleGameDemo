// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPBaseWeapon.h"

#include "AbilitySystemComponent.h"
#include "Abilities/DPGameplayTags.h"
#include "Characters/DPCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
ADPBaseWeapon::ADPBaseWeapon()
{	
	PrimaryActorTick.bCanEverTick = false;

	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADPBaseWeapon::OnBoxComponentBeginOverlap);	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPBaseWeapon::ToggleBoxCollision(const bool bIsActive)
{
	CollisionComponent->SetCollisionEnabled(bIsActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void ADPBaseWeapon::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OwnerCharacter = Cast<ADPCharacter>(GetOwner());
	auto TargetCharacter = Cast<ADPCharacter>(OtherActor);

	if (!OwnerCharacter || !TargetCharacter || OwnerCharacter == TargetCharacter)
	{
		return;
	}

	auto TargetASC = TargetCharacter->GetAbilitySystemComponent();
	auto OwnerASC = Cast<ADPCharacter>(GetOwner())->GetAbilitySystemComponent();

	if (TargetASC && OwnerASC)
	{
		FGameplayEffectContextHandle DamageEffectContext = OwnerASC->MakeEffectContext();
		DamageEffectContext.AddInstigator(OwnerASC->GetOwner(), this);


		const auto& SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect, 1.0f, DamageEffectContext);

		if (SpecHandle.Data.IsValid())
		{	 
			SpecHandle.Data->SetSetByCallerMagnitude(SetByCallerTags::SetByCaller_Damage, -WeaponDamage*DamageMultiplier);
			OwnerASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);			
		}
	}
}