#pragma once

#include "CoreMinimal.h"
#include "Character/C_SMSCharacter.h"
#include "C_Enemy.generated.h"

class UC_SkillSystemComponent;

UCLASS()
class STRONGMETALSTONE_API AC_Enemy : public AC_SMSCharacter
{
	GENERATED_BODY()

public:
	AC_Enemy();

	UFUNCTION(NetMulticast, Reliable)
	virtual void Update() override;

	virtual void BaseAttack(float Value);

	virtual void Death(AC_SMSCharacter* Killer)override;

	UFUNCTION(Server, Reliable)
	void ServerUpdate(FEnemyInfo _EnemyInfo);

	UFUNCTION(NetMulticast, Reliable)
	void MultiUpdate(FEnemyInfo _EnemyInfo);
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	FEnemyInfo EnemyInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* BaseAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* QSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* WSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* ESkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* RSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* DodgeMontage;


	TMap<FString, float> CharacterDamage;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	bool SuperArmor = false;

	//드랍 아이템
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AC_Item>> DropItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AC_Gold> DropGoldClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DropGoldValue = 30;

};
