#include "Game/BaseGameMode.h"
#include "Game/BaseGameInstance.h"
#include "Character/BaseCharacter.h"
#include "Building/CharacterStartBuilding.h"
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

void ABaseGameMode::SpawnCharacter(uint8 TeamID)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform SpawnTransform(FRotator(0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f));
	if (GetWorld())
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "getworld ok");
	ABaseCharacter* TestCharacter = GetWorld()->SpawnActor<ABaseCharacter>(BaseCharacterBP, FVector(0.0f), FRotator(0.0f), SpawnParameters);

	for (TActorIterator<ACharacterStartBuilding> CharacterStart(GetWorld()); CharacterStart; ++CharacterStart)
	{
		if (CharacterStart->TeamID == TeamID)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, "team id ok");

			const FTransform SpawnTransform2(CharacterStart->GetActorRotation(), CharacterStart->GetActorLocation(), FVector(1.0f));

			//const FTransform SpawnTransform(FRotator(0.0f), FVector(0.0f), FVector(1.0f));
			ABaseCharacter* TestCharacter3 = GetWorld()->SpawnActor<ABaseCharacter>(BaseCharacterBP, CharacterStart->GetSpawnTransform(), SpawnParameters);

			/*ABaseCharacter* const Character = GetWorld()->SpawnActorDeferred<ABaseCharacter>(BaseCharacterBP, SpawnTransform);
			if (Character)
			{
				//Character->Init("Yolo", 0);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, "character ok");
				UGameplayStatics::FinishSpawningActor(Character, SpawnTransform);
			}*/
		}
	}
}