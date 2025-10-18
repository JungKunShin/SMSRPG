// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"

#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"

#include "WC_LoginWidget.generated.h"

class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_LoginWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
	const FText& ERROR_ID = FText::FromString(TEXT("아이디 또는 비밀번호가 틀렸습니다."));
	const FText& ERROR_CREATE_PASSWORD = FText::FromString(TEXT("비밀번호는 반드시 숫자나 특수문자가 포함되어야합니다."));
	const FText& ERROR_ID_NUM = FText::FromString(TEXT("아이디는 최소 4글자 이상이여야합니다."));
	const FText& ERROR_PASSWORD_NUM = FText::FromString(TEXT("비밀번호는 최소 4글자 이상이여야합니다."));
	const FText& ERROR_NICKNAME = FText::FromString(TEXT("이미 아이디가 존재합니다."));

private:
	const int MAX_ID_LENGTH = 8;
	const int MIN_ID_LENGTH = 4;
	const int MAX_PASSWORD_LENGTH = 16;
	const int MIN_PASSWORD_LENGTH = 4;
private:
	virtual void NativeConstruct() override;

	//버튼
	UFUNCTION()
	void OnButtonClickMemberShip();

	UFUNCTION()
	void OnButtonClickEnter();

	UFUNCTION()
	void OnButtonClickCreateMemberShip();

	UFUNCTION()
	void OnButtonClickBack();

	//텍스트

	UFUNCTION()
	void OnTextCommittedID(const FText& Text, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnTextChangedID(const FText& NewText);

	UFUNCTION()
	void OnTextCommittedPassWord(const FText& Text, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnTextChangedPassWord(const FText& NewText);


	UFUNCTION()
	void OnTextCommittedCreateID(const FText& Text, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnTextChangedCreateID(const FText& NewText);

	UFUNCTION()
	void OnTextCommittedCreatePassWord(const FText& Text, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnTextChangedCreatePassWord(const FText& NewText);

	UFUNCTION()
	void CheckID(FUserInfo _UserInfo);

	void OnButtonSound();
public:
	//위젯스위처
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher_Login;
	
	//버튼
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* WBPC_Button_MemberShip;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* WBPC_Button_Enter;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* WBPC_Button_CreateMemberShip;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* WBPC_Button_Back;

	//텍스트

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableText_ID;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableText_PassWord;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableText_CreateID;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableText_CreatePassWord;

private:	
	FString InputID; // 입력 아이디
	FString InputPassWord; // 입력 비밀번호
	FString InputCreateID; // 입력 생성할아이디
	FString InputCreatePassWord; // 입력 생성할 비밀번호

public:
	bool IDCheck = false;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
};
