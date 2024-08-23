// Primey

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */


UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);

	//Tick() 函数是通用的控制器更新逻辑,适用于所有类型的控制器。
	//PlayerTick() 函数则更专注于处理与玩家交互相关的逻辑,只在 PlayerController 中被调用
	virtual void PlayerTick(float DeltaTime) override;

	void LineTraceCursor();
private:
	UPROPERTY(EditAnywhere,Category = Input)
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category = Input)
	TObjectPtr<UInputAction> InputAction;

	TObjectPtr<IEnemyInterface> LastActor = nullptr;
	
	TObjectPtr<IEnemyInterface> ThisActor = nullptr;
};
