#include "BaseItem.h"
#include "Engine/Engine.h" //GEngine
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ABaseItem::ABaseItem()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->SetWorldScale3D(FVector(1.1f));
	RootComponent = RootScene;

	BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	BaseStaticMesh->SetCollisionProfileName("IgnoreAll");
	BaseStaticMesh->SetupAttachment(RootScene);

	BaseSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseSkeletalMesh"));
	BaseSkeletalMesh->SetCollisionProfileName("IgnoreAll");
	BaseSkeletalMesh->SetupAttachment(RootScene);

	PrimaryActorTick.bCanEverTick = true;

	/*static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataTableAsset(TEXT("DataTable'/Game/Blueprints/Data/ItemData_DT.ItemData_DT'"));
	if (ItemDataTableAsset.Object != NULL)
		ItemDataTable = ItemDataTableAsset.Object;*/
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseItem::AttachToCharacterHand(ACharacter* TargetCharacter)
{
	this->AttachToComponent(TargetCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandSocket");
}