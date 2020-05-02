#include "Pawn/TurretBuilding.h"
#include "Pawn/DetectionComponent.h"
#include "Core/BaseGameInstance.h"
#include "Components/PoseableMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"


#include "Containers/UnrealString.h"
//#include "Components/SkinnedMeshComponent.h"

ATurretBuilding::ATurretBuilding() : 
    TargetLocation(FVector::ZeroVector)
{

}

void ATurretBuilding::BeginPlay()
{
	Super::BeginPlay();

    DetectionCPT->EnableActiveDetection();
}

void ATurretBuilding::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    RotateTurret();
}

void ATurretBuilding::SetTargetLocation(FVector NewTargetLocation)
{
    TargetLocation = NewTargetLocation;
}

void ATurretBuilding::RotateTurret()
{
    if (GInstance && PMeshCPT)
    {
        FName RingBoneName = GInstance->GetBuildingDataFromRow("Turret_Single_03")->RingBoneName;
        FRotator CurrentRotation = PMeshCPT->GetBoneRotationByName(RingBoneName, EBoneSpaces::WorldSpace);
        FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
        FRotator FinalRotation = FRotator(TargetRotation.Pitch - 90, TargetRotation.Yaw, TargetRotation.Roll);

        PMeshCPT->SetBoneRotationByName(RingBoneName, FinalRotation, EBoneSpaces::WorldSpace);
        //PMeshCP->SetBoneRotationByName(RingBoneName, FMath::Lerp(CurrentRotation, TargetRotation, 0.5f), EBoneSpaces::WorldSpace);
        GEngine->AddOnScreenDebugMessage(50, 1.5f, FColor::Green, FString::Printf(TEXT("yo : %s"), *TargetLocation.ToCompactString()), false);
    }

    /*FRotator CurrentRotation = BaseSkeletalMesh->GetBoneRotationByName(FName("Prop_left"), EBoneSpaces::ComponentSpace);

    FRotator PropRotation = CurrentRotation;
    PropRotation.Pitch -= PropSpeed * DeltaTime;

    PoseMesh->SetBoneRotationByName(FName("Prop_left"), PropRotation, EBoneSpaces::ComponentSpace);*/
    

}
