// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
    :CurrentAction(nullptr)
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentAction = nullptr;
}

void UActionComponent::StartDefaultAction()
{
    if (!DefaultActionClass) return;

    UActionBase* Action = NewObject<UActionBase>(GetOwner(), DefaultActionClass);
    StartAction(Action);
}

void UActionComponent::StartAction(UActionBase* Action)
{
    if (!Action) return;

    if (CurrentAction)
    {
        CurrentAction->Interrupt();
    }

    CurrentAction = Action;
    CurrentAction->SetOwnerCharacter(Cast<ACharacter>(GetOwner()));
    CurrentAction->OnActionFinished.AddUObject(this, &UActionComponent::OnActionFinished);
    CurrentAction->ActionStart();
}

//void UActionComponent::Tick(float DeltaTime)
//{
//    if (CurrentAction)
//    {
//        CurrentAction->Tick(DeltaTime);
//    }
//}

void UActionComponent::OnActionFinished(UActionBase* Action, const FActionResult& Result)
{
    if (Action != CurrentAction) return;
    CurrentAction = nullptr;
}