// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserInterface.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/StazZagadkaGameMode.h"

void UUserInterface::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode = Cast<AStazZagadkaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (ResetOneTurnButton)
	{
		ResetOneTurnButton->OnClicked.AddDynamic(this, &UUserInterface::ResetOneTurnButtonClicked);
	}

	if (ResetMapButton)
	{
		ResetMapButton->OnClicked.AddDynamic(this, &UUserInterface::ResetMapButtonClicked);
	}

	if (FullscreenButton)
	{
		FullscreenButton->OnClicked.AddDynamic(this, &UUserInterface::FullscreenButtonClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UUserInterface::QuitGameButtonClicked);
	}

	GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetFullscreenMode(EWindowMode::Fullscreen);
}

void UUserInterface::DisableButtons()
{
	ResetOneTurnButton->SetIsEnabled(false);
	ResetMapButton->SetIsEnabled(false);
	FullscreenButton->SetIsEnabled(false);
	QuitGameButton->SetIsEnabled(false);
}

void UUserInterface::EnableResetOneTurnButton()
{
	ResetOneTurnButton->SetIsEnabled(true);
}

void UUserInterface::DisableResetOneTurnButton()
{
	ResetOneTurnButton->SetIsEnabled(false);
}

void UUserInterface::ResetOneTurnButtonClicked()
{
	if (GameMode)
	{
		GameMode->HandlePrevVertexButtonClick();
	}
}

void UUserInterface::ResetMapButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()));
}

void UUserInterface::FullscreenButtonClicked()
{
	EWindowMode::Type CurrentMode = GameSettings->GetFullscreenMode();
	if (CurrentMode == EWindowMode::Fullscreen)
	{
		GameSettings->SetScreenResolution(FIntPoint(1024, 768));
		GameSettings->SetFullscreenMode(EWindowMode::Windowed);
		GameSettings->ApplyResolutionSettings(false);
	}
	else
	{
		GameSettings->SetScreenResolution(FIntPoint(1024, 768));
		GameSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		GameSettings->ApplyResolutionSettings(false);
	}

	GameSettings->ApplySettings(false);
}

void UUserInterface::QuitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
