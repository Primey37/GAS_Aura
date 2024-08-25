// Primey

#pragma once

#include "CoreMinimal.h"
#include "Charactor/AuraCharacterBase.h"
#include "AuraPlayer.generated.h"
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayer : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraPlayer();
	
	virtual void PossessedBy(AController* NewOwner) override;
	virtual void OnRep_PlayerState() override;
	
protected:
	UPROPERTY(VisibleAnywhere,Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere,Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

private:
	void InitAbilityActorInfo();
};
