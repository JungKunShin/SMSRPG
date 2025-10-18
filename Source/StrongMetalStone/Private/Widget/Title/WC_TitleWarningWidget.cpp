// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/WC_TitleWarningWidget.h"
#include "Widget/Title/WC_TitleWidget.h"
#include "Widget/WC_SMSButton.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"


void UWC_TitleWarningWidget::NativeConstruct()
{
	Super::NativeConstruct();	

	if (Button_Back)
	{
		// 버튼 초기화
		Button_Back->Init(FText::FromString(TEXT("뒤로")), 20);

		// 함수 이벤트 바인딩
		Button_Back->OnButtonClicked.AddDynamic(this, &UWC_TitleWarningWidget::OnButton_Back);
	}	
}

void UWC_TitleWarningWidget::SetWarningMessage(const FText& _Text)
{
	TextBlock_Warning->SetText(_Text);

	Cast<AC_TitleHUD>(GetMyHUD())->SetTitleWidgetSwitcherIndex(4);	
}

void UWC_TitleWarningWidget::OnButton_Back()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}

	AC_TitleHUD* TempHUD = Cast<AC_TitleHUD>(GetMyHUD());
	TempHUD->SetTitleWidgetSwitcherIndex(TempHUD->TitleWidget->PreWidgetNum);
}

