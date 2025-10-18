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
	void OnDenyButtonClicked(); // 거절 버튼

	UFUNCTION()
	void OnAcceptButtonClicked(); // 수락 버튼

	UFUNCTION()
	void OnRewardButtonClicked(); // 보상 버튼

	UFUNCTION()
	void OnGiveUpButtonClicked(); // 보상 버튼

	void SetText(AC_SMSQuest* Quest);
public:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* AcceptButton;	// 수락 버튼

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* DenyButton;	// 거절 버튼

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* RewardButton;	// 보상획득 버튼

	UPROPERTY(meta=(BindWidget))
	UWC_SMSButton* GiveUpButton;	// 포기 버튼

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestTitle;					// Quest제목 텍스트 박스

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestInfo;						// Quest정보 텍스트 박스

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestReward;					// Quest보상 텍스트 박스

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_QuestCompletedCondition;		// Quest보상 텍스트 박스

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_Accept;		// 수락 텍스트 박스

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_Deny;		// 거절 텍스트 박스

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_Reward;		// 보상획득 텍스트 박스

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_GiveUp;		// 보상획득 텍스트 박스

	AC_SMSQuest* CurQuest;							// 현재 Quest

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
