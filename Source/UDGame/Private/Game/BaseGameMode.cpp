// UDGame
#include "Game/BaseGameMode.h"
#include "Game/BaseGameInstance.h"
#include "Character/BaseCharacter.h"
#include "Character/BaseAIController.h"
#include "Building/CharacterStartBuilding.h"
#include "UDGameTypes.h"
// Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

ABaseGameMode::ABaseGameMode()
{
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGameMode::SpawnAllCharacters()
{
	for (TActorIterator<ACharacterStartBuilding> CharacterStart(GetWorld()); CharacterStart; ++CharacterStart)
	{
		if (CharacterStart->bIsActive)
			SpawnCharacter(CharacterStart->GetSpawnTransform(), CharacterStart->Team);
	}
}

void ABaseGameMode::SpawnCharacter(FTransform SpawnTransform, ETeam Team)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//const FTransform SpawnTransform(FRotator(0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f));

	//ABaseCharacter* TestCharacter = GetWorld()->SpawnActor<ABaseCharacter>(BaseCharacterBP, SpawnTransform.GetLocation(), SpawnTransform.GetRotation(), SpawnParameters);

			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, "team id ok");

			//const FTransform SpawnTransform2(CharacterStart->GetActorRotation(), CharacterStart->GetActorLocation(), FVector(1.0f));

			//const FTransform SpawnTransform(FRotator(0.0f), FVector(0.0f), FVector(1.0f));
			//ABaseCharacter* TestCharacter3 = GetWorld()->SpawnActor<ABaseCharacter>(BaseCharacterBP, CharacterStart->GetSpawnTransform(), SpawnParameters);


	if (Team == ETeam::Ally)
	{
		ABaseCharacter* Character = GetWorld()->SpawnActorDeferred<ABaseCharacter>(AllyCharacterBP, SpawnTransform);
		if (Character)
		{
			Character->Init("Yolo", Team);
			UGameplayStatics::FinishSpawningActor(Character, SpawnTransform);
		}
	}
	if (Team == ETeam::Enemy)
	{
		ABaseCharacter* Character = GetWorld()->SpawnActorDeferred<ABaseCharacter>(EnemyCharacterBP, SpawnTransform); //const ?
		if (Character)
		{
			Character->Init("Yolo", Team);
			UGameplayStatics::FinishSpawningActor(Character, SpawnTransform);
		}
	}


}