// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackShape/BoxAttackHitShape.h"
#include "Components/BoxComponent.h"

void UBoxAttackHitShape::Initialize(AActor* InOwner)
{
    Super::Initialize(InOwner);

    if (PreplacedBox)
    {
        Collision = PreplacedBox;
    }
    else
    {
        // コード生成
        Collision = NewObject<UBoxComponent>(InOwner, UBoxComponent::StaticClass(), TEXT("AttackHitBox"));
        Collision->AttachToComponent(InOwner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        Collision->RegisterComponent(); // これでエディタ上でも表示・操作可能
    }

    Collision->SetRelativeLocation(RelativeLocation);
    Collision->SetRelativeRotation(RelativeRotation);
    Collision->SetRelativeScale3D(RelativeScale);

    Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Collision->SetGenerateOverlapEvents(true);
    Collision->OnComponentBeginOverlap.AddDynamic(this, &UBoxAttackHitShape::OnOverlap);
}

void UBoxAttackHitShape::Activate()
{
    if (Collision)
        Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UBoxAttackHitShape::Deactivate()
{
    if (Collision)
        Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UBoxAttackHitShape::OnOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    EAttackHitResult Result = JudgeHitResult(OtherActor);
    OnHit.ExecuteIfBound(Result);
}