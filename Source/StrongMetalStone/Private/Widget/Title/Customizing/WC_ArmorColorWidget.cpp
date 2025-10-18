// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_ArmorColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_ArmorColorWidget::NativeConstruct()
{
	// 메뚜기전사 버튼 초기화
	GrassHopherButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_armor.icon_armor")), FVector3f(1.f, 1.f, 1.f));
	// 메뚜기전사 버튼에 함수 바인딩
	GrassHopherButton->OnButtonClicked.AddDynamic(this, &UWC_ArmorColorWidget::OnGrassHopherButtonClicked);
	// 오리지널 버튼 초기화
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_armor.icon_armor")), FVector3f(1.f, 1.f, 1.f));
	// 오리지널 버튼에 함수 바인딩
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_ArmorColorWidget::OnOriginalButtonClicked);
	// 아이언맨 버튼 초기화
	IronManButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_armor.icon_armor")), FVector3f(1.f, 1.f, 1.f));
	// 아이언맨 버튼에 함수 바인딩
	IronManButton->OnButtonClicked.AddDynamic(this, &UWC_ArmorColorWidget::OnIronManButtonClicked);
	// 배트맨 버튼 초기화
	DarkKnightButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_armor.icon_armor")), FVector3f(1.f, 1.f, 1.f));
	// 배트맨 버튼에 함수 바인딩
	DarkKnightButton->OnButtonClicked.AddDynamic(this, &UWC_ArmorColorWidget::OnDarkKnightButtonClicked);
	// 도라에몽 버튼 초기화
	DoraemonButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_armor.icon_armor")), FVector3f(1.f, 1.f, 1.f));
	// 도라에몽 버튼에 함수 바인딩
	DoraemonButton->OnButtonClicked.AddDynamic(this, &UWC_ArmorColorWidget::OnDoraemonButtonClicked);
	// 디바 버튼 초기화
	DVaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_armor.icon_armor")), FVector3f(1.f, 1.f, 1.f));
	// 디바 버튼에 함수 바인딩
	DVaButton->OnButtonClicked.AddDynamic(this, &UWC_ArmorColorWidget::OnDVaButtonClicked);

}

void UWC_ArmorColorWidget::OnGrassHopherButtonClicked()
{
	OnButtonSound(); // 버튼 소리
	BasicChest(FLinearColor::Green, FLinearColor::Red, FLinearColor::Red);
	BasicBelly(FLinearColor::Green, FLinearColor::Black, FLinearColor::Gray, FLinearColor::Green);
	BasicSkirt(FLinearColor::Green, FLinearColor::Red, FLinearColor::Red, FLinearColor::Red, FLinearColor::Green);
	BasicKnee(FLinearColor::Black, FLinearColor::Red, FLinearColor::Green);
	CustomCharacter->CharacterInfo.CustomizingInfo.ArmorColorNum = 2;
}

void UWC_ArmorColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); // 버튼 소리
	BasicChest(FLinearColor::White, FLinearColor::White, FLinearColor::White);
	BasicBelly(FLinearColor::White, FLinearColor::White, FLinearColor::White, FLinearColor::White);
	BasicSkirt(FLinearColor::White, FLinearColor::White, FLinearColor::White, FLinearColor::White, FLinearColor::White);
	BasicKnee(FLinearColor::White, FLinearColor::White, FLinearColor::White);
	CustomCharacter->CharacterInfo.CustomizingInfo.ArmorColorNum = 0;
}

void UWC_ArmorColorWidget::OnIronManButtonClicked()
{
	OnButtonSound(); // 버튼 소리
	BasicChest(FLinearColor::Red, FLinearColor::Red, FLinearColor::Yellow);
	BasicBelly(FLinearColor::Red, FLinearColor::Yellow, FLinearColor::Yellow, FLinearColor(0.0f,1.0f,1.0f));
	BasicSkirt(FLinearColor::Red, FLinearColor::Red, FLinearColor::Yellow, FLinearColor::Yellow, FLinearColor::Yellow);
	BasicKnee(FLinearColor::Red, FLinearColor::Red, FLinearColor::Yellow);
	CustomCharacter->CharacterInfo.CustomizingInfo.ArmorColorNum = 1;
}

void UWC_ArmorColorWidget::OnDarkKnightButtonClicked()
{
	OnButtonSound(); // 버튼 소리
	BasicChest(FLinearColor::Black, FLinearColor::Black, FLinearColor::Black);
	BasicBelly(FLinearColor::Black, FLinearColor::Black, FLinearColor::Black, FLinearColor::Yellow);
	BasicSkirt(FLinearColor::Black, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black);
	BasicKnee(FLinearColor::Black, FLinearColor::Black, FLinearColor::Black);
	CustomCharacter->CharacterInfo.CustomizingInfo.ArmorColorNum = 3;
}

void UWC_ArmorColorWidget::OnDoraemonButtonClicked()
{
	OnButtonSound(); // 버튼 소리
	BasicChest(FLinearColor(0.0f,0.43f,1.0f), FLinearColor::Red, FLinearColor(0.0f, 0.43f, 1.0f));
	BasicBelly(FLinearColor::White, FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor::Yellow);
	BasicSkirt(FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f));
	BasicKnee(FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor::White, FLinearColor(0.0f, 0.43f, 1.0f));
	CustomCharacter->CharacterInfo.CustomizingInfo.ArmorColorNum = 4;
}

void UWC_ArmorColorWidget::OnDVaButtonClicked()
{
	OnButtonSound(); // 버튼 소리
	BasicChest(FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f));
	BasicBelly(FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(0.49f, 1.0f, 0.58f));
	BasicSkirt(FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f));
	BasicKnee(FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f));
	CustomCharacter->CharacterInfo.CustomizingInfo.ArmorColorNum = 5;
}

void UWC_ArmorColorWidget::BasicChest(FLinearColor Armor, FLinearColor Neck, FLinearColor Detail)
{
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	
	if (Warrior)
	{
		CustomCharacter->ButtonColor(Armor, 1);
		CustomCharacter->ButtonColor(Neck, 11);
		CustomCharacter->ButtonColor(Detail,12);
	}
}

void UWC_ArmorColorWidget::BasicBelly(FLinearColor Armor, FLinearColor Biceps, FLinearColor FormArm, FLinearColor Detail)
{
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(Armor, 2);
		CustomCharacter->ButtonColor(Biceps, 21);
		CustomCharacter->ButtonColor(FormArm, 22);
		CustomCharacter->ButtonColor(Detail, 23);
	}
}

void UWC_ArmorColorWidget::BasicSkirt(FLinearColor Armor, FLinearColor DetailUp, FLinearColor DetailDown, FLinearColor Point, FLinearColor Thigh)
{
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(Armor, 3);
		CustomCharacter->ButtonColor(DetailUp, 31);
		CustomCharacter->ButtonColor(DetailDown, 32);
		CustomCharacter->ButtonColor(Point, 33);
		CustomCharacter->ButtonColor(Thigh, 34);
	}
}

void UWC_ArmorColorWidget::BasicKnee(FLinearColor Armor, FLinearColor Leather, FLinearColor Detail)
{
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(Armor, 5);
		CustomCharacter->ButtonColor(Leather, 51);
		CustomCharacter->ButtonColor(Detail, 52);	
	}
}

void UWC_ArmorColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}

