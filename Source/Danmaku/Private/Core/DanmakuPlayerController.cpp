// © 2024, Huy Phan. All rights reserved.


#include "Core/DanmakuPlayerController.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Actor/DanmakuPlayerCharacter.h"
#include "Core/DanmakuGameState.h"
#include "Engine/RendererSettings.h"
#include "TileMap/TileGrid.h"

ADanmakuPlayerController::ADanmakuPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	
	RotationSpeed = 150.f;
	
	DefaultContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Danmaku.IMC_Danmaku'"));
	MoveAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Move.IA_Move'"));
	RotateAction = LoadObject<UInputAction>(nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Rotate.IA_Rotate'"));
}

float ADanmakuPlayerController::GetRotation()
{
	return GetControlRotation().Yaw;
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
}

void ADanmakuPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (RotationInput != 0.f)
	{
		if (ADanmakuPlayerCharacter* ControlledPawn = Cast<ADanmakuPlayerCharacter>(GetPawn()))
		{
			float NewRotation = GetControlRotation().Yaw + RotationInput * RotationSpeed * DeltaTime;
			NewRotation = fmod(NewRotation, 360.f);
			ControlledPawn->SetSpriteRotation(NewRotation);
			ControlledPawn->SetCameraRotation(NewRotation);
			SetControlRotation(FRotator(0.f, NewRotation, 0.f));

			NewRotation = FMath::DegreesToRadians(NewRotation);
			FVector SortAxis(FMath::Cos(NewRotation), FMath::Sin(NewRotation), 0.f);
			URendererSettings* Settings = GetMutableDefault<URendererSettings>();
			Settings->TranslucentSortAxis = SortAxis.GetSafeNormal();
			Settings->SaveConfig();
			
			RotationInput = 0.f;
		}
	}
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

void ADanmakuPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsLocalController() && GetWorld()->GetNetMode() < ENetMode::NM_Client)
	{
		bClientFinishProceduralGeneration = true;
	}
}

void ADanmakuPlayerController::ServerClientFinishedProcGen_Implementation()
{
	bClientFinishProceduralGeneration = true;
}

void ADanmakuPlayerController::ServerRequestProcGenData_Implementation()
{
	ClientReceiveProcGenData();
}

void ADanmakuPlayerController::ClientReceiveProcGenData_Implementation()
{
	ATileGrid* ClientTileGrid = nullptr;
	for (ATileGrid* TileGrid : TActorRange<ATileGrid>(GetWorld()))
	{
		ClientTileGrid = TileGrid;
		break;
	}

	if (!ClientTileGrid)
	{
		return;
	}

	ClientTileGrid->Generate();
	ServerClientFinishedProcGen();

	if (ADanmakuGameState* GS = GetWorld()->GetGameState<ADanmakuGameState>())
	{
		GS->StartBeginPlay();
	}
}

void ADanmakuPlayerController::PostNetInit()
{
	Super::PostNetInit();

	ServerRequestProcGenData();
}

void ADanmakuPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D InputAxisVector = Value.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		FRotator Rotation = GetControlRotation();
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
	
	RotationInput = InputAxisValue;
}
