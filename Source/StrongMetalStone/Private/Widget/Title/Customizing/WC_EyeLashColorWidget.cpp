// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_EyeLashColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_EyeLashColorWidget::NativeConstruct()
{
	// 빨강 버튼 초기화
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 빨강 버튼에 함수 바인딩
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnRedButtonClicked);
	// 초록 버튼 초기화
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 초록 버튼에 함수 바인딩
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnGreenButtonClicked);
	// 원래색 버튼 초기화
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 원래색 버튼에 함수 바인딩
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnOriginalButtonClicked);
	// 흰색 버튼 초기화
	WhiteButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 흰색 버튼에 함수 바인딩
	WhiteButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnWhiteButtonClicked);
	// 파란색 버튼 초기화
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 파란색 버튼에 함수 바인딩
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnBlueButtonClicked);
	// 노란색 버튼 초기화
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 노란색 버튼에 함수 바인딩
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnYellowButtonClicked);
	// 청록색 버튼 초기화
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 청록색 버튼에 함수 바인딩
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnCyanButtonClicked);
	// 마젠타색 버튼 초기화
	MagentaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// 마젠타색 버튼에 함수 바인딩
	MagentaButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnMagentaButtonClicked);

}

void UWC_EyeLashColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 2;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 2;
	}
}

void UWC_EyeLashColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 1;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 1;
	}
}

void UWC_EyeLashColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 0;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 0;
	}
}

void UWC_EyeLashColorWidget::OnWhiteButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 3;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 3;
	}
}

void UWC_EyeLashColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 4;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 4;
	}
}

void UWC_EyeLashColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 5;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 5;
	}
}

void UWC_EyeLashColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 6;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 6;
	}
}

void UWC_EyeLashColorWidget::OnMagentaButtonClicked()
{
	OnButtonSound(); //버튼 소리

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 7;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 7;
	}
}

void UWC_EyeLashColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
