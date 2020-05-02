#pragma once

#include "Components/ActorComponent.h"
#include "OutlineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDGAME_API UOutlineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UOutlineComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterSkeletalMesh(class USkeletalMeshComponent* NewSkeletalMesh);
	void RegisterStaticMesh(class UStaticMeshComponent* NewStaticMesh);

	void SetStencilValue(float NewStencilValue);
	void ShowOutline();
	void HideOutline();

private:

	class USkeletalMeshComponent* SkeletalMesh;
	class UStaticMeshComponent* StaticMesh;

};
