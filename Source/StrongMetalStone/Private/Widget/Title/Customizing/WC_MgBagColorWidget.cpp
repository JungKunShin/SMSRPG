// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_MgBagColorWidget.h"
#include "Character/C_Mage.h"
#include "Widget/WC_SMSButton.h"
#include "HUD/C_TitleHUD.h"
#include "Manager/C_CustomizingManager.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_MgBagColorWidget::NativeConstruct()
{
	// 오리지널 버튼 초기화
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// 오리지널 버튼에 함수 바인딩
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnOriginalButtonClicked);
	// 파랑 버튼 초기화
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// 파랑 버튼에 함수 바인딩
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnBlueButtonClicked);
	// 초록 버튼 초기화
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// 초록 버튼에 함수 바인딩
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnGreenButtonClicked);
	// 빨강 버튼 초기화
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// 빨강 버튼에 함수 바인딩
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnRedButtonClicked);
	// 노랑 버튼 초기화
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// 노랑 버튼에 함수 바인딩
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnYellowButtonClicked);
	// 청록 버튼 초기화
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// 청록 버튼에 함수 바인딩
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnCyanButtonClicked);
}

void UWC_MgBagColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //버튼 소리

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 0);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 0;
	}
}

void UWC_MgBagColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //버튼 소리

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 1);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 1;
	}
}

void UWC_MgBagColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //버튼 소리

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 2);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 2;
	}
}

void UWC_MgBagColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //버튼 소리

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 3);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 3;
	}
}

void UWC_MgBagColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //버튼 소리

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 4);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 4;
	}
}

void UWC_MgBagColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //버튼 소리

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 5);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 5;
	}
}

void UWC_MgBagColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
