// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "AttackAction.generated.h"

class UAnimationMontage;
class UAttackHitShape;
/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew)
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

    UPROPERTY(EditAnywhere, Instanced, Category = "HitShapes")
    TArray<UAttackHitShape*> HitShapes;

    UPROPERTY()
    UAnimInstance* AnimInstance;

    EAttackHitResult FinalHitResult;
};