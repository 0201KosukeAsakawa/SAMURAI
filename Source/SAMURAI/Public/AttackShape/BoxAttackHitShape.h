// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackShape/AttackHitShape.h"
#include "BoxAttackHitShape.generated.h"

class UBoxComponent;

UCLASS()
class SAMURAI_API UBoxAttackHitShape : public UAttackHitShape
{
    GENERATED_BODY()

private:
    virtual void Initialize(AActor* InOwner) override;

    virtual void Activate() override;

    virtual void Deactivate() override;

    UFUNCTION()
    void OnOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

private:
    /** Blueprint で置いた BoxComponent を指定可能 */
    UPROPERTY(EditAnywhere)
    UBoxComponent* PreplacedBox = nullptr;

    /** コード生成時の位置・回転・スケール */
    UPROPERTY(EditAnywhere)
    FVector RelativeLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere)
    FRotator RelativeRotation = FRotator::ZeroRotator;

    UPROPERTY(EditAnywhere)
    FVector RelativeScale = FVector(1.f, 1.f, 1.f);
};