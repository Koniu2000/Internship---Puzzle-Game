// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StazZagadkaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STAZZAGADKA_API AStazZagadkaGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AStazZagadkaGameMode();
	virtual void Tick(float DeltaTime) override;

	void HandlePrevVertexButtonClick();
	void EnableOrDisableResetOneTurn();

	UPROPERTY(BlueprintReadOnly)
	int ResetsLeft;
	bool ResetButtonUsed;


protected:
	virtual void BeginPlay() override;
	void SetSounds();
	void GetAllVertices();

	void HandleVertexClick();
	void HandleGameStart();
	void CheckVertexConnections();
	void ChangeVertexStatus();

	void UpdateCurrentToPreviousVertex();

	void LoseCondition();
	void WinCondition();

	void UpdateMusic();
	void ChangeMapSprite();

	void AddWinSummaryWidgetAfterTime();
	void AddLoseSummaryWidgetAfterTime();

	bool GameWon;
	bool GameLost;
	bool GameStart;
	bool ShouldBreak;

private:
	UPROPERTY(VisibleAnywhere, Category = "Audio")
	TObjectPtr<class UAudioComponent> BackgroundMusicAudio;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	TObjectPtr<class UAudioComponent> LoseSoundAudio;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	TObjectPtr<class UAudioComponent> WinSoundAudio;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<class USoundBase> BackgroundMusic;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<class USoundBase> LoseSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<class USoundBase> WinSound;

	FTimerHandle WidgetAddTimerHandle;
	TObjectPtr<class AVertex> CurrentVertex;
	TObjectPtr<class AVertex> ClickedVertex;
	TObjectPtr<class AVertex> PreviousVertex;
	TObjectPtr<class AConnection> UsedConnection;
	TObjectPtr<class AStazZagadkaPlayerController> PlayerController;
	TArray<class AVertex*> Vertices;
};
