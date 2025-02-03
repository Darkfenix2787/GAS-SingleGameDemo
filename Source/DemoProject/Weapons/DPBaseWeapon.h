// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "GameFramework/Actor.h"
#include "DPBaseWeapon.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UGameplayEffect;

UCLASS()
class DEMOPROJECT_API ADPBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ADPBaseWeapon();

	void ToggleBoxCollision(const bool bIsActive);

protected:
	
	virtual void BeginPlay() override;	

	UFUNCTION()
	void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(EditDefaultsOnly, Category = "Damage",Meta = (ClampMin = 0, ClampMax = 100))
	float WeaponDamage = 0.f;

	void SetDamageMultiplier(const int32 Value) { DamageMultiplier = Value; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffect = nullptr;
		
	int32 DamageMultiplier = 1;
};
