// Primey


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,1);
	}
	

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI Input;
	//可以在游戏外使用鼠标，不被局限于游戏内
	Input.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//即使鼠标有行为被捕获仍显示
	Input.SetHideCursorDuringCapture(false);
	SetInputMode(Input);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//跟项目设置中的Default Classes有关，设定了InputComponent的实际类型
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(InputAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D Vector2D = Value.Get<FVector2D>();
	const FRotator Rotator = GetControlRotation();
	const FRotator NewRotator(0.f,Rotator.Pitch,0.f);
	const FVector ForwardVector = FRotationMatrix(NewRotator).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(NewRotator).GetUnitAxis(EAxis::Y);
	if(APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardVector,Vector2D.Y);
		ControllerPawn->AddMovementInput(RightVector,Vector2D.X);
	}
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	LineTraceCursor();
}

void AAuraPlayerController::LineTraceCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	if(!HitResult.bBlockingHit)return;
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(HitResult.GetActor());
	if(LastActor == nullptr)
	{
		if(ThisActor != nullptr)
		{
			ThisActor->Highlight();
		}
	}
	else
	{
		if(ThisActor != nullptr&&LastActor != ThisActor)
		{
			LastActor->UnHighlight();
			ThisActor->Highlight();
		}
		else if(ThisActor == nullptr)
		{
			LastActor->UnHighlight();
		}
	}
}




