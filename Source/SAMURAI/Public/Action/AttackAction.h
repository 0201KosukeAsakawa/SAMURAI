// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "AttackAction.generated.h"

class UAnimationMontage;
class UAttackHitShape;

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    Normal,     // 通常斬り
    Thrust,     // 突き（見切り対象）
    Sweep,      // 下段（ジャンプ対象）
    Grab        // 掴み（ガード不可）
};

USTRUCT(BlueprintType)
struct FAttackInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    float Damage = 0.f;

    UPROPERTY(EditAnywhere)
    EAttackType Type = EAttackType::Normal;
};

UCLASS(Blueprintable)
class SAMURAI_API UAttackAction : public UActionBase
{
    GENERATED_BODY()
   
public:
    UAttackAction();
    virtual void ActionStart() override;
    virtual void Interrupt() override;

    void ActivateHitShapes();
    void DeactivateHitShapes();

    void NotifyHitResult(EAttackHitResult InResult);

    TArray<UAttackHitShape*> GetActiveShapes()const;
private:
    void OnMontageEnded(UAnimMontage* EndedMontage, bool bInterrupted);

private:
    UPROPERTY(EditAnywhere)
    UAnimMontage* Montage;

    UPROPERTY(EditAnywhere, Instanced, Category = "HitShape")
    TArray<UAttackHitShape*> ActiveShapes;

    UPROPERTY()
    UAnimInstance* AnimInstance;

    UPROPERTY(EditAnywhere)
    FAttackInfo AttackInfo;
};