// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackShape/WeaponCollisionShape.h"

void UWeaponAttackHitShape::Initialize(AActor* InOwner)
{
    Super::Initialize(InOwner);

  /*  WeaponCollision = FindWeaponCollision(InOwner);*/

    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponCollision->SetGenerateOverlapEvents(true);

    WeaponCollision->OnComponentBeginOverlap.AddDynamic(
        this,
        &UWeaponAttackHitShape::OnOverlap
    );
}
void UWeaponAttackHitShape::Activate()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
void UWeaponAttackHitShape::Deactivate()
{
    WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void UWeaponAttackHitShape::OnOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    EAttackHitResult Result = JudgeHitResult(OtherActor);
    OnHit.ExecuteIfBound(Result);
}
