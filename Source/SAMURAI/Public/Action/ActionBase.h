// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/ActionInterface.h"
#include "ActionBase.generated.h"

enum class EActionEndReason : uint8
{
    Completed,     // 正常完了
    Interrupted    // 強制中断
};

UENUM(BlueprintType)
enum class EAttackHitResult : uint8
{
    Miss,       // 空振り
    Deflect,    // 弾き
    Guard,      // ガード
    Hit,        // 被弾
    Mikiri,     // 見切り
    Grabbed     // 掴まれた
};

struct FActionResult
{
    EActionEndReason EndReason = EActionEndReason::Completed;
    EAttackHitResult HitResult = EAttackHitResult::Miss;
};
/**
 * 
 */
UCLASS()
class SAMURAI_API UActionBase : public UObject
{
    GENERATED_BODY()

public:
    UActionBase();

    DECLARE_MULTICAST_DELEGATE_TwoParams(
        FOnActionFinished,
        UActionBase*,
        const FActionResult&
    );

    FOnActionFinished OnActionFinished;

    virtual void ActionStart() {}
    virtual void Tick(float DeltaTime) {}
    virtual void ActionEnd() {}
    virtual void Interrupt();

    void SetOwnerCharacter(ACharacter* newOwner) {OwnerCharacter = newOwner ;}
protected:
    void FinishAction(const FActionResult& Result);
protected:

    UPROPERTY()
    ACharacter* OwnerCharacter;

    FActionResult ActionResult;
private:
    bool bFinished;
};