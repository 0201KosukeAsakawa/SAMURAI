// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAMURAI_API IActionInterface
{
	GENERATED_BODY()
public:
    virtual void Start() {}
    virtual void Tick(float DeltaTime) {}
    virtual void End() {}
};
