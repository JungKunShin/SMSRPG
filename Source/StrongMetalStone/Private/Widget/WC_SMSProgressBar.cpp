#include "Widget/WC_SMSProgressBar.h"
#include "Components/ProgressBar.h"

void UWC_SMSProgressBar::Init(float percent, FLinearColor color)
{
	// 색상 설정
	SetFillColorAndOpacity(color);
	// 퍼센트 설정
	SetPercent(percent);
}

void UWC_SMSProgressBar::SetType(EProgressBarType type)
{
	BarType = type;
}

void UWC_SMSProgressBar::Update(float percent)
{	
	// 퍼센트 설정
	SetPercent(percent);
}

void UWC_SMSProgressBar::Update(float percent, FLinearColor Color)
{
	// 퍼센트 설정
	SetPercent(percent);
	SetFillColorAndOpacity(Color);
}