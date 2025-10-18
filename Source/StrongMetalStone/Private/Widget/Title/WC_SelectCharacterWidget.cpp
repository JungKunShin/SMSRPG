// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/WC_SelectCharacterWidget.h"
#include "Widget/WC_SMSButton.h"
#include "PlayerController/C_TitlePlayerController.h"
#include "Widget/Title/WC_TitleWidget.h"
#include "C_SMSGameInstance.h"
#include "Character/C_PlayerCharacter.h"
#include "HUD/C_TitleHUD.h"


void UWC_SelectCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//시작
	if (Button_Start)
	{
		// 버튼 초기화
		Button_Start->Init(FText::FromString(TEXT("시작")), 20);

		// 함수 이벤트 바인딩
		Button_Start->OnButtonClicked.AddDynamic(this, &UWC_SelectCharacterWidget::OnButtonStart);
	}

	//나가기
	if (Button_End)
	{
		// 버튼 초기화
		Button_End->Init(FText::FromString(TEXT("나가기")), 20);

		// 함수 이벤트 바인딩
		Button_End->OnButtonClicked.AddDynamic(this, &UWC_SelectCharacterWidget::OnButtonEnd);
	}

	//캐릭터 생성
	if (Button_CreateCharacter)
	{
		// 버튼 초기화
		Button_CreateCharacter->Init(FText::FromString(TEXT("캐릭터 생성")), 20);

		// 함수 이벤트 바인딩
		Button_CreateCharacter->OnButtonClicked.AddDynamic(this, &UWC_SelectCharacterWidget::OnButtonCreateCharacter);
	}

	//캐릭터 삭제
	if (Button_DeleteCharacter)
	{
		// 버튼 초기화
		Button_DeleteCharacter->Init(FText::FromString(TEXT("캐릭터 삭제")), 20);

		// 함수 이벤트 바인딩
		Button_DeleteCharacter->OnButtonClicked.AddDynamic(this, &UWC_SelectCharacterWidget::OnButtonDeleteCharacter);
	}
}


void UWC_SelectCharacterWidget::OnButtonStart()
{
	OnButtonSound();

	//선택한 캐릭터가 없을 때
	if (!Cast<AC_TitlePlayerController>(GetMyPC())->SelectCharacter)
	{
		Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_SELECT_CHARACTER);
		return;
	}

	CastWGI(GetMyGI())->CharacterInfo = Cast<AC_TitlePlayerController>(GetMyPC())->SelectCharacter->CharacterInfo;
	FCharacterInfo DebugInfo = CastWGI(GetMyGI())->CharacterInfo;
	UGameplayStatics::OpenLevel(GetWorld(), FName(GetLevelIP(LevelPort)));
}

void UWC_SelectCharacterWidget::OnButtonEnd()
{
	OnButtonSound();

	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UWC_SelectCharacterWidget::OnButtonCreateCharacter()
{
	OnButtonSound();

	Cast<AC_TitleHUD>(GetMyHUD())->SetTitleWidgetSwitcherIndex(2);
}

void UWC_SelectCharacterWidget::OnButtonDeleteCharacter()
{
	OnButtonSound();

	if (!Cast<AC_TitlePlayerController>(GetMyPC())->SelectCharacter) return;
	Cast<AC_SMSPlayerController>(GetMyPC())->ServerDeleteCharacterInfoCSV(Cast<AC_TitlePlayerController>(GetMyPC())->SelectCharacter->CharacterInfo);
	Cast<AC_TitlePlayerController>(GetMyPC())->SelectCharacter->Destroy();
	Cast<AC_TitlePlayerController>(GetMyPC())->SelectCharacter = nullptr;
}

void UWC_SelectCharacterWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
