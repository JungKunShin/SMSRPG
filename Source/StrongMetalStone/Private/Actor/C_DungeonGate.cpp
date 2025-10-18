// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C_DungeonGate.h"
#include "C_SMSGameInstance.h"
#include "Character/C_PlayerCharacter.h"
#include "HUD/C_WorldHUD.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_DungeonGate::AC_DungeonGate()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMeshComponent);

}

void AC_DungeonGate::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_DungeonGate::BeginOverlapBoxCollision);
}

void AC_DungeonGate::BeginOverlapBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!HasAuthority()) return;

	if (CastWCharacter(GetMyCharacter())->PartyInfo.PartyOwner == OtherActor)
	{
		//for (int i = 0; i < CastWCharacter(OtherActor)->PartyInfo.PartyPlayers.Num(); ++i)
		//{
		//	AC_PlayerCharacter* Player = CastWCharacter(OtherActor)->PartyInfo.PartyPlayers[i];
		//	if (Player)
		//	{
		//		Player->ClientSetLoading(true, true);
		//	}
		//}
		Cast<UC_SMSGameInstance>(GetGameInstance())->OpenDungeonLevel(LevelName, PortNum, CastWCharacter(OtherActor),this);
	}
}
