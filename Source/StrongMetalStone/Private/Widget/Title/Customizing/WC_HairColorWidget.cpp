// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_HairColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_HairColorWidget::NativeConstruct()
{
	// 빨강 버튼 초기화
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 빨강 버튼에 함수 바인딩
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnRedButtonClicked);
	// 초록 버튼 초기화
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 초록 버튼에 함수 바인딩
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnGreenButtonClicked);
	// 파랑 버튼 초기화
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 파랑 버튼에 함수 바인딩
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnBlueButtonClicked);
	// 검정 버튼 초기화
	BlackButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 검정 버튼에 함수 바인딩
	BlackButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnBlackButtonClicked);
	// 회색 버튼 초기화
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 회색 버튼에 함수 바인딩
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnOriginalButtonClicked);
	// 노랑 버튼 초기화
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 노랑 버튼에 함수 바인딩
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnYellowButtonClicked);
	// 청록 버튼 초기화
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 청록 버튼에 함수 바인딩
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnCyanButtonClicked);
	// 마젠타 버튼 초기화
	MagentaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// 마젠타 버튼에 함수 바인딩
	MagentaButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnMagentaButtonClicked);
}

void UWC_HairColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 4;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 4;
	}
}

void UWC_HairColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 1;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 1;
	}
}

void UWC_HairColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 2;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 2;
	}
}

void UWC_HairColorWidget::OnBlackButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 3;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 0;
	}
}

void UWC_HairColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 0;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 3;
	}
}

void UWC_HairColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 5;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 5;
	}
}

void UWC_HairColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 6;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 6;
	}
}

void UWC_HairColorWidget::OnMagentaButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 7;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 7;
	}
}

void UWC_HairColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
