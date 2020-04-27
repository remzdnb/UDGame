#include "Building/CharacterStartBuilding.h"

ACharacterStartBuilding::ACharacterStartBuilding()
{
	Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	Arrow->SetupAttachment(RootComponent);
}

FTransform ACharacterStartBuilding::GetSpawnTransform()
{
	return Arrow->GetComponentTransform();
}

