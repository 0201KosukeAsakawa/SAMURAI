// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


// =======================
// デリゲート
// =======================

/** スタミナが0になった */
DECLARE_MULTICAST_DELEGATE(FOnStaminaZero);

/** スタミナが変化した */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float);

/**
 * スタミナ（体幹）管理コンポーネント
 * - 値の管理のみを責務とする
 * - ルール解釈（即死 / ダメ倍率など）は所有者側で行う
 */
UCLASS(ClassGroup = (Combat), meta = (BlueprintSpawnableComponent))
class SAMURAI_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStaminaComponent();

	// ----------------------------
	// スタミナ操作
	// ----------------------------

	/** スタミナを減らす */
	void SubtractStamina(float DecreasingValue);

	/** スタミナを回復する */
	void RecoverStamina(float RecoverValue);

	/** 現在のスタミナ取得 */
	float GetCurrentStamina() const;

	/** 最大スタミナ取得 */
	float GetMaxStamina() const;

	/** ブレイク状態か */
	bool IsBroken() const;

	// ----------------------------
	// イベント
	// ----------------------------

	FOnStaminaZero OnStaminaZero;
	FOnStaminaChanged OnStaminaChanged;

protected:
	virtual void BeginPlay() override;

private:
	// ----------------------------
	// 内部処理
	// ----------------------------

	/** 回復開始 */
	void StartRecovery();

	/** 定期回復処理 */
	void RecoveryTick();

	/** 回復停止 */
	void StopRecovery();

private:
	// ----------------------------
	// パラメータ
	// ----------------------------

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(VisibleAnywhere, Category = "Stamina")
	bool bIsBroken;

	UPROPERTY(EditAnywhere, Category = "Stamina|Recovery")
	float RecoveryDelay;

	UPROPERTY(EditAnywhere, Category = "Stamina|Recovery")
	float RecoveryRate;

	UPROPERTY(EditAnywhere, Category = "Stamina|Recovery")
	float RecoveryInterval;

	// ----------------------------
	// タイマー
	// ----------------------------

	FTimerHandle RecoveryDelayTimerHandle;
	FTimerHandle RecoveryTickTimerHandle;
};