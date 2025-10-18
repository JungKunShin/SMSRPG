// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/WC_LoginWidget.h"
#include "HUD/C_TitleHUD.h"
#include "Widget/Title/WC_TitleWidget.h"
#include "Widget/WC_SMSButton.h"
#include "PlayerController/C_SMSPlayerController.h"
#include "C_SMSGameInstance.h"

void UWC_LoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼
	// 회원가입
	if (WBPC_Button_MemberShip)
	{
		// 버튼 초기화
		WBPC_Button_MemberShip->Init(FText::FromString(TEXT("회원가입")), 15);

		// 함수 이벤트 바인딩
		WBPC_Button_MemberShip->OnButtonClicked.AddDynamic(this, &UWC_LoginWidget::OnButtonClickMemberShip);
	}

	//입장
	if (WBPC_Button_Enter)
	{
		// 버튼 초기화
		WBPC_Button_Enter->Init(FText::FromString(TEXT("입장")), 15);

		// 함수 이벤트 바인딩
		WBPC_Button_Enter->OnButtonClicked.AddDynamic(this, &UWC_LoginWidget::OnButtonClickEnter);
	}

	//아이디생성
	if (WBPC_Button_CreateMemberShip)
	{
		// 버튼 초기화
		WBPC_Button_CreateMemberShip->Init(FText::FromString(TEXT("가입")), 15);

		// 함수 이벤트 바인딩
		WBPC_Button_CreateMemberShip->OnButtonClicked.AddDynamic(this, &UWC_LoginWidget::OnButtonClickCreateMemberShip);
	}

	//뒤로
	if (WBPC_Button_Back)
	{
		// 버튼 초기화
		WBPC_Button_Back->Init(FText::FromString(TEXT("뒤로")), 15);

		// 함수 이벤트 바인딩
		WBPC_Button_Back->OnButtonClicked.AddDynamic(this, &UWC_LoginWidget::OnButtonClickBack);
	}


	//텍스트
	EditableText_ID->OnTextCommitted.AddDynamic(this, &UWC_LoginWidget::OnTextCommittedID);
	EditableText_ID->OnTextChanged.AddDynamic(this, &UWC_LoginWidget::OnTextChangedID);

	EditableText_PassWord->OnTextCommitted.AddDynamic(this, &UWC_LoginWidget::OnTextCommittedPassWord);
	EditableText_PassWord->OnTextChanged.AddDynamic(this, &UWC_LoginWidget::OnTextChangedPassWord);

	EditableText_CreateID->OnTextCommitted.AddDynamic(this, &UWC_LoginWidget::OnTextCommittedCreateID);
	EditableText_CreateID->OnTextChanged.AddDynamic(this, &UWC_LoginWidget::OnTextChangedCreateID);

	EditableText_CreatePassWord->OnTextCommitted.AddDynamic(this, &UWC_LoginWidget::OnTextCommittedCreatePassWord);
	EditableText_CreatePassWord->OnTextChanged.AddDynamic(this, &UWC_LoginWidget::OnTextChangedCreatePassWord);
}

//회원가입 버튼
void UWC_LoginWidget::OnButtonClickMemberShip()
{
	OnButtonSound(); // 버튼 소리

	WidgetSwitcher_Login->SetActiveWidgetIndex(1);
	Cast<AC_TitleHUD>(GetMyHUD())->TitleWidget->TextInit();
}
// 입장 버튼
void UWC_LoginWidget::OnButtonClickEnter()
{

	Cast<AC_SMSPlayerController>(GetMyPC())->ServerLoadUserInfoFromCSV();

	for (FUserInfo userInfo :CastWGI(GetMyGI())->UserInfoDatas)
	{
		if (userInfo.ID == InputID)
		{
			if (userInfo.PassWord == InputPassWord)
			{
				//캐릭터 선택창으로 이동시키기
				CastWGI(GetMyGI())->UserInfo.ID = userInfo.ID;
				Cast<AC_SMSPlayerController>(GetMyPC())->ServerLoadPlayerInfoFromCSV();
				Cast<AC_TitleHUD>(GetMyHUD())->SetTitleWidgetSwitcherIndex(1);			
				return;
			}
		}
	}	

	//아이디 비번 입력이 틀렸다는 위젯 출력
	Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_ID);
}

//아이디 생성 버튼
void UWC_LoginWidget::OnButtonClickCreateMemberShip()
{
	OnButtonSound(); // 버튼 소리

	FUserInfo TempUserInfo;
	if (InputCreateID.Len() < MIN_ID_LENGTH)
	{
		//아이디 최소 글자수 제한 경고 위젯 띄우기
		Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_ID_NUM);
		return;
	}
	else if (InputCreatePassWord.Len() < MIN_PASSWORD_LENGTH)
	{
		//비밀번호 최소 글자수 제한 경고 위젯 띄우기
		Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_PASSWORD_NUM);
		return;
	}

	const FRegexPattern RequirePattern(TEXT("(?=.*[0-9!@#\\$%\\^&\\*\\(\\)_\\+])"));
	FRegexMatcher Matcher(RequirePattern, InputCreatePassWord);
	if (!Matcher.FindNext())
	{
		//숫자나 특수문자 포함 경고 위젯 띄우기
		Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_CREATE_PASSWORD);
		return;
	}

	TempUserInfo.ID = InputCreateID;
	TempUserInfo.PassWord = InputCreatePassWord;
	TempUserInfo.GUID = FGuid::NewGuid();

	Cast<AC_SMSPlayerController>(GetMyPC())->ServerCheckIDFromCSV(TempUserInfo.ID);

	FTimerHandle LoginTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(LoginTimerHandle, [this, TempUserInfo]()
		{
			CheckID(TempUserInfo);
		}, 0.2f, false);

}

