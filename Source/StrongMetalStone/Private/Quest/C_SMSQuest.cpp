// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/C_SMSQuest.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AC_SMSQuest::AC_SMSQuest()
{
	bReplicates = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableObj(TEXT("/Script/Engine.DataTable'/Game/Table/TB_QuestData.TB_QuestData'"));
	if (DataTableObj.Succeeded())
	{
		QuestDataTable = DataTableObj.Object;
	}
}

// Called when the game starts or when spawned
void AC_SMSQuest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_SMSQuest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

// Called every frame
void AC_SMSQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
