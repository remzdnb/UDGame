#include "Pawn/BaseBuilding.h"
#include "Pawn/CombatComponent.h"
#include "Pawn/DetectionComponent.h"
#include "Core/BaseGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PoseableMeshComponent.h"

ABaseBuilding::ABaseBuilding() : 
	RowName("Turret_Single_03")
{
	SceneCPT = CreateDefaultSubobject<USceneComponent>(FName("SceneCPT"));
	RootComponent = SceneCPT;
	SMeshCPT = CreateDefaultSubobject<UStaticMeshComponent>(FName("SMeshCPT"));
	SMeshCPT->SetCollisionProfileName("BlockAll");
	SMeshCPT->SetupAttachment(SceneCPT);
	PMeshCPT = CreateDefaultSubobject<UPoseableMeshComponent>(FName("PMeshCPT"));
	PMeshCPT->SetCollisionProfileName("BlockAll");
	PMeshCPT->SetupAttachment(SceneCPT);

	CombatCPT = CreateDefaultSubobject<UCombatComponent>(FName("CombatCPT"));
	DetectionCPT = CreateDefaultSubobject<UDetectionComponent>(FName("DetectionCPT"));

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseBuilding::Init(FName NewTableRowName, ETeam NewTeam)
{
	RowName = NewTableRowName;
	
	CombatCPT->Init(this, NewTeam);
	DetectionCPT->Init(this);
}

void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();

	GInstance = Cast<UBaseGameInstance>(GetGameInstance());

	Init("Turret_Single_03", ETeam::Ally);
}

void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
