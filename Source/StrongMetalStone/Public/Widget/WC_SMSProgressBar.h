#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "../C_SMSEnum.h"
#include "WC_SMSProgressBar.generated.h"

UCLASS()
class STRONGMETALSTONE_API UWC_SMSProgressBar : public UProgressBar
{
	GENERATED_BODY()
	
public:
	// Progress Bar 초기화
	void Init(float percent, FLinearColor color);

	// Progress Bar 타입 설정
	void SetType(EProgressBarType type);

	// Percent 업데이트
	void Update(float percent);
	void Update(float percent, FLinearColor Color);

protected:

	EProgressBarType BarType;
};