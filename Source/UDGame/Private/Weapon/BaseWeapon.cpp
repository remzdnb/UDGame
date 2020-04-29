#include "Weapon/BaseWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

ABaseWeapon::ABaseWeapon()
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
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

