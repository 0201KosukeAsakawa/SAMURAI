// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CameraControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UCameraControllerComponent::UCameraControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(this);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}



// Called when the game starts
void UCameraControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (FollowCamera && !FollowCamera->IsAttachedTo(this))
	{
		CameraBoom->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
		FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
		UE_LOG(LogTemp, Warning, TEXT("Camera was reattached to PlayerCameraControlComponent"));
	}

}

void UCameraControllerComponent::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if(APawn* owner = Cast<APawn>(GetOwner()))
	{
		if (owner->GetController() != nullptr)
		{
			// add yaw and pitch input to controller
			owner->AddControllerYawInput(LookAxisVector.X);
			owner->AddControllerPitchInput(LookAxisVector.Y);
		}
	}

}