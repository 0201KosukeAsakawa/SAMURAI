// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/AttackAction.h"
#include "GameFramework/Character.h"
#include "AttackShape/AttackHitShape.h"

UAttackAction::UAttackAction()
    : Montage(nullptr)
    , AnimInstance(nullptr)
    , FinalHitResult(EAttackHitResult::None)
{
}

void UAttackAction::ActionStart()
{
    if (!Montage || !OwnerCharacter) return;

    AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
    if (!AnimInstance) return;

  //ActiveShapes.Empty();

  //  for (auto ShapeClass : HitShapes)
  //  {
  //      UAttackHitShape* Shape =
  //          NewObject<UAttackHitShape>(this, ShapeClass);

  //      Shape->Initialize(OwnerCharacter);

  //      Shape->OnHit.BindUObject(
  //          this,
  //          &UAttackAction::NotifyHitResult
  //      );

  //      ActiveShapes.Add(Shape);
  //  }

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
    if (InResult == EAttackHitResult::Parried)
    {
        FinalHitResult = InResult;
    }
    else if (FinalHitResult == EAttackHitResult::None)
    {
        FinalHitResult = InResult;
    }
}
TArray<UAttackHitShape*> UAttackAction::GetActiveShapes() const
{
    return HitShapes;
}
void UAttackAction::ActivateHitShapes()
{
    for (UAttackHitShape* Shape : HitShapes)
    {
        Shape->Activate();
    }
}

void UAttackAction::DeactivateHitShapes()
{
    for (UAttackHitShape* Shape : HitShapes)
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

    Result.HitResult = FinalHitResult;

    FinishAction(Result);
}