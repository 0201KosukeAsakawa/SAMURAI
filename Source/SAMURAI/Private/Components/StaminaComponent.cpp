// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StaminaComponent.h"

namespace  {
	// スタミナ減少後に回復を開始するまでの秒数 
	constexpr float RECOVERY_DELAY = 3.f; 
	// 1秒あたりの回復量 
	constexpr float RECOVERY_RATE = 10.f; 
	constexpr float RECOVERY_INTERVAL= 0.1f;
}
UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxStamina = 100.f;
	CurrentStamina = MaxStamina;
	bIsBroken = false;

	RecoveryDelay = RECOVERY_DELAY;
	RecoveryRate = RECOVERY_RATE;
	RecoveryInterval = RECOVERY_INTERVAL;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;
}

void UStaminaComponent::SubtractStamina(float DecreasingValue)
{
	if (DecreasingValue <= 0.f || CurrentStamina <= 0.f)
	{
		return;
	}

	CurrentStamina -= DecreasingValue;
	CurrentStamina = FMath::Max(CurrentStamina, 0.f);

	OnStaminaChanged.Broadcast(CurrentStamina);

	// 回復停止 & 再予約
	StopRecovery();
	StartRecovery();

	// ブレイク判定
	if (CurrentStamina == 0.f && !bIsBroken)
	{
		bIsBroken = true;
		OnStaminaZero.Broadcast();
	}
}

void UStaminaComponent::RecoverStamina(float RecoverValue)
{
	if (RecoverValue <= 0.f || CurrentStamina >= MaxStamina)
	{
		return;
	}

	CurrentStamina += RecoverValue;
	CurrentStamina = FMath::Min(CurrentStamina, MaxStamina);

	OnStaminaChanged.Broadcast(CurrentStamina);
}

float UStaminaComponent::GetCurrentStamina() const
{
	return CurrentStamina;
}

float UStaminaComponent::GetMaxStamina() const
{
	return MaxStamina;
}

bool UStaminaComponent::IsBroken() const
{
	return bIsBroken;
}

// =======================
// 回復制御
// =======================

void UStaminaComponent::StartRecovery()
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().SetTimer(
		RecoveryDelayTimerHandle,
		this,
		&UStaminaComponent::RecoveryTick,
		RecoveryInterval,
		true,
		RecoveryDelay
	);
}

void UStaminaComponent::RecoveryTick()
{
	if (CurrentStamina >= MaxStamina)
	{
		StopRecovery();
		return;
	}

	RecoverStamina(RecoveryRate * RecoveryInterval);
}

void UStaminaComponent::StopRecovery()
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(RecoveryDelayTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RecoveryTickTimerHandle);
}
