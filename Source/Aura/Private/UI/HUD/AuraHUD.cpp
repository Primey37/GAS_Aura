// Primey


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return OverlayWidgetController;
}
//初始化Widget及其控制器
void AAuraHUD::InitOverlay(UAbilitySystemComponent* ASC, UAttributeSet* AS, APlayerController* PC, APlayerState* PS)
{
	
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller class is not overlappable"));
	checkf(OverlayWidgetClass,TEXT("Overlay Widget class is not overlappable"));
	
	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(),OverlayWidgetClass);
	//初始化控制器
	FWidgetControllerParams WCParams(ASC,AS,PC,PS);
	UOverlayWidgetController* OverlayController = GetOverlayWidgetController(WCParams);
	//设置OverlayWidget控制器
	if(Widget == nullptr) return;
	Widget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BindCallbacksToDependencies();
	OverlayController->BroadcastInitialValues();

	Widget->AddToViewport();
}


