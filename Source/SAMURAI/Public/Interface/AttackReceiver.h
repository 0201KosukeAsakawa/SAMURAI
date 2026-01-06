// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackReceiver.generated.h"

enum class EAttackHitResult : uint8;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMURAI_API IAttackReceiver
{
    GENERATED_BODY()

public:
    virtual EAttackHitResult ReceiveAttack(
        const FAttackInfo& AttackInfo,
        AActor* Attacker) 
    {
       return EAttackHitResult();
    };
};