// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

class UActionBase;
struct FActionResult;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SAMURAI_API UActionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UActionComponent();

    /** デフォルトアクションを開始 */
    void StartDefaultAction();

    /** 任意の Action を開始 */
    void StartAction(UActionBase* Action);

    ///** Tick 内で CurrentAction を更新 */
    //void Tick(float DeltaTime);

    /** 現在実行中の Action を返す */
    UActionBase* GetCurrentAction() const { return CurrentAction; }

private:
    /** Action 完了時の処理 */
    void OnActionFinished(UActionBase* Action, const FActionResult& Result);
private:
    /** デフォルトアクションクラス（Editor で設定） */
    UPROPERTY(EditAnywhere,Category = "Action")
    TSubclassOf<UActionBase> DefaultActionClass;

    /** 現在実行中の Action */
    UPROPERTY()
    UActionBase* CurrentAction;
};