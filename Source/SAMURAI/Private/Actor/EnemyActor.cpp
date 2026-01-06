// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemyActor.h"
#include "Components/ActionComponent.h"

AEnemyActor::AEnemyActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // ActionComponent を生成
    ActionComp = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
}

void AEnemyActor::BeginPlay()
{
    Super::BeginPlay();

    if (ActionComp)
    {
        // デフォルトアクションは全て ActionComponent に任せる
        ActionComp->StartDefaultAction();
    }
}

void AEnemyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //if (ActionComp)
    //{
    //    ActionComp->Tick(DeltaTime);
    //}
}