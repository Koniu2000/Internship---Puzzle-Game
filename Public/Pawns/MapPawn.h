// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MapPawn.generated.h"

UCLASS()
class STAZZAGADKA_API AMapPawn : public APawn
{
	GENERATED_BODY()

public:
	AMapPawn();
	void ChangeMap();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	FVector ScaleVector;
	float MaxScaleValue;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSpriteComponent> MapSpriteComponent;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSpriteComponent> KeySpriteComponent;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSprite> MapSprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSprite> EndMapSprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSprite> KeySprite;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	TObjectPtr<class AStazZagadkaGameMode> GameMode;

};
