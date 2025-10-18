// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Widget/WC_SMSProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "WC_OnePartyWidget.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_OnePartyWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

public:
	UWC_OnePartyWidget();
	virtual void NativeConstruct() override;
	void SetWidget();

	void HpBarUpdate(float percent);
public:
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Owner;

	FString NickName;
	EPlayerJob job;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_NickName;

	UPROPERTY(meta = (BindWidget))

	UImage* Image_Job;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSProgressBar* WBPC_SMSProgressBar_HP; //��Ƽü��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Owner, meta = (AllowPrivateAccess = "true"))
	UTexture2D* WarriorImage; //���� �̹���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Owner, meta = (AllowPrivateAccess = "true"))
	UTexture2D* MageImage; //������ �̹���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Owner, meta = (AllowPrivateAccess = "true"))
	UTexture2D* HealerImage; //���� �̹���

};
