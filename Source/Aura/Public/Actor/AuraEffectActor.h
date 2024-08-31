// Primey

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

USTRUCT(BlueprintType)
struct FDurationEffectType
{
	GENERATED_BODY()
	FDurationEffectType(){};
	FDurationEffectType(TSubclassOf<UGameplayEffect> DurationEffectClass,EEffectApplicationPolicy ApplicationPolicy)
	:DurationEffectClass(DurationEffectClass),ApplicationPolicy(ApplicationPolicy)
	{};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DurationEffectClass = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EEffectApplicationPolicy ApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AAuraEffectActor();

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);
protected:
	virtual void BeginPlay() override;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Applied Effect")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effect")
	EEffectApplicationPolicy InstanceApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Applied Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effect")
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effect")
	TSubclassOf<UGameplayEffect> InfinityGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effect")
	EEffectApplicationPolicy InfinityApplicationPolicy = EEffectApplicationPolicy::DoNotApply;



	UFUNCTION(BlueprintCallable,Category = "Game Effect")
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable,Category = "Game Effect")
	void OnEndOverlap(AActor* TargetActor);

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;

	//实现多重效果的数组，效果是一起生效，取消也是一起取消的
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effect")
	TArray<FDurationEffectType> DurationEffects;

	//决定这个数组的Policy
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effect")
	EEffectApplicationPolicy DurationEffectsApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	//根据这个决定是否取消
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Applied Effect")
	EEffectRemovalPolicy RemovalPolicy = EEffectRemovalPolicy::DoNotRemove;
};
