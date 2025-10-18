
#include "Widget/Title/WC_TitleWidget.h"
#include "C_SMSGameInstance.h"
#include "PlayerController/C_TitlePlayerController.h"
#include "Character/C_PlayerCharacter.h"

void UWC_TitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

    Cast<AC_SMSPlayerController>(GetMyPC())->ServerLoadUserInfoFromCSV();
}



//위젯스위처 변경
void UWC_TitleWidget::SetWidgetSwitcherIndex(int _index)
{	
	if (_index == CurWidgetNum) return;

    //캐릭터 객체가 남아있으면 전부 삭제
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_PlayerCharacter::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        if (Actor)
        {
            if (_index == 3)
            {

            }
            else
            {
                Actor->Destroy();
            }
        }
    }
    if (_index == 1)
    {
        TextBlock_Title1->SetVisibility(ESlateVisibility::Hidden);
        TextBlock_Title2->SetVisibility(ESlateVisibility::Hidden);
        Cast<AC_TitlePlayerController>(GetMyPC())->ServerSpawnMyCharacter(CastWGI(GetMyGI())->UserInfo.ID);
    }
    

	PreWidgetNum = CurWidgetNum;
	CurWidgetNum = _index;
	TitleWidgetSwitcher->SetActiveWidgetIndex(CurWidgetNum);
    TextInit();
}

void UWC_TitleWidget::SetWarningMessage(const FText& _Text)
{
    AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
    if (!TitleController)return;

    if (WarningSound)// 인벤토리 소리
    {
        UGameplayStatics::PlaySoundAtLocation(this, WarningSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
    }

	WBPC_TitleWarningWidget->SetWarningMessage(_Text);
}

void UWC_TitleWidget::TextInit()
{       
    WBPC_LoginWidget->EditableText_ID->SetText(FText::FromString(""));
    WBPC_LoginWidget->EditableText_PassWord->SetText(FText::FromString(""));
    WBPC_LoginWidget->EditableText_CreateID->SetText(FText::FromString(""));
    WBPC_LoginWidget->EditableText_CreatePassWord->SetText(FText::FromString(""));
    WBPC_CustomizingWidget->EditableText_CharacterName->SetText(FText::FromString(""));
}