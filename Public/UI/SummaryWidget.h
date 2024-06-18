// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SummaryWidget.generated.h"

/**
 * 
 */
UCLASS()
class STAZZAGADKA_API USummaryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ResetMapButtonClicked();

	UFUNCTION()
	void QuitGameButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ResetMapButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitGameButton;
};
