#include "Weapon/BaseWeapon.h"
#include "Components/StaticMeshComponent.h"

ABaseWeapon::ABaseWeapon()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootScene->SetWorldScale3D(FVector(1.1f));
	RootComponent = RootScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetCollisionProfileName("IgnoreAll");
	BaseMesh->SetupAttachment(RootScene);

	MagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagMesh"));
	MagMesh->SetCollisionProfileName("IgnoreAll");
	MagMesh->SetupAttachment(BaseMesh);

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*void ABaseWeapon::AttachToOwnerHand()
{
	ABaseCharacter* OwnerChar = Cast<ABaseCharacter>(GetOwner());

	if (OwnerChar)
		this->AttachToComponent(OwnerChar->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponData.SocketName);
}*/

