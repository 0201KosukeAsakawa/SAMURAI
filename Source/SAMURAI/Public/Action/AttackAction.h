// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ActionInterface.h"
#include "UObject/NoExportTypes.h"
#include "AttackAction.generated.h"

class UAnimationMontage;
/**
 * 
 */
UCLASS()
class SAMURAI_API UAttackAction : public UObject,public IActionInterface
{
	GENERATED_BODY()
public:
	UAttackAction();
	void OnMontageEnded(UAnimationMontage*, bool bInterrupted);
private:
	virtual void Start() override;
	virtual void Tick(float DeltaTime) override;
	virtual void End() override;
};
