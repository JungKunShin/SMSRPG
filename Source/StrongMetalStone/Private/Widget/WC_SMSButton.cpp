#include "Widget/WC_SMSButton.h"

#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UWC_SMSButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UWC_SMSButton::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼에 함수 바인딩
	if (BaseButton)
	{
		BaseButton->OnClicked.AddDynamic(this, &UWC_SMSButton::HandleInternalClicked);
	}
}

// 이미지만 있을 때
void UWC_SMSButton::Init(UTexture2D* icon, FVector3f color)
{
	// 텍스트 삭제
	ButtonText->RemoveFromParent();

	// 배경 색상 설정
	FLinearColor Background;

	// 투명 색상 설정
	FSlateBrushOutlineSettings Outline;
	Outline.Color = FSlateColor(FLinearColor::Transparent);

	FButtonStyle NewStyle = FButtonStyle();

	// 버튼 테두리 투명으로 설정
	NewStyle.Normal.OutlineSettings = Outline;
	NewStyle.Hovered.OutlineSettings = Outline;
	NewStyle.Pressed.OutlineSettings = Outline;

	// 투명 색상 설정
	Background = FLinearColor::Transparent;

	// 버튼 배경 투명으로 설정
	NewStyle.Normal.TintColor = FSlateColor(Background);
	NewStyle.Hovered.TintColor = FSlateColor(Background);
	NewStyle.Pressed.TintColor = FSlateColor(Background);

	// 이미지 설정
	ButtonImage->SetBrushSize(FVector2D(50.f, 50.f));
	ButtonImage->SetBrushFromTexture(icon);
	ButtonImage->SetVisibility(ESlateVisibility::Visible);
	ButtonImage->InvalidateLayoutAndVolatility();
	
	// 색상 설정
	ButtonImage->SetBrushTintColor(FLinearColor(color));

	// 적용
	BaseButton->SetStyle(NewStyle);
	SynchronizeProperties();
}

// 텍스트만 있을 때
void UWC_SMSButton::Init(const FText& text, const int32 size)
{
	// 이미지 삭제
	ButtonImage->RemoveFromParent();

	// 텍스트 설정 
	ButtonText->SetText(text);

	FSlateFontInfo NewFont = ButtonText->GetFont();
	NewFont.Size = size;
	ButtonText->SetFont(NewFont);
	ButtonText->SetJustification(ETextJustify::Center);

	// 배경 색상 설정
	FLinearColor Background;

	// 투명 색상 설정
	FSlateBrushOutlineSettings Outline;
	Outline.Color = FSlateColor(FLinearColor::Transparent);

	FButtonStyle NewStyle = FButtonStyle();

	// 버튼 테두리 투명으로 설정
	NewStyle.Normal.OutlineSettings = Outline;
	NewStyle.Hovered.OutlineSettings = Outline;
	NewStyle.Pressed.OutlineSettings = Outline;

	// 버튼 배경 색상 설정
	Background = FLinearColor(0.f, 0.001527f, 0.010417f, 0.3f);

	// 기본/겹침/눌림 시 배경 색상 설정
	NewStyle.Normal.TintColor = FSlateColor(Background);
	NewStyle.Hovered.TintColor = FSlateColor(Background * 1.2f);
	NewStyle.Pressed.TintColor = FSlateColor(Background * 0.9f);

	// 텍스트 색상 설정
	ButtonText->SetColorAndOpacity(FLinearColor(0.6041678f, 0.6041678f, 0.487739f, 1.f));

	// 적용
	BaseButton->SetStyle(NewStyle);
	SynchronizeProperties();
}

// 이미지와 텍스트 있을 때
void UWC_SMSButton::Init(const FText& text, const int32 size, UTexture2D* icon)
{
	// 텍스트 설정 
	ButtonText->SetText(text);
	ButtonText->SetJustification(ETextJustify::Center);

	FSlateFontInfo NewFont = ButtonText->GetFont();
	NewFont.Size = size;
	ButtonText->SetFont(NewFont);

	// 배경 색상 설정
	FLinearColor Background;

	// 투명 색상 설정
	FSlateBrushOutlineSettings Outline;
	Outline.Color = FSlateColor(FLinearColor::Transparent);

	FButtonStyle NewStyle = FButtonStyle();

	// 버튼 테두리 투명으로 설정
	NewStyle.Normal.OutlineSettings = Outline;
	NewStyle.Hovered.OutlineSettings = Outline;
	NewStyle.Pressed.OutlineSettings = Outline;

	// 이미지와 텍스트가 있을 때 버튼 설정
	// 투명 색상 설정
	Background = FLinearColor::Transparent;

	// 버튼 배경 투명으로 설정
	NewStyle.Normal.TintColor = FSlateColor(Background);
	NewStyle.Hovered.TintColor = FSlateColor(Background);
	NewStyle.Pressed.TintColor = FSlateColor(Background);

	// 이미지 설정
	ButtonImage->SetBrushSize(FVector2D(50.f, 50.f));
	ButtonImage->SetBrushFromTexture(icon);
	ButtonImage->SetBrushTintColor(FLinearColor::Black);
	ButtonImage->SetVisibility(ESlateVisibility::Visible);
	ButtonImage->InvalidateLayoutAndVolatility();

	// 텍스트 색상 설정
	ButtonText->SetColorAndOpacity(FLinearColor::Black);

	FSlateChildSize ChildSize;
	ChildSize.SizeRule = ESlateSizeRule::Fill;

	// 이미지와 텍스트 배치 변경
	if (UVerticalBoxSlot* ImageSlot = Cast<UVerticalBoxSlot>(ButtonImage->Slot))
	{
		ChildSize.Value = 1.f;
		ImageSlot->SetSize(ChildSize);
		ImageSlot->SetVerticalAlignment(VAlign_Center);
	}

	if (UVerticalBoxSlot* TextSlot = Cast<UVerticalBoxSlot>(ButtonText->Slot))
	{
		ChildSize.Value = 0.f;
		TextSlot->SetSize(ChildSize);
	}

	// 적용
	BaseButton->SetStyle(NewStyle);
	SynchronizeProperties();
}

void UWC_SMSButton::HandleInternalClicked()
{
	// 버튼이 눌리면 연결된 모든 함수 자동 호출
	OnButtonClicked.Broadcast();
}