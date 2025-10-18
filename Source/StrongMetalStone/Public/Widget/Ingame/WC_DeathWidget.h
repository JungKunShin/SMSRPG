#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_DeathWidget.generated.h"

UCLASS()
class STRONGMETALSTONE_API UWC_DeathWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OnReviveButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
	class UWC_SMSButton* WBPC_SMSButton_Revive;  // 부활 버튼
	
};
