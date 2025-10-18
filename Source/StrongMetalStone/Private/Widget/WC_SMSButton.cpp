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

	// ��ư�� �Լ� ���ε�
	if (BaseButton)
	{
		BaseButton->OnClicked.AddDynamic(this, &UWC_SMSButton::HandleInternalClicked);
	}
}

// �̹����� ���� ��
void UWC_SMSButton::Init(UTexture2D* icon, FVector3f color)
{
	// �ؽ�Ʈ ����
	ButtonText->RemoveFromParent();

	// ��� ���� ����
	FLinearColor Background;

	// ���� ���� ����
	FSlateBrushOutlineSettings Outline;
	Outline.Color = FSlateColor(FLinearColor::Transparent);

	FButtonStyle NewStyle = FButtonStyle();

	// ��ư �׵θ� �������� ����
	NewStyle.Normal.OutlineSettings = Outline;
	NewStyle.Hovered.OutlineSettings = Outline;
	NewStyle.Pressed.OutlineSettings = Outline;

	// ���� ���� ����
	Background = FLinearColor::Transparent;

	// ��ư ��� �������� ����
	NewStyle.Normal.TintColor = FSlateColor(Background);
	NewStyle.Hovered.TintColor = FSlateColor(Background);
	NewStyle.Pressed.TintColor = FSlateColor(Background);

	// �̹��� ����
	ButtonImage->SetBrushSize(FVector2D(50.f, 50.f));
	ButtonImage->SetBrushFromTexture(icon);
	ButtonImage->SetVisibility(ESlateVisibility::Visible);
	ButtonImage->InvalidateLayoutAndVolatility();
	
	// ���� ����
	ButtonImage->SetBrushTintColor(FLinearColor(color));

	// ����
	BaseButton->SetStyle(NewStyle);
	SynchronizeProperties();
}

// �ؽ�Ʈ�� ���� ��
void UWC_SMSButton::Init(const FText& text, const int32 size)
{
	// �̹��� ����
	ButtonImage->RemoveFromParent();

	// �ؽ�Ʈ ���� 
	ButtonText->SetText(text);

	FSlateFontInfo NewFont = ButtonText->GetFont();
	NewFont.Size = size;
	ButtonText->SetFont(NewFont);
	ButtonText->SetJustification(ETextJustify::Center);

	// ��� ���� ����
	FLinearColor Background;

	// ���� ���� ����
	FSlateBrushOutlineSettings Outline;
	Outline.Color = FSlateColor(FLinearColor::Transparent);

	FButtonStyle NewStyle = FButtonStyle();

	// ��ư �׵θ� �������� ����
	NewStyle.Normal.OutlineSettings = Outline;
	NewStyle.Hovered.OutlineSettings = Outline;
	NewStyle.Pressed.OutlineSettings = Outline;

	// ��ư ��� ���� ����
	Background = FLinearColor(0.f, 0.001527f, 0.010417f, 0.3f);

	// �⺻/��ħ/���� �� ��� ���� ����
	NewStyle.Normal.TintColor = FSlateColor(Background);
	NewStyle.Hovered.TintColor = FSlateColor(Background * 1.2f);
	NewStyle.Pressed.TintColor = FSlateColor(Background * 0.9f);

	// �ؽ�Ʈ ���� ����
	ButtonText->SetColorAndOpacity(FLinearColor(0.6041678f, 0.6041678f, 0.487739f, 1.f));

	// ����
	BaseButton->SetStyle(NewStyle);
	SynchronizeProperties();
}

// �̹����� �ؽ�Ʈ ���� ��
void UWC_SMSButton::Init(const FText& text, const int32 size, UTexture2D* icon)
{
	// �ؽ�Ʈ ���� 
	ButtonText->SetText(text);
	ButtonText->SetJustification(ETextJustify::Center);

	FSlateFontInfo NewFont = ButtonText->GetFont();
	NewFont.Size = size;
	ButtonText->SetFont(NewFont);

	// ��� ���� ����
	FLinearColor Background;

	// ���� ���� ����
	FSlateBrushOutlineSettings Outline;
	Outline.Color = FSlateColor(FLinearColor::Transparent);

	FButtonStyle NewStyle = FButtonStyle();

	// ��ư �׵θ� �������� ����
	NewStyle.Normal.OutlineSettings = Outline;
	NewStyle.Hovered.OutlineSettings = Outline;
	NewStyle.Pressed.OutlineSettings = Outline;

	// �̹����� �ؽ�Ʈ�� ���� �� ��ư ����
	// ���� ���� ����
	Background = FLinearColor::Transparent;

	// ��ư ��� �������� ����
	NewStyle.Normal.TintColor = FSlateColor(Background);
	NewStyle.Hovered.TintColor = FSlateColor(Background);
	NewStyle.Pressed.TintColor = FSlateColor(Background);

	// �̹��� ����
	ButtonImage->SetBrushSize(FVector2D(50.f, 50.f));
	ButtonImage->SetBrushFromTexture(icon);
	ButtonImage->SetBrushTintColor(FLinearColor::Black);
	ButtonImage->SetVisibility(ESlateVisibility::Visible);
	ButtonImage->InvalidateLayoutAndVolatility();

	// �ؽ�Ʈ ���� ����
	ButtonText->SetColorAndOpacity(FLinearColor::Black);

	FSlateChildSize ChildSize;
	ChildSize.SizeRule = ESlateSizeRule::Fill;

	// �̹����� �ؽ�Ʈ ��ġ ����
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

	// ����
	BaseButton->SetStyle(NewStyle);
	SynchronizeProperties();
}

void UWC_SMSButton::HandleInternalClicked()
{
	// ��ư�� ������ ����� ��� �Լ� �ڵ� ȣ��
	OnButtonClicked.Broadcast();
}