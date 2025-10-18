// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Riding/C_SMSRiding.h"
#include "Character/C_PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/C_PartySystemComponent.h"
#include "Components/CapsuleComponent.h"

AC_SMSRiding::AC_SMSRiding()
{
	RidingBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("RidingBoom"));	// ī�޶� �� â��
	RidingBoom->SetupAttachment(GetCapsuleComponent());										// RootComponent ������ �ֱ�
	RidingBoom->TargetArmLength = 600.0f;											// ī�޶� �� ���� �ʱ� ����
	RidingBoom->bUsePawnControlRotation = true;

	RidingCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("RidingCamera"));						// ī�޶� â��
	RidingCamera->SetupAttachment(RidingBoom, USpringArmComponent::SocketName);																// ī�޶� �� ������ �ֱ�
	RidingCamera->bUsePawnControlRotation = false;

	PartySytemComponent = CreateDefaultSubobject<UC_PartySystemComponent>(TEXT("PartySystemComponent"));

	SetReplicates(true);
	bReplicates = true;
	SetReplicatingMovement(true);
	GetCharacterMovement()->SetIsReplicated(true);
}

void AC_SMSRiding::Mount_Implementation(AC_PlayerCharacter* Rider)
{
	if (!Rider || CurrentRider)return;
	CurrentRider = Rider;

	FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("RidingSocket"));
	Rider->SetActorLocationAndRotation(SocketTransform.GetLocation(), SocketTransform.GetRotation());
	Rider->GetCharacterMovement()->DisableMovement(); // �̵� ��Ȱ��ȭ
	Rider->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RidingSocket"));
	Rider->SetActorEnableCollision(false);
	Rider->DisableInput(nullptr);	
	EnableInput(Cast<AC_WorldPlayerController>(Rider->GetController()));
}

void AC_SMSRiding::DisMount_Implementation()
{
	if (!CurrentRider)return;

	CurrentRider->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentRider->SetActorEnableCollision(true);
	CurrentRider->EnableInput(Cast<AC_WorldPlayerController>(CurrentRider->GetController()));
	DisableInput(nullptr);

	CurrentRider = nullptr;
}

void AC_SMSRiding::OnMount(AC_PlayerCharacter* Rider)
{
	if (!bOnRiding)
	{
		Mount(Rider);
		bOnRiding = true;
	}
	else
	{
		DisMount();
		bOnRiding = false;
		Destroy();
	}
}

void AC_SMSRiding::Move(FVector2D Value)
{
	FVector2D MovementVector = Value;

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// �¿� �Է¿� ���� ȸ�� ����
		const float MaxYawOffset = 30.0f;  // �ִ� �¿� ȸ�� ����
		float YawOffset = MovementVector.Y * MaxYawOffset;

		// ���ο� �̵� ���� ���
		FRotator AdjustedRotation = YawRotation + FRotator(0, YawOffset, 0);
		FVector AdjustedDirection = FRotationMatrix(AdjustedRotation).GetUnitAxis(EAxis::X);

		// �Է¿� ���� �ӵ� ���� ���� (��/�� �Է�)
		float ForwardInput = MovementVector.X;
		if (ForwardInput > 0.f)
		{
			AddMovementInput(AdjustedDirection, ForwardInput);
		}
		else if (ForwardInput <= 0.f)
		{
			YawOffset = -MovementVector.Y * MaxYawOffset;
			AdjustedRotation = YawRotation + FRotator(0, YawOffset, 0);
			AdjustedDirection = FRotationMatrix(AdjustedRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(AdjustedDirection, ForwardInput/8);
		}
	}
}

void AC_SMSRiding::LookAt(FVector2D Value)
{
	FVector2D LookAxisVector = Value;

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC_SMSRiding::ServerRun_Implementation()
{
	Run();
}

void AC_SMSRiding::Run()
{
	if (!bOnRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = RUN_SPEED;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	}
	bOnRun = !bOnRun;
}
