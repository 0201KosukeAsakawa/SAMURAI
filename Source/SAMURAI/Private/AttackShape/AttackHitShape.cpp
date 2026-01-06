// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackShape/AttackHitShape.h"

void UAttackHitShape::Initialize(AActor* InOwner)
{
    OwnerActor = InOwner;
}

EAttackHitResult UAttackHitShape::JudgeHitResult(AActor* OtherActor) const
{
    // 共通の最低限ロジック
    if (!OtherActor || OtherActor == OwnerActor)
    {
        return EAttackHitResult::None;
    }

    //// 防御・弾き判定は Actor 側に問い合わせる
    //return ICombatInterface::Execute_JudgeHit(
    //    OtherActor,
    //    OwnerActor
    //);
    return EAttackHitResult::None;
}