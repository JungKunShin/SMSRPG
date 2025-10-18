// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/WC_CustomizingWidget.h"
#include "Widget/Title/WC_TitleWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_PlayerCharacter.h"
#include "C_SMSGameInstance.h"
#include "PlayerController/C_SMSPlayerController.h"
#include "HUD/C_TitleHUD.h"
#include "Widget/Title/Customizing/WC_FaceColorWidget.h"
#include "Widget/Title/Customizing/WC_EyeColorWidget.h"
#include "Widget/Title/Customizing/WC_HairColorWidget.h"
#include "Widget/Title/Customizing/WC_WeaponColorWidget.h"
#include "Widget/Title/Customizing/WC_EyeLashColorWidget.h"
#include "Widget/Title/Customizing/WC_WeightSizeWidget.h"
#include "Widget/Title/Customizing/WC_ArmorColorWidget.h"
#include "Widget/Title/Customizing/WC_MgClothColorWidget.h"
#include "Widget/Title/Customizing/WC_MgBagColorWidget.h"
#include "PlayerController/C_TitlePlayerController.h"
#include "Character/C_Mage.h"
#include "Character/C_Warrior.h"

void UWC_CustomizingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//결정
	if (Button_Select)
	{
		// 버튼 초기화
		Button_Select->Init(FText::FromString(TEXT("결정")), 20);

		// 함수 이벤트 바인딩
		Button_Select->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnButtonClickEnter);
	}

	//뒤로
	if (Button_Back)
	{
		// 버튼 초기화
		Button_Back->Init(FText::FromString(TEXT("뒤로")), 20);

		// 함수 이벤트 바인딩
		Button_Back->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnButtonClickBack);
	}
	EditableText_CharacterName->OnTextCommitted.AddDynamic(this, &UWC_CustomizingWidget::OnTextCommittedCharacterName);	
	EditableText_CharacterName->OnTextChanged.AddDynamic(this, &UWC_CustomizingWidget::OnTextChangedCharacterName);
	Button_FaceColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_face.icon_face")), FVector3f(1.f, 1.f, 1.f));
	Button_FaceColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnFaceColorButtonClicked);
	Button_EyeColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	Button_EyeColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnEyeColorButtonClicked);
	Button_HairColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	Button_HairColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnHairColorButtonClicked);
	Button_WeaponColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_weapon.icon_weapon")), FVector3f(1.f, 1.f, 1.f));
	Button_WeaponColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnWeaponColorButtonClicked);
	Button_EyeLashColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	Button_EyeLashColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnEyeLashColorButtonClicked);
	/*Button_WeightSize->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/btn_icon_fat.btn_icon_fat")), FVector3f(1.f, 1.f, 1.f));
	Button_WeightSize->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnWeightSizeButtonClicked);*/
	Button_ArmorColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_armor.icon_armor")), FVector3f(1.f, 1.f, 1.f));
	Button_ArmorColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnArmorColorButtonClicked);
	Button_MgClothColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	Button_MgClothColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnMgClothColorButtonClicked);
	Button_MgBagColor->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	Button_MgBagColor->OnButtonClicked.AddDynamic(this, &UWC_CustomizingWidget::OnMgBagColorButtonClicked);
	InitButton();
}

//결정 버튼
void UWC_CustomizingWidget::OnButtonClickEnter()
{
	OnButtonSound(); //버튼 소리

	Cast<AC_SMSPlayerController>(GetMyPC())->ServerLoadPlayerInfoFromCSV();
	//닉네임 입력하라는 경고메세지
	if (InputName.Len() < MIN_NAME_NUM)
	{		
		Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_NICKNAME_NUM);
		return;
	}

	CastWGI(GetMyGI())->CharacterInfoDatas = GetLoadCharacterInfoFromCSV();
	//중복닉네임감지
	for (FCharacterInfo MyCharacterInfo:CastWGI(GetMyGI())->CharacterInfoDatas)
	{
		if (MyCharacterInfo.CharacterName == InputName)
		{
			Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_NICKNAME_INPUT);
			return;
		}
	}
	//FaceColorWidget->FaceColorSlider->SetValue(0); // 얼굴색 변경 슬라이더 초기화

	Cast<AC_TitleHUD>(GetMyHUD())->TitleWidget->WBPC_CreateCharacterWidget->SpawnCharacter->CharacterInfo.CharacterName = InputName;
	Cast<AC_SMSPlayerController>(GetMyPC())->ServerAddCharacterInfoToCSV(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar->CharacterInfo);

	Cast<AC_TitleHUD>(GetMyHUD())->SetTitleWidgetSwitcherIndex(1);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Pawn);
	InitButton();
}

