// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackShape/AttackHitShape.h"
#include "WeaponCollisionShape.generated.h"

UCLASS()
class SAMURAI_API UWeaponAttackHitShape : public UAttackHitShape
{
    GENERATED_BODY()

public:
    virtual void Initialize(AActor* InOwner) override;
    virtual void Activate() override;
    virtual void Deactivate() override;

private:
    UPROPERTY()
    UPrimitiveComponent* WeaponCollision;

    UFUNCTION()
    void OnOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};