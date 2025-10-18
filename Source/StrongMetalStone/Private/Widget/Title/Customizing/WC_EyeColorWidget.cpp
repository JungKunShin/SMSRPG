// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_EyeColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_EyeColorWidget::NativeConstruct()
{
	// 빨강 버튼 초기화
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 빨강 버튼에 함수 바인딩
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnRedButtonClicked);
	// 초록 버튼 초기화
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 초록 버튼에 함수 바인딩
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnGreenButtonClicked);
	// 파랑 버튼 초기화
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 파랑 버튼에 함수 바인딩
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnBlueButtonClicked);
	// 검정 버튼 초기화
	BlackButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 검정 버튼에 함수 바인딩
	BlackButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnBlackButtonClicked);
	// 회색 버튼 초기화
	GrayButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 회색 버튼에 함수 바인딩
	GrayButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnGrayButtonClicked);
	// 노랑 버튼 초기화
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 노랑 버튼에 함수 바인딩
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnYellowButtonClicked);
	// 청록 버튼 초기화
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 청록 버튼에 함수 바인딩
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnCyanButtonClicked);
	// 마젠타 버튼 초기화
	MagentaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// 마젠타 버튼에 함수 바인딩
	MagentaButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnMagentaButtonClicked);
}

void UWC_EyeColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 4;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 4;
	}
}

void UWC_EyeColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 1;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 1;
	}
}

void UWC_EyeColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 2;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 2;
	}
}

void UWC_EyeColorWidget::OnBlackButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 3;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 3;
	}
}

void UWC_EyeColorWidget::OnGrayButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 0;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 0;
	}
}

void UWC_EyeColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 5;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 5;
	}
}

void UWC_EyeColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 6;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 6;
	}
}

void UWC_EyeColorWidget::OnMagentaButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 7;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 7;
	}
}

void UWC_EyeColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
