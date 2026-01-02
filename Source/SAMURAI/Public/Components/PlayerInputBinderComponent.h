// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputBinderComponent.generated.h"


struct FInputActionValue;
class UEnhancedInputComponent;
class UInputAction;
class IPlayerInputReceiver;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMURAI_API UPlayerInputBinderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInputBinderComponent();


	/**
	 * 入力アクションをバインドする
	 *
	 * @param InputComponent 入力コンポーネント
	 * @param Receiver 入力を受け取るオブジェクト
	 */
	void BindInputs(UEnhancedInputComponent* InputComponent, TScriptInterface<IPlayerInputReceiver> Receiver);

private:
	void HandleMove(const FInputActionValue& Value);

	void HandleJump(const FInputActionValue& Value);

	void HandleLook(const FInputActionValue& Value);

private:	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
		
	UPROPERTY()
	TScriptInterface<IPlayerInputReceiver>InputReceiver;
};
