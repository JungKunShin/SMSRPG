#include "Widget/WC_SMSProgressBar.h"
#include "Components/ProgressBar.h"

void UWC_SMSProgressBar::Init(float percent, FLinearColor color)
{
	// ���� ����
	SetFillColorAndOpacity(color);
	// �ۼ�Ʈ ����
	SetPercent(percent);
}

void UWC_SMSProgressBar::SetType(EProgressBarType type)
{
	BarType = type;
}

void UWC_SMSProgressBar::Update(float percent)
{	
	// �ۼ�Ʈ ����
	SetPercent(percent);
}

void UWC_SMSProgressBar::Update(float percent, FLinearColor Color)
{
	// �ۼ�Ʈ ����
	SetPercent(percent);
	SetFillColorAndOpacity(Color);
}