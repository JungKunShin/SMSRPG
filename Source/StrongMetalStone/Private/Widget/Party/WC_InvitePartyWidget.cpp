// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Party/WC_InvitePartyWidget.h"
#include "Widget/WC_SMSButton.h"
#include "HUD/C_WorldHUD.h"
#include "Character/C_PlayerCharacter.h"
#include "Component/C_PartySystemComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

void UWC_InvitePartyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Yes)
	{
		// 버튼 초기화
		Button_Yes->Init(FText::FromString(TEXT("수 락")), 15);

		// 함수 이벤트 바인딩
		Button_Yes->OnButtonClicked.AddDynamic(this, &UWC_InvitePartyWidget::OnButtonYes);
	}

	if (Button_No)
	{
		// 버튼 초기화
		Button_No->Init(FText::FromString(TEXT("거 절")), 15);
		// 함수 이벤트 바인딩
		Button_No->OnButtonClicked.AddDynamic(this, &UWC_InvitePartyWidget::OnButtonNo);
	}

	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (BeginSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, BeginSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_InvitePartyWidget::OnButtonYes()
{	
	if (CastWCharacter(GetMyCharacter())->PartyInfo.InParty)return;

	CastWCharacter(GetMyCharacter())->PartySytemComponent->ServerCreateParty(Inviter);

	InviteParty();

	RemoveFromParent();

	AC_PlayerCharacter* CurCharacter = CastWCharacter(GetMyCharacter());	
	CastWHUD(GetMyHUD())->SetInputMode(EInputMode::GameOnly, false);
	CurCharacter->bOnMouse = false;

	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, CurCharacter->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_InvitePartyWidget::OnButtonNo()
{
	RemoveFromParent();

	AC_PlayerCharacter* CurCharacter = CastWCharacter(GetMyCharacter());
	CastWHUD(GetMyHUD())->SetInputMode(EInputMode::GameOnly, false);
	CurCharacter->bOnMouse = false;


	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, CurCharacter->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_InvitePartyWidget::InviteParty()
{
	CastWCharacter(GetMyCharacter())->PartySytemComponent->ServerPartyAddCharacter(Inviter, CastWCharacter(GetMyCharacter()));
}


