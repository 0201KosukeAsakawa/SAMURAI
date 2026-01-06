// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Action/ActionBase.h"
#include "EnemyActor.generated.h"


UCLASS()
class SAMURAI_API AEnemyActor : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyActor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    /** ActionComponent を持つだけ */
    UPROPERTY(EditAnywhere, Instanced, Category = "Actions")
    class UActionComponent* ActionComp;
};
