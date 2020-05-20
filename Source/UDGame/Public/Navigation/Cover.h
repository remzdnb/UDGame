#pragma once

#include "Core/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

UCLASS()
class UDGAME_API ACover : public AActor
{
	GENERATED_BODY()
	
public:	

	ACover();

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* DirectionArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* CoverParticle;

	bool bIsFullCover;

	void SelfRegisterToNavBlock();

};
