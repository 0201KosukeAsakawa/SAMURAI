// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interface/PlayerInputReceiver.h"
#include "SAMURAICharacter.generated.h"


class UInputAction;
class UCameraControllerComponent;
class UPlayerInputBinderComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASAMURAICharacter : public ACharacter,public IPlayerInputReceiver
{
	GENERATED_BODY()
public:
	ASAMURAICharacter();
protected:
	/** Called for movement input */
	void OnMove(const FInputActionValue& Value)override;

	/** Called for looking input */
	void OnLook(const FInputActionValue& Value)override;

	void OnJump(const FInputActionValue& Value)override;
	
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	UCameraControllerComponent* CameraControllerComponent;
	UPROPERTY(EditAnywhere)
	UPlayerInputBinderComponent* PlayerInputBinderComponent;
};

