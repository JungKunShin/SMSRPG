#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WC_SMSButton.generated.h"

// OnClicked ���ε��� �߰��ϱ� ���� ��������Ʈ 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class STRONGMETALSTONE_API UWC_SMSButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// ���� �� UI ����
	virtual void SynchronizeProperties() override;

	virtual void NativeConstruct() override;

public:
	// ��ư �ʱ�ȭ
	void Init(UTexture2D* icon, FVector3f color);
	void Init(const FText& text, const int32 size);
	void Init(const FText& text, const int32 size, UTexture2D* icon);

	// OnClicked ���ε� �߰� �Լ�
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
