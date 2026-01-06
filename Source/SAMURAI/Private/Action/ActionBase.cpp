// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/ActionBase.h"

UActionBase::UActionBase()
    :bFinished(false)
    ,OwnerCharacter(nullptr)
{
}

void UActionBase::Interrupt()
{
    if (bFinished) return;

    FActionResult Result;
    Result.EndReason = EActionEndReason::Interrupted;

    FinishAction(Result);
}

void UActionBase::FinishAction(const FActionResult& Result)
{
    if (bFinished) return;

    bFinished = true;
    OnActionFinished.Broadcast(this, Result);
}