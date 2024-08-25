// Primey

#pragma once

#include "CoreMinimal.h"
#include "Charactor/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	virtual void Highlight() override;
	virtual void UnHighlight() override;

protected:
	virtual void BeginPlay() override;
};
