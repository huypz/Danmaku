// Copyright Huy Phan. All Rights Reserved.


#include "Player/DanmakuPlayerController.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Actor/DanmakuActorInterface.h"
#include "Engine/RendererSettings.h"
#include "Game/DanmakuGameState.h"
#include "Player/DanmakuPlayerCameraManager.h"
#include "TileMap/TileGrid.h"

ADanmakuPlayerController::ADanmakuPlayerController()
{
	CameraRotation = 0.f;
	
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
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttack(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Attack.IA_Attack'"));
	if (InputActionAttack.Succeeded())
	{
		AttackAction = InputActionAttack.Object;
	}
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
	
	if (APawn* CurrentPawn = GetPawn<APawn>())
	{
		for (AActor* Actor : TActorRange<AActor>(GetWorld()))
		{
			if (Actor->GetClass()->ImplementsInterface(UDanmakuActorInterface::StaticClass()))
			{
				IDanmakuActorInterface::Execute_UpdateRotation(Actor, CurrentPawn->GetActorLocation(), CameraRotation);
			}
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
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ADanmakuPlayerController::Attack);
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
	
	const FRotator Rotation(0.f, CameraRotation, 0.f);
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
	
	const float Value = InputActionValue.Get<float>() * 200.f * FApp::GetDeltaTime();
	if (Value != 0.f)
	{

		CameraRotation += Value;
	}
}

void ADanmakuPlayerController::Attack(const FInputActionValue& InputActionValue)
{
	APawn* CurrentPawn = GetPawn<APawn>();
	if (!CurrentPawn)
	{
		return;
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
