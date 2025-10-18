#pragma once

#include "CoreMinimal.h"
#include "GameMode/C_SMSGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "C_WorldGameMode.generated.h"

UCLASS()
class STRONGMETALSTONE_API AC_WorldGameMode : public AC_SMSGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;	

	virtual void PostLogin(APlayerController* NewPlayer) override; //�÷��̾ �α��ν� ȣ��Ǵ� �Լ�

	void FindStartPoint(); //�������� Ž��	
public:
	void SpawnPlayer(FCharacterInfo _CharacterInfo, APlayerController* PC); //�÷��̾� ����

	virtual void LogOut(APlayerController* _NewPlayer, AC_PlayerCharacter* _Character);

	// ��� Ŭ���̾�Ʈ���� �޽����� ����
	void SendChatMessage(const FString& Message);

public:
	UPROPERTY()
	TArray<APlayerController*> Players; //�������� �÷��̾���Ʈ�ѷ���
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AC_PlayerCharacter*> Characters; //�������� ĳ���͵�
	UPROPERTY()
	TArray<FPartyInfo> PartyDatas; //��Ƽ������


	APlayerStart* WorldPlayerStart; //�÷��̾� ��ŸƮ

private:
	UPROPERTY()
	AC_PlayerCharacter* CurPlayer; //���� ���ӽõ����� ĳ����
	UPROPERTY()
	APlayerController* CurPlayerController; //���� ���ӽõ����� ��Ʈ�ѷ�
};
