// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SummaryWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

void USummaryWidget::NativeConstruct()
{
	if (ResetMapButton)
	{
		ResetMapButton->OnClicked.AddDynamic(this, &USummaryWidget::ResetMapButtonClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USummaryWidget::QuitGameButtonClicked);
	}
}

void USummaryWidget::ResetMapButtonClicked()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()));
}

void USummaryWidget::QuitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
