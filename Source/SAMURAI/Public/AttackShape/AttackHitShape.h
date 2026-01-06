// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action/ActionBase.h"
#include "AttackHitShape.generated.h"

UCLASS(Abstract,Blueprintable, EditInlineNew, DefaultToInstanced)
class SAMURAI_API UAttackHitShape : public UObject
{
    GENERATED_BODY()

public:
    virtual void Initialize(AActor* InOwner);
    virtual void Activate() {}
    virtual void Deactivate() {}
    UPrimitiveComponent* GetCollision()const {return Collision;}
    DECLARE_DELEGATE_OneParam(
        FOnHitResult,
        EAttackHitResult
    );
    FOnHitResult OnHit;

protected:
    UPROPERTY()
    AActor* OwnerActor;

    // 派生先で作成する UPrimitiveComponent を格納
    UPROPERTY()
    UPrimitiveComponent* Collision;

    virtual EAttackHitResult JudgeHitResult(AActor* OtherActor) const;
};