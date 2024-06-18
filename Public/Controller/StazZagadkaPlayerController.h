// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StazZagadkaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STAZZAGADKA_API AStazZagadkaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStazZagadkaPlayerController();
	virtual void Tick(float DeltaTime) override;

	void AddWinSummaryWidget();
	void AddLoseSummaryWidget();

	void RemoveUI();
	void DisableUI();

	void EnableGameUIResetOneTurnButton();
	void DisableGameUIResetOneTurnButton();

	bool VertexClicked;
	TObjectPtr<class AVertex> HittedVertex;
	TObjectPtr<AActor> HitActor;

protected:
	virtual void BeginPlay() override;

	void CheckMouseClick();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UUserInterface> GameUI;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USummaryWidget> WinSummaryWidget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USummaryWidget> LoseSummaryWidget;
};
