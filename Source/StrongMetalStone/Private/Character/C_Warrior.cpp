#include "Character/C_Warrior.h"
#include "PlayerController/C_WorldPlayerController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Component/C_ParticleSystemComponent.h"
//#include "NiagaraSystem.h"

AC_Warrior::AC_Warrior()
{
	CharacterJob = EPlayerJob::WARRIOR;
	CharacterInfo.Job = EPlayerJob::WARRIOR;

	LowHeatEffects= CreateDefaultSubobject<UNiagaraComponent>(TEXT("LowHeatEffect"));
	MiddleHeatEffects = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MiddleHeatEffect"));
	HighHeatEffects = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HighHeatEffect"));
	LowHeatEffects->SetupAttachment(RootComponent);
	MiddleHeatEffects->SetupAttachment(RootComponent);
	HighHeatEffects->SetupAttachment(RootComponent);
}

void AC_Warrior::BeginPlay()
{
	Super::BeginPlay();		
}

void AC_Warrior::Update()
{
	Super::Update();

	ParticleSystemComponent->ServerUpdate();
}

void AC_Warrior::SetColor()
{
	UMaterialInterface* BaseMatFace = GetMesh()->GetMaterial(0); // ���� 0 ����(�󱼻�)
	DynMaterialFace = UMaterialInstanceDynamic::Create(BaseMatFace, this);
	GetMesh()->SetMaterial(0, DynMaterialFace);
	UMaterialInterface* BaseMatEye = GetMesh()->GetMaterial(8); // ���� 8 ����(������)
	DynMaterialEye = UMaterialInstanceDynamic::Create(BaseMatEye, this);
	GetMesh()->SetMaterial(8, DynMaterialEye);
	UMaterialInterface* BaseMatHair = GetMesh()->GetMaterial(7); // ���� 7 ����(�Ӹ�����)
	DynMaterialHair = UMaterialInstanceDynamic::Create(BaseMatHair, this);
	GetMesh()->SetMaterial(7, DynMaterialHair);
	UMaterialInterface* BaseMatWeapon = GetMesh()->GetMaterial(6); // ���� 6 ����(�������)
	DynMaterialWeapon = UMaterialInstanceDynamic::Create(BaseMatWeapon, this);
	GetMesh()->SetMaterial(6, DynMaterialWeapon);
	UMaterialInterface* BaseMatEyeLash = GetMesh()->GetMaterial(10); // ���� 10 ����(�Ӵ������)
	DynMaterialEyeLash = UMaterialInstanceDynamic::Create(BaseMatEyeLash, this);
	GetMesh()->SetMaterial(10, DynMaterialEyeLash);

	UMaterialInterface* BaseMatChest = GetMesh()->GetMaterial(1); // ���� 1 ����(���ʰ����κл���)
	DynMaterialChest = UMaterialInstanceDynamic::Create(BaseMatChest, this);
	GetMesh()->SetMaterial(1, DynMaterialChest);

	UMaterialInterface* BaseMatBelly = GetMesh()->GetMaterial(2); // ���� 2 ����(���ʹ�κл���)
	DynMaterialBelly = UMaterialInstanceDynamic::Create(BaseMatBelly, this);
	GetMesh()->SetMaterial(2, DynMaterialBelly);

	UMaterialInterface* BaseMatSkirt = GetMesh()->GetMaterial(3); // ���� 3 ����(�������ǻ���)
	DynMaterialSkirt1 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(3, DynMaterialSkirt1);
	DynMaterialSkirt2 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(4, DynMaterialSkirt2);
	DynMaterialSkirt3 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(12, DynMaterialSkirt3);
	DynMaterialSkirt4 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(13, DynMaterialSkirt4);
	DynMaterialSkirt5 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(14, DynMaterialSkirt5);
	DynMaterialSkirt6 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(15, DynMaterialSkirt6);

	UMaterialInterface* BaseMatKnee = GetMesh()->GetMaterial(5); // ���� 5 ����(���ʹ����κл���)
	DynMaterialKnee = UMaterialInstanceDynamic::Create(BaseMatKnee, this);
	GetMesh()->SetMaterial(5, DynMaterialKnee);

}

void AC_Warrior::NewColor(float Value)
{
	if (DynMaterialFace)
	{
		FLinearColor Color = FLinearColor::LerpUsingHSV(
			FLinearColor::White,          // ���� ����
			FLinearColor::Black,          // �� ����
			Value                   // 0.0 ~ 1.0
		);

		DynMaterialFace->SetVectorParameterValue("SkinColor", Color);
	}
}

