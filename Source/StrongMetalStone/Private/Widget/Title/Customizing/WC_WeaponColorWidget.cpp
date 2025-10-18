// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_WeaponColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_WeaponColorWidget::NativeConstruct()
{
	// 빨강 버튼 초기화
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_weapon.icon_weapon")), FVector3f(1.f, 1.f, 1.f));
	// 빨강 버튼에 함수 바인딩
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_WeaponColorWidget::OnRedButtonClicked);
	// 초록 버튼 초기화
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_weapon.icon_weapon")), FVector3f(1.f, 1.f, 1.f));
	// 초록 버튼에 함수 바인딩
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_WeaponColorWidget::OnGreenButtonClicked);
	// 원래색 버튼 초기화
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_weapon.icon_weapon")), FVector3f(1.f, 1.f, 1.f));
	// 원래색 버튼에 함수 바인딩
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_WeaponColorWidget::OnOriginalButtonClicked);
}

void UWC_WeaponColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //버튼 소리
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(FLinearColor::Red, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.WeaponColorNum = 2;
	}
}

void UWC_WeaponColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //버튼 소리
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(FLinearColor::Green, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.WeaponColorNum = 1;
	}
}

void UWC_WeaponColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //버튼 소리
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(FLinearColor::White, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.WeaponColorNum = 0;
	}
}

void UWC_WeaponColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
