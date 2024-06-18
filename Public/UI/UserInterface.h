// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInterface.generated.h"

/**
 * 
 */
UCLASS()
class STAZZAGADKA_API UUserInterface : public UUserWidget
{
	GENERATED_BODY()

public:
	void DisableButtons();
	void EnableResetOneTurnButton();
	void DisableResetOneTurnButton();

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ResetOneTurnButtonClicked();

	UFUNCTION()
	void ResetMapButtonClicked();

	UFUNCTION()
	void FullscreenButtonClicked();

	UFUNCTION()
	void QuitGameButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ResetOneTurnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ResetMapButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> FullscreenButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitGameButton;

	TObjectPtr<class UGameUserSettings> GameSettings;
	TObjectPtr<class AStazZagadkaGameMode> GameMode;
};
