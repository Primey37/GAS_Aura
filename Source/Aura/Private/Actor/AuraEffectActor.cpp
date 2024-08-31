// Primey


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (AbilitySystemComponent == nullptr) return;
	check(EffectClass);
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass,1.0f,EffectContextHandle);
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	const EGameplayEffectDurationType EffectDurationPolicy =  SpecHandle.Data.Get()->Def.Get()->DurationPolicy;
	if(EffectDurationPolicy == EGameplayEffectDurationType::Infinite&&
		(InfinityApplicationPolicy != EEffectApplicationPolicy::DoNotApply||
		DurationEffectsApplicationPolicy != EEffectApplicationPolicy::DoNotApply))
	{
		//后面要移除的话就需要保存
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle,AbilitySystemComponent);
	}
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}


void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if(InstanceApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstanceGameplayEffectClass);
	}
	if(DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if(InfinityApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfinityGameplayEffectClass);
	}
	if(!DurationEffects.IsEmpty())
	{
		for(auto Effect : DurationEffects)
		{
			if(Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
			{
				ApplyEffectToTarget(TargetActor,Effect.DurationEffectClass);
			}
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(InstanceApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstanceGameplayEffectClass);
	}
	if(DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if(InfinityApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfinityGameplayEffectClass);
	}
	if(!DurationEffects.IsEmpty())
	{
		for(auto Effect : DurationEffects)
		{
			if(Effect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
			{
				ApplyEffectToTarget(TargetActor,Effect.DurationEffectClass);
			}
		}
	}

	//去除效果,根据TargetActor来去除GE
	if(RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(AbilitySystemComponent)) return;

		TArray<FActiveGameplayEffectHandle> RemovedHandles;
		for(auto ActiveHandle:ActiveEffectHandles)
		{
			if(ActiveHandle.Value == AbilitySystemComponent)
			{
				AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveHandle.Key,1);
				RemovedHandles.Add(ActiveHandle.Key);
			}
		}
		for(auto RemovedHandle:RemovedHandles)
		{
			ActiveEffectHandles.FindAndRemoveChecked(RemovedHandle);
		}
	}
}




