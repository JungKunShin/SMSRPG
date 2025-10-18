#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WC_SMSButton.generated.h"

// OnClicked 바인딩을 중계하기 위한 델리게이트 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class STRONGMETALSTONE_API UWC_SMSButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// 생성 시 UI 구성
	virtual void SynchronizeProperties() override;

	virtual void NativeConstruct() override;

public:
	// 버튼 초기화
	void Init(UTexture2D* icon, FVector3f color);
	void Init(const FText& text, const int32 size);
	void Init(const FText& text, const int32 size, UTexture2D* icon);

	// OnClicked 바인딩 중계 함수
	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnButtonClicked;

private:
	UFUNCTION()
	void HandleInternalClicked();

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* BaseButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ContentBox;

	UPROPERTY(meta = (BindWidget))
	class UImage* ButtonImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;
};
