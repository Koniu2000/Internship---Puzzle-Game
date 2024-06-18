// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/StazZagadkaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Pawns/Vertex.h"
#include "UI/UserInterface.h"
#include "UI/SummaryWidget.h"

AStazZagadkaPlayerController::AStazZagadkaPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	VertexClicked = false;
}

void AStazZagadkaPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckMouseClick();
}

void AStazZagadkaPlayerController::BeginPlay()
{
	if (GameUI)
	{
		GameUI->AddToViewport();
	}
}

void AStazZagadkaPlayerController::CheckMouseClick()
{
	if (WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit)
		{
			HitActor = HitResult.GetActor();
			if (HitActor)
			{
				HittedVertex = Cast<AVertex>(HitActor);
				if (HittedVertex)
				{
					VertexClicked = true;
				}
			}
		}
	}
}

void AStazZagadkaPlayerController::AddLoseSummaryWidget()
{
	if (LoseSummaryWidget)
	{
		LoseSummaryWidget->AddToViewport();
	}
}

void AStazZagadkaPlayerController::AddWinSummaryWidget()
{
	if (WinSummaryWidget)
	{
		WinSummaryWidget->AddToViewport();
	}
}

void AStazZagadkaPlayerController::RemoveUI()
{
	if (GameUI)
	{
		GameUI->RemoveFromParent();
	}
}

void AStazZagadkaPlayerController::DisableUI()
{
	if (GameUI)
	{
		GameUI->DisableButtons();
	}
}

void AStazZagadkaPlayerController::EnableGameUIResetOneTurnButton()
{
	if (GameUI)
	{
		GameUI->EnableResetOneTurnButton();
	}
}

void AStazZagadkaPlayerController::DisableGameUIResetOneTurnButton()
{
	if (GameUI)
	{
		GameUI->DisableResetOneTurnButton();
	}
}