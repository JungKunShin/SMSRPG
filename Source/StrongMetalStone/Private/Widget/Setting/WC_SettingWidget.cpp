// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Setting/WC_SettingWidget.h"
#include "Widget/WC_SMSButton.h"
#include "HUD/C_WorldHUD.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void UWC_SettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// 창 닫기 버튼 초기화
	WBPC_SMSButton_Close->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/Delete")), FVector3f(1.f, 1.f, 1.f));
	// 창 닫기 버튼에 함수 바인딩
	WBPC_SMSButton_Close->OnButtonClicked.AddDynamic(this, &UWC_SettingWidget::OnCloseButtonClicked);

	// 게임 버튼 초기화
	WBPC_SMSButton_Game->Init(FText::FromString(TEXT("게임")), 15);
	// 게임 버튼에 함수 바인딩
	WBPC_SMSButton_Game->OnButtonClicked.AddDynamic(this, &UWC_SettingWidget::OnGameButtonClicked);

	// 사운드 버튼 초기화
	WBPC_SMSButton_Sound->Init(FText::FromString(TEXT("사운드")), 15);
	// 사운드 버튼에 함수 바인딩
	WBPC_SMSButton_Sound->OnButtonClicked.AddDynamic(this, &UWC_SettingWidget::OnSoundButtonClicked);

}

void UWC_SettingWidget::OnCloseButtonClicked()
{
	AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (WorldHUD)
	{
		WorldHUD->SetSettingWidgetVisible(false);
	}

	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_SettingWidget::OnGameButtonClicked()
{
	WidgetSwitcher_Setting->SetActiveWidgetIndex(0);

	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_SettingWidget::OnSoundButtonClicked()
{
	WidgetSwitcher_Setting->SetActiveWidgetIndex(1);


	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_SettingWidget::OnSaveButtonClicked()
{
}


