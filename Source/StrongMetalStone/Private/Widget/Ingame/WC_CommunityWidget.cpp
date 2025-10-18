// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_CommunityWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "HUD/C_WorldHUD.h"
#include "Component/C_PartySystemComponent.h"

void UWC_CommunityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//파티초대
	if (Button_Party)
	{
		// 버튼 초기화
		Button_Party->Init(FText::FromString(TEXT("파티초대")), 20);

		// 함수 이벤트 바인딩
		Button_Party->OnButtonClicked.AddDynamic(this, &UWC_CommunityWidget::OnButtonParty);
	}

	//싸우자
	if (Button_Fight)
	{
		// 버튼 초기화
		Button_Fight->Init(FText::FromString(TEXT("싸우자")), 20);

		// 함수 이벤트 바인딩
		Button_Fight->OnButtonClicked.AddDynamic(this, &UWC_CommunityWidget::OnButtonFight);
	}

	//닫기
	if (Button_Exit)
	{
		// 버튼 초기화
		Button_Exit->Init(FText::FromString(TEXT("닫기")), 20);

		// 함수 이벤트 바인딩
		Button_Exit->OnButtonClicked.AddDynamic(this, &UWC_CommunityWidget::OnButtonExit);
	}

	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}

}

void UWC_CommunityWidget::OnButtonParty()
{
	AC_PlayerCharacter* CurCharacter= CastWCharacter(GetMyCharacter());	
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, CurCharacter->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
	CurCharacter->PartySytemComponent->ServerOpenPartyInviteWidget(CurCharacter, CurCharacter->SelectPlayerCharacter);
	OnButtonExit();
}

void UWC_CommunityWidget::OnButtonFight()
{
	AC_PlayerCharacter* CurCharacter = CastWCharacter(GetMyCharacter());

	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, CurCharacter->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
	CurCharacter->ClientSetEnemy(CurCharacter->SelectPlayerCharacter);
	CurCharacter->ServerSetEnemy(CurCharacter->SelectPlayerCharacter);
	OnButtonExit();
}

void UWC_CommunityWidget::OnButtonExit()
{	
	AC_PlayerCharacter* CurCharacter = CastWCharacter(GetMyCharacter());

	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, CurCharacter->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
	RemoveFromParent();	
	CastWHUD(GetMyHUD())->SetInputMode(EInputMode::GameOnly, false);
	CurCharacter->bOnMouse = false;
}
