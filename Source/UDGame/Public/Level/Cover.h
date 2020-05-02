#pragma once

#include "Core/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

UCLASS()
class UDGAME_API ACover : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	

	ACover();

	virtual void BeginPlay() override;

	// Interaction Interface

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHoverStart();
	virtual void OnHoverStart_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHoverStop();
	virtual void OnHoverStop_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLeftClick();
	virtual void OnLeftClick_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRightClick();
	virtual void OnRightClick_Implementation() override;

	//

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