//뒤로 버튼
void UWC_CustomizingWidget::OnButtonClickBack()
{
	OnButtonSound(); //버튼 소리

//	FaceColorWidget->FaceColorSlider->SetValue(0); // 얼굴색 변경 슬라이더 초기화
	Cast<AC_TitleHUD>(GetMyHUD())->SetTitleWidgetSwitcherIndex(2);
	InitButton();
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Pawn);
}

void UWC_CustomizingWidget::OnTextChangedCharacterName(const FText& NewText)
{
	InputName = NewText.ToString();

	if (InputName.Len() <= 0)return;

	if (InputName.Len() >= MAX_NAME_NUM)
	{
		EditableText_CharacterName->SetText(FText::FromString(InputName.Left(MAX_NAME_NUM)));
		return;
	}
}

void UWC_CustomizingWidget::OnTextCommittedCharacterName(const FText& Text, ETextCommit::Type CommitType)
{
	InputName = Text.ToString();

	if (CommitType == ETextCommit::OnEnter)
	{
		OnButtonClickEnter();
	}
}

void UWC_CustomizingWidget::OnFaceColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	FaceColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Character);
}

void UWC_CustomizingWidget::OnEyeColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	EyeColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Character);
}

void UWC_CustomizingWidget::OnHairColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	HairColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Character);
}

void UWC_CustomizingWidget::OnWeaponColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	WeaponColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Pawn);
}

void UWC_CustomizingWidget::OnEyeLashColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	EyeLashColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Character);
}

//void UWC_CustomizingWidget::OnWeightSizeButtonClicked()
//{
//	InitButton();
//	WeightSizeWidget->SetVisibility(ESlateVisibility::Visible);
//	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
//	PC->ChangeCamera(false);
//}

void UWC_CustomizingWidget::OnArmorColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	ArmorColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Pawn);
}

void UWC_CustomizingWidget::OnMgClothColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	MgClothColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Pawn);
}

void UWC_CustomizingWidget::OnMgBagColorButtonClicked()
{
	OnButtonSound(); //버튼 소리

	InitButton();
	MgBagColorWidget->SetVisibility(ESlateVisibility::Visible);
	AC_TitlePlayerController* PC = Cast<AC_TitlePlayerController>(GetMyPC());
	PC->ChangeCamera(ECameraViewPoint::Bag);
}

void UWC_CustomizingWidget::InitButton()
{
	FaceColorWidget->SetVisibility(ESlateVisibility::Hidden);
	EyeColorWidget->SetVisibility(ESlateVisibility::Hidden);
	HairColorWidget->SetVisibility(ESlateVisibility::Hidden);
	WeaponColorWidget->SetVisibility(ESlateVisibility::Hidden);
	EyeLashColorWidget->SetVisibility(ESlateVisibility::Hidden);
	//WeightSizeWidget->SetVisibility(ESlateVisibility::Hidden);
	ArmorColorWidget->SetVisibility(ESlateVisibility::Hidden);
	MgClothColorWidget->SetVisibility(ESlateVisibility::Hidden);
	MgBagColorWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UWC_CustomizingWidget::HiddenButtonByJob()
{
	if (!Cast<AC_TitleHUD>(GetMyHUD())->CustomChar)return;
	AC_PlayerCharacter* Character =Cast<AC_PlayerCharacter>( Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);
	if (Cast<AC_Warrior>(Character))
	{
		Button_MgClothColor->SetVisibility(ESlateVisibility::Hidden);
		Button_MgBagColor->SetVisibility(ESlateVisibility::Hidden);
		Button_ArmorColor->SetVisibility(ESlateVisibility::Visible);
		Button_WeaponColor->SetVisibility(ESlateVisibility::Visible);
	}
	else if (Cast<AC_Mage>(Character))
	{
		Button_ArmorColor->SetVisibility(ESlateVisibility::Hidden);
		Button_WeaponColor->SetVisibility(ESlateVisibility::Hidden);
		Button_MgClothColor->SetVisibility(ESlateVisibility::Visible);
		Button_MgBagColor->SetVisibility(ESlateVisibility::Visible);
	}
}

void UWC_CustomizingWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
