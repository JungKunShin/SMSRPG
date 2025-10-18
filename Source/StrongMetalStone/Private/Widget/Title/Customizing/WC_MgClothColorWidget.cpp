// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_MgClothColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "Manager/C_CustomizingManager.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_MgClothColorWidget::NativeConstruct()
{
	// 오리지널 버튼 초기화
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// 오리지널 버튼에 함수 바인딩
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnOriginalButtonClicked);
	// 메뚜기 버튼 초기화
	GrassHopherButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// 메뚜기 버튼에 함수 바인딩
	GrassHopherButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnGrassHopherButtonClicked);
	// 태양신 라 버튼 초기화
	GodLaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// 태양신 라 버튼에 함수 바인딩
	GodLaButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnGodLaButtonClicked);
	// 아프로디테 버튼 초기화
	AphroditeButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// 아프로디테 버튼에 함수 바인딩
	AphroditeButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnAphroditeButtonClicked);
	// 뿡뿡이 버튼 초기화
	PoopGuyButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// 뿡뿡이 버튼에 함수 바인딩
	PoopGuyButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnPoopGuyButtonClicked);
	// 보노보노 버튼 초기화
	BonoBonoButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// 보노보노 버튼에 함수 바인딩
	BonoBonoButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnBonoBonoButtonClicked);
}

void UWC_MgClothColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //버튼 소리
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 0);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 0;
	}
}

void UWC_MgClothColorWidget::OnGrassHopherButtonClicked()
{
	OnButtonSound(); //버튼 소리
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 1);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 1;
	}
}

void UWC_MgClothColorWidget::OnGodLaButtonClicked()
{
	OnButtonSound(); //버튼 소리
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 2);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 2;
	}
}

void UWC_MgClothColorWidget::OnAphroditeButtonClicked()
{
	OnButtonSound(); //버튼 소리
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 3);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 3;
	}
}

void UWC_MgClothColorWidget::OnPoopGuyButtonClicked()
{
	OnButtonSound(); //버튼 소리
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 4);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 4;
	}
}

void UWC_MgClothColorWidget::OnBonoBonoButtonClicked()
{
	OnButtonSound(); //버튼 소리
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 5);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 5;
	}
}

void UWC_MgClothColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
