// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_LoadingWidget.h"
#include "HUD/C_WorldHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerController/C_WorldPlayerController.h"

void UWC_LoadingWidget::NativeConstruct()
{
	PlayAnimation(Loading);
	RandomTip();
	DelayUpdate();

	AC_WorldPlayerController* WPC = CastWPC(GetMyPC());
	if (WPC)
	{
		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
		WPC->Subsystem->RemoveMappingContext(WPC->LookIMC);
		WPC->Subsystem->RemoveMappingContext(WPC->MoveIMC);
	}
}

void UWC_LoadingWidget::RandomTip()
{
	FText Tip = FText::FromString(TEXT("Tip : "));
	FText FirstTip = FText::FromString(TEXT("전사는 패링과 쉴드상태로 과열을 채울 수 있습니다. 과열을 채우면 평소의 1.2/1.5/2.5배 강해집니다."));
	FText SecondTip = FText::FromString(TEXT("마법사는 F키를 꾹 눌러 마나를 충전할 수 있어요."));
	FText ThirdTip = FText::FromString(TEXT("마법사의 황소방패는 적과 적의 공격뿐만이 아니라, 아군도 막을 수 있어요."));
	FText FourthTip = FText::FromString(TEXT("전사의 '레오니다스'와 '호플론돌진'은 적 플레이어를 일정시간 스턴상태에 빠지게 합니다."));
	FText FifthTip = FText::FromString(TEXT("전사의 '참격돌진'과 마법사의 기본공격은 타겟이 있어야만 발동가능합니다."));
	FText SixthTip = FText::FromString(TEXT("플레이어와 배틀을 하고자한다면, 상대 플레이어를 우클릭하고 싸우자를 클릭하면 됩니다."));
	FText SeventhTip = FText::FromString(TEXT("전사의 '집중참격'과 마법사의 '헬리오스의잔광'은 차징공격입니다."));
	FText EighthTip = FText::FromString(TEXT("마법사의 '헬리오스의맥동'은 주변의 적을 밀어냅니다. 가까운 적은 더 멀리 밀어냅니다."));
	FText NinthTip = FText::FromString(TEXT("Z키를 눌러 탑승물에 오를 수 있습니다."));
	FText TenthTip = FText::FromString(TEXT("I키를 눌러 인벤토리를 열고 닫을 수 있어요."));
	FText EleventhTip = FText::FromString(TEXT("G키를 눌러 상호작용을 할 수 있습니다."));
	FText TwelevethTip = FText::FromString(TEXT("고급좌변기는 사망 시, 일정시간 후 넓은 범위에 폭발을 가합니다."));
	FText ThirteenthTip = FText::FromString(TEXT("전사는 F키를 눌러 방패를 들 수 있어요. 타이밍에 맞게 방패를 들면 패링상태(3초 무적)가 됩니다."));
	FText FourteenthTip = FText::FromString(TEXT("꼬마 드론은 근거리 공격 이외에도 원거리 공격도 해요. 원거리 공격은 많이 아프답니다."));
	FText FifteenthTip = FText::FromString(TEXT("마중 소크라, 인중 테스라는 말이 있어요. 소크라를 죽이면 그 주인 테스가 소크라에서 내려 쫓아와요."));
	FText SixteenthTip = FText::FromString(TEXT("경험치를 얻어 레벨업을 하면, 기본 능력치들이 상승해요."));
	FText SeventeenthTip = FText::FromString(TEXT("아이템을 장착하면 아이템에 해당하는 능력치들이 상승해요."));
	FText EighteenthTip = FText::FromString(TEXT("설정에서 화면, 마우스감도, 소리 설정을 할 수 있어요. 심지어, 배경음악도 바꿀 수 있답니다...!"));
	FText NineteenthTip = FText::FromString(TEXT("물약을 먹으면 체력을 회복할 수 있어요. 퀵슬롯에 옮겨 사용할 수도 있습니다."));
	FText TwentythTip = FText::FromString(TEXT("스킬창을 열어 퀵슬롯의 스킬들을 내 입맛에 맞게 바꿔보세요. 스킬들을 끌어서 교체할 수 있습니다."));
	FText TwentyOneTip = FText::FromString(TEXT("던전에는 혼자 못들어가요... 다른 사람과 파티를 맺어, 협력하여 보스를 잡아보아요!"));
	FText TwentyTwoTip = FText::FromString(TEXT("대쉬나 텔레포트 중에는 무적상태입니다."));

	int32 RandomInt = FMath::RandRange(1, 21); // 1부터 21 사이의 랜덤 정수
	FText Result = FText::Format(FText::FromString("{0} {1}"), Tip, FirstTip);
	
	switch (RandomInt)
	{
	case 1:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, FirstTip);
		break;
	case 2:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, SecondTip);
		break;
	case 3:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, ThirdTip);
		break;
	case 4:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, FourthTip);
		break;
	case 5:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, FifthTip);
		break;
	case 6:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, SixthTip);
		break;
	case 7:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, SeventhTip);
		break;
	case 8:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, EighthTip);
		break;
	case 9:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, NinthTip);
		break;
	case 10:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, TenthTip);
		break;
	case 11:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, EleventhTip);
		break;
	case 12:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, TwelevethTip);
		break;
	case 13:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, ThirteenthTip);
		break;
	case 14:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, FourteenthTip);
		break;
	case 15:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, FifteenthTip);
		break;
	case 16:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, SixteenthTip);
		break;
	case 17:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, SeventeenthTip);
		break;
	case 18:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, EighteenthTip);
		break;
	case 19:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, NineteenthTip);
		break;
	case 20:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, TwentythTip);
		break;
	case 21:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, TwentyOneTip);
		break;
	case 22:
		Result = FText::Format(FText::FromString("{0} {1}"), Tip, TwentyTwoTip);
		break;
	default:
		break;
	}

	if (TEXT_Tip)
	{
		TEXT_Tip->SetText(Result);
	}
}

void UWC_LoadingWidget::UpdateProgressBar()
{
	LoadingProgressBar->SetPercent(CurTime / TOTAL_TIME);
	CurTime+=0.1f;
	DelayUpdate();
}

void UWC_LoadingWidget::DelayUpdate()
{
	if (CurTime>= TOTAL_TIME)
	{
		AC_WorldPlayerController* WPC = CastWPC(GetMyPC());
		if (WPC)
		{
			WPC->Subsystem->AddMappingContext(WPC->AttackIMC, 0);
			WPC->Subsystem->AddMappingContext(WPC->LookIMC, 0);
			WPC->Subsystem->AddMappingContext(WPC->MoveIMC, 0);
		}
		RemoveFromParent();
	}
	GetWorld()->GetTimerManager().ClearTimer(LoadingTH);
	GetWorld()->GetTimerManager().SetTimer(LoadingTH, this, &UWC_LoadingWidget::UpdateProgressBar, 0.1f, false);
}

void UWC_LoadingWidget::Init(bool OnDungeon)
{
	if (OnDungeon)
	{
		TEXT_Field-> SetVisibility(ESlateVisibility::Hidden);
		Image_Field->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TEXT_Dungeon->SetVisibility(ESlateVisibility::Hidden);
		Image_Dungeon->SetVisibility(ESlateVisibility::Hidden);
	}
}
