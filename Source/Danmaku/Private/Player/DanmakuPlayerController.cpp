// Copyright Huy Phan. All Rights Reserved.


#include "Player/DanmakuPlayerController.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Game/DanmakuGameState.h"
#include "Player/DanmakuPlayerCameraManager.h"
#include "TileMap/TileGrid.h"

ADanmakuPlayerController::ADanmakuPlayerController()
{
	bClientFinishedProceduralGeneration = false;
	bShowMouseCursor = true;

	PlayerCameraManagerClass = ADanmakuPlayerCameraManager::StaticClass();
	
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Danmaku.IMC_Danmaku'"));
	if (InputMappingContext.Succeeded())
	{
		DefaultContext = InputMappingContext.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Move.IA_Move'"));
	if (InputActionMove.Succeeded())
	{
		MoveAction = InputActionMove.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRotate(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Rotate.IA_Rotate'"));
	if (InputActionRotate.Succeeded())
	{
		RotateAction = InputActionRotate.Object;
	}
}

FMatrix ADanmakuPlayerController::GetCameraProjectionMatrix()
{
	FMatrix ProjectionMatrix;

	if( GetLocalPlayer() != nullptr )
	{
		FSceneViewProjectionData PlayerProjectionData;
		GetLocalPlayer()->GetProjectionData(GetLocalPlayer()->ViewportClient->Viewport,PlayerProjectionData );
		ProjectionMatrix = PlayerProjectionData.ProjectionMatrix;
	}

	return ProjectionMatrix;
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
	
	SetControlRotation(FRotator(0.f, -90.f, 0.f));
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

void ADanmakuPlayerController::Move(const FInputActionValue& InputActionValue)
{
	APawn* CurrentPawn = GetPawn<APawn>();
	if (!CurrentPawn)
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();
	
	const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
	if (Value.X != 0.f)
	{
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		CurrentPawn->AddMovementInput(RightDirection, Value.X);
	}
	if (Value.Y != 0.f)
	{
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		CurrentPawn->AddMovementInput(ForwardDirection, Value.Y);
	}
}

void ADanmakuPlayerController::Rotate(const FInputActionValue& InputActionValue)
{
	APawn* CurrentPawn = GetPawn<APawn>();
	if (!CurrentPawn)
	{
		return;
	}
	
	const float Value = InputActionValue.Get<float>() * 75.f * FApp::GetDeltaTime();
	if (Value != 0.f)
	{
		CurrentPawn->AddControllerYawInput(Value);
	}
}

void ADanmakuPlayerController::ServerClientFinishedProcGen_Implementation()
{
	bClientFinishedProceduralGeneration = true;
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

	if (ADanmakuGameState* GameState = GetWorld()->GetGameState<ADanmakuGameState>())
	{
		GameState->StartBeginPlay();
	}
}

void ADanmakuPlayerController::PostNetInit()
{
	Super::PostNetInit();

	ServerRequestProcGenData();
}

void ADanmakuPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsLocalController() && GetWorld()->GetNetMode() < ENetMode::NM_Client)
	{
		bClientFinishedProceduralGeneration = true;
	}
}
