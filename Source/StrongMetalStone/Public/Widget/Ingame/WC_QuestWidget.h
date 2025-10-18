#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_QuestWidget.generated.h"

class UTextBlock;
class AC_SMSQuest;
class UWC_SMSButton;

UCLASS()
class STRONGMETALSTONE_API UWC_QuestWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OnDenyButtonClicked(); // ���� ��ư

	UFUNCTION()
	void OnAcceptButtonClicked(); // ���� ��ư

	UFUNCTION()
	void OnRewardButtonClicked(); // ���� ��ư

	UFUNCTION()
	void OnGiveUpButtonClicked(); // ���� ��ư

	void SetText(AC_SMSQuest* Quest);
public:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* AcceptButton;	// ���� ��ư

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* DenyButton;	// ���� ��ư

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* RewardButton;	// ����ȹ�� ��ư

	UPROPERTY(meta=(BindWidget))
	UWC_SMSButton* GiveUpButton;	// ���� ��ư

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestTitle;					// Quest���� �ؽ�Ʈ �ڽ�

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestInfo;						// Quest���� �ؽ�Ʈ �ڽ�

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestReward;					// Quest���� �ؽ�Ʈ �ڽ�

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestCompletedCondition;		// Quest���� �ؽ�Ʈ �ڽ�

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_Accept;		// ���� �ؽ�Ʈ �ڽ�

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_Deny;		// ���� �ؽ�Ʈ �ڽ�

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_Reward;		// ����ȹ�� �ؽ�Ʈ �ڽ�

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_GiveUp;		// ����ȹ�� �ؽ�Ʈ �ڽ�

	AC_SMSQuest* CurQuest;							// ���� Quest

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* BeginSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* CancelSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* GiveUpSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* RewardSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AcceptSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UDA_ItemData* DarkSword;
};
