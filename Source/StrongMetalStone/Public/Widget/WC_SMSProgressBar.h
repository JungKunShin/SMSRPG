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
	// Progress Bar �ʱ�ȭ
	void Init(float percent, FLinearColor color);

	// Progress Bar Ÿ�� ����
	void SetType(EProgressBarType type);

	// Percent ������Ʈ
	void Update(float percent);
	void Update(float percent, FLinearColor Color);

protected:

	EProgressBarType BarType;
};