void AC_Warrior::ButtonColor(FLinearColor Color, int32 Index)
{
	if (DynMaterialEye && Index == 8) // ������
	{
		DynMaterialEye->SetVectorParameterValue("EyeColor", Color);
	}
	if (DynMaterialHair && Index == 7) // �Ӹ�ī������
	{
		DynMaterialHair->SetVectorParameterValue("HairColor", Color);
	}
	if (DynMaterialWeapon && Index == 6) // �������
	{
		DynMaterialWeapon->SetVectorParameterValue("WeaponColor", Color);
	}
	if (DynMaterialEyeLash && Index == 10) // �Ӵ������
	{
		DynMaterialEyeLash->SetVectorParameterValue("Eyelash Color", Color);
	}
	if (DynMaterialChest && Index == 1)
	{
		DynMaterialChest->SetVectorParameterValue("ArmorColor", Color); 
	}// ���ʰ��� ��ü���λ���
	if (DynMaterialChest && Index == 11)
	{
		DynMaterialChest->SetVectorParameterValue("NeckColor", Color); 
	}// ���ʰ��� ��κл���
	if (DynMaterialChest && Index == 12)
	{
		DynMaterialChest->SetVectorParameterValue("DetailColor", Color);
	} // ���ʰ��� �����ϻ���
	if (DynMaterialBelly && Index == 2)
	{
		DynMaterialBelly->SetVectorParameterValue("ArmorColor", Color);
	} // ���ʹ� ��ü���λ���
	if (DynMaterialBelly && Index == 21)
	{
		DynMaterialBelly->SetVectorParameterValue("BicepsColor", Color);
	}// ���ʹ� �̵ιڱٻ���
	if (DynMaterialBelly && Index == 22)
	{
		DynMaterialBelly->SetVectorParameterValue("FormArmColor", Color);
	}// ���ʹ� ���ϱٻ���
	if (DynMaterialBelly && Index == 23)
	{
		DynMaterialBelly->SetVectorParameterValue("DetailColor", Color);
	}// ���ʹ� �����ϻ���
	if (DynMaterialSkirt1 && DynMaterialSkirt2 && DynMaterialSkirt3 && DynMaterialSkirt4 && DynMaterialSkirt5 && DynMaterialSkirt6 && Index == 3)
	{
		DynMaterialSkirt1->SetVectorParameterValue("ArmorColor", Color);
		DynMaterialSkirt2->SetVectorParameterValue("ArmorColor", Color);
		DynMaterialSkirt3->SetVectorParameterValue("ArmorColor", Color);
		DynMaterialSkirt4->SetVectorParameterValue("ArmorColor", Color);
		DynMaterialSkirt5->SetVectorParameterValue("ArmorColor", Color);
		DynMaterialSkirt6->SetVectorParameterValue("ArmorColor", Color);
	}// �������� ��ü���� ����
	if (DynMaterialSkirt1 && DynMaterialSkirt2 && DynMaterialSkirt3 && DynMaterialSkirt4 && DynMaterialSkirt5 && DynMaterialSkirt6 && Index == 31)
	{
		DynMaterialSkirt1->SetVectorParameterValue("DetailUpColor", Color);
		DynMaterialSkirt2->SetVectorParameterValue("DetailUpColor", Color);
		DynMaterialSkirt3->SetVectorParameterValue("DetailUpColor", Color);
		DynMaterialSkirt4->SetVectorParameterValue("DetailUpColor", Color);
		DynMaterialSkirt5->SetVectorParameterValue("DetailUpColor", Color);
		DynMaterialSkirt6->SetVectorParameterValue("DetailUpColor", Color);
	}// �������� ������ �� ����
	if (DynMaterialSkirt1 && DynMaterialSkirt2 && DynMaterialSkirt3 && DynMaterialSkirt4 && DynMaterialSkirt5 && DynMaterialSkirt6 && Index == 32)
	{
		DynMaterialSkirt1->SetVectorParameterValue("DetailDownColor", Color);
		DynMaterialSkirt2->SetVectorParameterValue("DetailDownColor", Color);
		DynMaterialSkirt3->SetVectorParameterValue("DetailDownColor", Color);
		DynMaterialSkirt4->SetVectorParameterValue("DetailDownColor", Color);
		DynMaterialSkirt5->SetVectorParameterValue("DetailDownColor", Color);
		DynMaterialSkirt6->SetVectorParameterValue("DetailDownColor", Color);
	}// �������� ������ �Ʒ� ����
	if (DynMaterialSkirt1 && DynMaterialSkirt2 && DynMaterialSkirt3 && DynMaterialSkirt4 && DynMaterialSkirt5 && DynMaterialSkirt6 && Index == 33)
	{
		DynMaterialSkirt1->SetVectorParameterValue("PointColor", Color);
		DynMaterialSkirt2->SetVectorParameterValue("PointColor", Color);
		DynMaterialSkirt3->SetVectorParameterValue("PointColor", Color);
		DynMaterialSkirt4->SetVectorParameterValue("PointColor", Color);
		DynMaterialSkirt5->SetVectorParameterValue("PointColor", Color);
		DynMaterialSkirt6->SetVectorParameterValue("PointColor", Color);
	}// �������� �߿���� ����
	if (DynMaterialSkirt1 && DynMaterialSkirt2 && DynMaterialSkirt3 && DynMaterialSkirt4 && DynMaterialSkirt5 && DynMaterialSkirt6 && Index == 34)
	{
		DynMaterialSkirt1->SetVectorParameterValue("ThighColor", Color);
		DynMaterialSkirt2->SetVectorParameterValue("ThighColor", Color);
		DynMaterialSkirt3->SetVectorParameterValue("ThighColor", Color);
		DynMaterialSkirt4->SetVectorParameterValue("ThighColor", Color);
		DynMaterialSkirt5->SetVectorParameterValue("ThighColor", Color);
		DynMaterialSkirt6->SetVectorParameterValue("ThighColor", Color);
	}// �������� ����� ����
	if (DynMaterialKnee && Index == 5)
	{
		DynMaterialKnee->SetVectorParameterValue("ArmorColor", Color);
	}// ���� ���� �� ���� ��ü���� ����
	if (DynMaterialKnee && Index == 51)
	{
		DynMaterialKnee->SetVectorParameterValue("LeatherColor", Color);
	}// ���� ���� �� ���� ���� ����
	if (DynMaterialKnee && Index == 52)
	{
		DynMaterialKnee->SetVectorParameterValue("DetailColor", Color);
	}// ���� ���� �� ���� ������ ����
}

