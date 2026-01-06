// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/AttackAction.h"
#include "GameFramework/Character.h"
#include "AttackShape/AttackHitShape.h"

UAttackAction::UAttackAction()
    : Montage(nullptr)
    , AnimInstance(nullptr)
    , AttackInfo()
{
}

void UAttackAction::ActionStart()
{
    if (!Montage || !OwnerCharacter) return;

    AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
    if (!AnimInstance) return;

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &UAttackAction::OnMontageEnded);
    AnimInstance->Montage_SetEndDelegate(EndDelegate, Montage);

    AnimInstance->Montage_Play(Montage);

    UE_LOG(LogTemp, Log, TEXT("[AttackAction] Montage Play"));
}

void UAttackAction::Interrupt()
{
    if (AnimInstance && Montage)
    {
        AnimInstance->Montage_Stop(0.2f, Montage);
    }

    //Super::Interrupt();
}

void UAttackAction::NotifyHitResult(EAttackHitResult InResult)
{
    if (InResult == EAttackHitResult::Mikiri)
    {
        ActionResult.HitResult = InResult;
    }
    else if (ActionResult.HitResult == EAttackHitResult::Miss)
    {
        ActionResult.HitResult = InResult;
    }
}
TArray<UAttackHitShape*> UAttackAction::GetActiveShapes() const
{
    return ActiveShapes;
}
void UAttackAction::ActivateHitShapes()
{
    for (UAttackHitShape* Shape : ActiveShapes)
    {
        Shape->Activate();
    }
}

void UAttackAction::DeactivateHitShapes()
{
    for (UAttackHitShape* Shape : ActiveShapes)
    {
        Shape->Deactivate();
    }
}


void UAttackAction::OnMontageEnded(
    UAnimMontage* EndedMontage,
    bool bInterrupted)
{
    if (EndedMontage != Montage) return;

    FActionResult Result;
    Result.EndReason = bInterrupted
        ? EActionEndReason::Interrupted
        : EActionEndReason::Completed;

    Result.HitResult = ActionResult.HitResult;

    FinishAction(Result);
}