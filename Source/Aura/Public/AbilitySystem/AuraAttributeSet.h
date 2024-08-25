// Primey

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	//注册网络复制的属性
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//设置网络更新后的属性和调用的函数
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_Health,Category = "Vital Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_MaxHealth,Category = "Vital Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_Mana,Category = "Vital Attribute")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing= OnRep_MaxMana,Category = "Vital Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);




	//网络复制后调用
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
};
