// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_ResultWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Widget/Ingame/WC_ResultCharacterWidget.h"
#include "C_SMSGameInstance.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/C_PlayerCharacter.h"

void UWC_ResultWidget::NativeConstruct()
{
	// 필드복귀 버튼 초기화
	BackButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/btn_icon_home_3.btn_icon_home_3")),FVector3f(1.0f,1.0f,1.0f));
	// 필드복귀 버튼에 함수 바인딩
	BackButton->OnButtonClicked.AddDynamic(this, &UWC_ResultWidget::OnBackButtonClicked);
}

void UWC_ResultWidget::OnBackButtonClicked()
{
	// 필드 레벨로 이동
	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	Cast<AC_SMSPlayerController>(GetMyPC())->ServerSetIsExit(false);
	CastWGI(GetMyGI())->PartyData.PartyPlayersName.Empty();
	CastWGI(GetMyGI())->PartyInfo.PartyPlayers.Empty();
	CastWGI(GetMyGI())->PartyData.InParty = false;
	CastWGI(GetMyGI())->PartyInfo.InParty = false;
	
	//RemoveFromParent();

	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetLevelIP(PortNum)));
}

void UWC_ResultWidget::SetText(FString Boss)
{
	TEXT_DefeatTitle->SetText(FText::FromString(Boss));
}

void UWC_ResultWidget::SetCharacter(UWC_ResultCharacterWidget* Result)
{
	PartyInfo->AddChild(Result);
	PartyInfo->bAnimateWheelScrolling = true;
}