//뒤로 버튼
void UWC_LoginWidget::OnButtonClickBack()
{
	OnButtonSound(); // 버튼 소리

	WidgetSwitcher_Login->SetActiveWidgetIndex(0);
	Cast<AC_TitleHUD>(GetMyHUD())->TitleWidget->TextInit();
}

//아이디 타이핑 완료
void UWC_LoginWidget::OnTextCommittedID(const FText& Text, ETextCommit::Type CommitType)
{
	InputID = Text.ToString();
	if (CommitType == ETextCommit::OnEnter)
	{
		OnButtonClickEnter();
	}
}

//아이디 입력값 바뀔때마다 호출
void UWC_LoginWidget::OnTextChangedID(const FText& NewText)
{
	InputID = NewText.ToString();
	if (InputID.Len() <= 0)return;

	//정규식, 영어와 숫자로만 입력 가능하게
	const FRegexPattern Pattern(TEXT("^[A-Za-z0-9]*$"));

	EditableText_ID->SetText((LimitString(NewText, Pattern,true)));	


	if (InputID.Len() >= MAX_ID_LENGTH)
	{
		EditableText_ID->SetText(FText::FromString(InputID.Left(MAX_ID_LENGTH)));
		return;
	}
}

//비밀번호 타이핑 완료
void UWC_LoginWidget::OnTextCommittedPassWord(const FText& Text, ETextCommit::Type CommitType)
{
	InputPassWord = Text.ToString();
	if (CommitType == ETextCommit::OnEnter)
	{
		OnButtonClickEnter();
	}
}

//비밀번호 입력값 바뀔때마다 호출
void UWC_LoginWidget::OnTextChangedPassWord(const FText& NewText)
{
	InputPassWord = NewText.ToString();
	if (InputPassWord.Len() <= 0)return;

	//한글 입력 불가능하게
	const FRegexPattern Pattern(TEXT("^[가-힣ㄱ-ㅎㅏ-ㅣ]*$"));

	EditableText_PassWord->SetText((LimitString(NewText, Pattern)));


	if (InputPassWord.Len() >= MAX_PASSWORD_LENGTH)
	{
		EditableText_PassWord->SetText(FText::FromString(InputPassWord.Left(MAX_PASSWORD_LENGTH)));
	}
}

//아이디 생성 타이핑 완료
void UWC_LoginWidget::OnTextCommittedCreateID(const FText& Text, ETextCommit::Type CommitType)
{
	InputCreateID = Text.ToString();
	if (CommitType == ETextCommit::OnEnter)
	{
		OnButtonClickCreateMemberShip();
	}
}

//아이디 생성 때 입력값 바뀔때마다 호출
void UWC_LoginWidget::OnTextChangedCreateID(const FText& NewText)
{
	InputCreateID = NewText.ToString();
	if (InputCreateID.Len() <= 0)return;

	//정규식, 영어와 숫자로만 입력 가능하게
	const FRegexPattern Pattern(TEXT("^[A-Za-z0-9]*$"));

	EditableText_CreateID->SetText((LimitString(NewText, Pattern,true)));


	if (InputCreateID.Len() >= MAX_ID_LENGTH)
	{
		EditableText_CreateID->SetText(FText::FromString(InputCreateID.Left(MAX_ID_LENGTH)));
	}
}

//비밀번호 생성 타이핑 완료
void UWC_LoginWidget::OnTextCommittedCreatePassWord(const FText& Text, ETextCommit::Type CommitType)
{
	InputCreatePassWord = Text.ToString();

	if (CommitType == ETextCommit::OnEnter)
	{
		OnButtonClickCreateMemberShip();
	}
}


//비밀번호 생성때 입력값 바뀔떄마다 호출
void UWC_LoginWidget::OnTextChangedCreatePassWord(const FText& NewText)
{
	InputCreatePassWord = NewText.ToString();

	if (InputCreatePassWord.Len() <= 0)return;

	//한글 입력 불가능하게
	const FRegexPattern Pattern(TEXT("^[가-힣ㄱ-ㅎㅏ-ㅣ]*$"));
	
	EditableText_CreatePassWord->SetText(LimitString(NewText, Pattern));


	if (InputCreatePassWord.Len() >= MAX_PASSWORD_LENGTH)
	{
		EditableText_CreatePassWord->SetText(FText::FromString(InputCreatePassWord.Left(MAX_PASSWORD_LENGTH)));
	}
}

void UWC_LoginWidget::CheckID(FUserInfo _UserInfo)
{
	if (IDCheck)
	{
		//아이디 CSV에 저장
		Cast<AC_SMSPlayerController>(GetMyPC())->ServerAddUserInfoToCSV(_UserInfo);
		Cast<AC_SMSPlayerController>(GetMyPC())->ServerLoadUserInfoFromCSV();

		IDCheck = false;
		OnButtonClickBack();
	}
	else
	{
		Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_NICKNAME);
	}

}

void UWC_LoginWidget::OnButtonSound()
{
	AC_SMSPlayerController* SMSController = Cast< AC_SMSPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!SMSController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, SMSController->GetPawn()->GetActorLocation(), SMSController->SoundManager->EffectVolume, 1.0f);
	}
}
