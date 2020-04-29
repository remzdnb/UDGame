#pragma once

#include "Blueprint/UserWidget.h"
#include "CharacterTopWidget.generated.h"

UCLASS()
class UDGAME_API UCharacterTopWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;

	void Init(class ABaseCharacter* NewCharacterReference);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

private:

	UPROPERTY()
	class ABaseCharacter* CharacterReference;
};
