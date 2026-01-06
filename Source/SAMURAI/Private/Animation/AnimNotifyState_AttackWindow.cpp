// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_AttackWindow.h"
#include "Components/ActionComponent.h"
#include "AttackShape/AttackHitShape.h"
#include "Action/AttackAction.h"

void UAnimNotifyState_AttackWindow::NotifyBegin(
    USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation,
    float TotalDuration)
{
    if (!MeshComp) return;
    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    // ActionComponent を取得
    UActionComponent* ActionComp = Owner->FindComponentByClass<UActionComponent>();
    if (!ActionComp) return;

    // 現在の Action が Attack か確認
    UAttackAction* Attack = Cast<UAttackAction>(ActionComp->GetCurrentAction());
    if (!Attack) return;

    // コリジョンを有効化
    for (UAttackHitShape* Shape : Attack->GetActiveShapes())
    {
        if (Shape && Shape->GetCollision())
        {
            Shape->GetCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            // デバッグ表示
            Shape->GetCollision()->SetHiddenInGame(false);
        }
    }
}


void UAnimNotifyState_AttackWindow::NotifyEnd(
    USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation)
{
    if (!MeshComp) return;
    AActor* Owner = MeshComp->GetOwner();
    if (!Owner) return;

    UActionComponent* ActionComp = Owner->FindComponentByClass<UActionComponent>();
    if (!ActionComp) return;

    UAttackAction* Attack = Cast<UAttackAction>(ActionComp->GetCurrentAction());
    if (!Attack) return;

    // コリジョンを無効化
    for (UAttackHitShape* Shape : Attack->GetActiveShapes())
    {
        if (Shape && Shape->GetCollision())
        {
            Shape->GetCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            // デバッグ表示
            Shape->GetCollision()->SetHiddenInGame(true);
        }
    }
}