float AC_Warrior::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float AdjustedDamageAmount = DamageAmount;
	
	if (bOnShield)
	{
		float PlusOverHeat = 2; // �⺻ ����
		AdjustedDamageAmount *= (CharacterInfo.Curmp / 170.0f); // ������ ��ġ ����
		if (CharacterInfo.Curmp <= 10)
		{
			AdjustedDamageAmount = 0;
		}

		if (bOnParrying) // �и���
		{
			AdjustedDamageAmount = 0; // �и��� ������X
			PlusOverHeat *= 15; // �и��� ������ ����
			/*bOnParrying = false;*/
			ServerParrying();
		}

		if (DamageAmount >= 0 && DamageAmount < 500)
		{
			CharacterInfo.Curmp += PlusOverHeat;
		}
		else if (DamageAmount >= 500 && DamageAmount < 1000)
		{
			CharacterInfo.Curmp += PlusOverHeat*2;
		}
		else
		{
			CharacterInfo.Curmp += PlusOverHeat*3;
		}

		if (CharacterInfo.Curmp > CharacterInfo.Maxmp) // ���� ������ �ִ� ������ �Ѿ�� ���
		{
			CharacterInfo.Curmp = CharacterInfo.Maxmp; // ���� ���� = �ִ� ����
		}
		DelayOverHeat();
		Update();
		ClientUpdate();
	}

	return Super::TakeDamage(AdjustedDamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AC_Warrior::OverHeatInit()
{
	CharacterInfo.Curmp = 0.0f;
	Update();
	ClientUpdate();
	GetWorld()->GetTimerManager().ClearTimer(BattleInitTH);
}

void AC_Warrior::DelayOverHeat()
{
	GetWorld()->GetTimerManager().ClearTimer(BattleInitTH);
	GetWorld()->GetTimerManager().SetTimer(BattleInitTH, this,&AC_Warrior::OverHeatInit, 10.0f, false);
	ClientDelayOverHeat();
}

void AC_Warrior::ClientDelayOverHeat_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(BattleInitTH);
	GetWorld()->GetTimerManager().SetTimer(BattleInitTH, this, &AC_Warrior::OverHeatInit, 10.0f, false);
}

void AC_Warrior::ServerDelayOverHeat_Implementation()
{
	DelayOverHeat();
}

void AC_Warrior::Death(AC_SMSCharacter* Killer)
{
	Super::Death(Killer);

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
}


void AC_Warrior::ServerDelayUnBeatable_Implementation()
{
	Absolute = true;
	GetWorld()->GetTimerManager().ClearTimer(UnBeatableTH);
	GetWorld()->GetTimerManager().SetTimer(UnBeatableTH, this, &AC_Warrior::UnBeatableInit, 3.0f, false);
	MultiDelayUnBeatable();
}

void AC_Warrior::MultiDelayUnBeatable_Implementation()
{
	Absolute = true;
	GetWorld()->GetTimerManager().ClearTimer(UnBeatableTH);
	GetWorld()->GetTimerManager().SetTimer(UnBeatableTH, this, &AC_Warrior::UnBeatableInit, 3.0f, false);
}

void AC_Warrior::UnBeatableInit()
{
	Absolute = false;
	GetWorld()->GetTimerManager().ClearTimer(UnBeatableTH);
}

void AC_Warrior::ServerParrying_Implementation ()
{
	bOnParrying = false;
	MultiParrying();
}

void AC_Warrior::MultiParrying_Implementation()
{
	bOnParrying = false;
}
