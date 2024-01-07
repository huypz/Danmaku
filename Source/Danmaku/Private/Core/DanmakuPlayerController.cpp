// © 2024, Huy Phan. All rights reserved.


#include "Core/DanmakuPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"

ADanmakuPlayerController::ADanmakuPlayerController()
{
	bShowMouseCursor = true;

	CameraYaw = 0.f;
	
	DefaultContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Danmaku.IMC_Danmaku'"));
	MoveAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'"));
	RotateAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Rotate.IA_Rotate'"));
}

void ADanmakuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultContext)
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}
	
	if (UGameViewportClient* GameViewport =  GetWorld()->GetGameViewport())
	{
		// Unlit view mode
		GameViewport->ViewModeIndex = 2;
	}
	
	// This setting is used to disable the tonemapper.
	FString Command = "ShowFlag.Tonemapper 0";
	ConsoleCommand(*Command);

	/**
	 *	The tonemapper is a function that maps high dynamic range (HDR) colors into low dynamic range (LDR) that a display can output.
	 */
	Command = "r.TonemapperGamma 0";
	ConsoleCommand(*Command);

	/**
	 *	This setting is used to switch off the filmic tonemapper.	
	 */
	Command = "r.TonemapperFilm 0";
	ConsoleCommand(*Command);

	/**
	 * This setting is used to control the sharpness of the image. It can make the game more clear. However, using a high value can make the image look crunchy.
	 */
	Command = "r.Tonemapper.Sharpen 0";
	ConsoleCommand(*Command);

	/**
	 *  This command is used to control the grain quantization. It is a technique used to reduce color banding on 8-bit screens.
	 *  However, it can result in a visible noise pattern.
	 */
	Command = "r.Tonemapper.GrainQuantization 0";
	ConsoleCommand(*Command);

	/**
	 *	This setting controls the quality of the tonemapper5. Higher values will improve the quality but may impact performance.
	 */
	Command = "r.Tonemapper.Quality 0";
	ConsoleCommand(*Command);
}

void ADanmakuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADanmakuPlayerController::Move);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ADanmakuPlayerController::Rotate);
	}
}

void ADanmakuPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D InputAxisVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		FRotator Rotation = ControlledPawn->GetActorRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ADanmakuPlayerController::Rotate(const FInputActionValue& Value)
{
	float InputAxisValue = Value.Get<float>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		FRotator Rotation = ControlledPawn->GetActorRotation();
		FRotator NewRotation(0.f, Rotation.Yaw + InputAxisValue, 0.f);
		ControlledPawn->SetActorRotation(NewRotation);
		
		CameraYaw = NewRotation.Yaw;
	}
}


