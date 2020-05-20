#pragma once

#include "UDGameTypes.h"
#include "Components/ActorComponent.h"
#include "DetectionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDGAME_API UDetectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UDetectionComponent();

	void Init(AActor* InParentActor);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EnableActiveDetection();
	void DisableActiveDetection();
	void RegisterDetectedCharacter(class ABaseCharacter* InCharacter);
	void UnregisterDetectedCharacter(class ABaseCharacter* InCharacter);
	bool HasDetectedCharacter();
	class ABaseCharacter* GetClosestDetectedCharacter();
	class ABaseCharacter* GetClosestCharacter();

private:

	UPROPERTY(Transient) AActor* ParentActor;
	UPROPERTY(Transient) TArray<class ABaseCharacter*> DetectedCharacters;

	bool bIsActiveDetectionEnabled;

	void DetectVisibleCharacters(ETeam Team);

	void Debug();
};
