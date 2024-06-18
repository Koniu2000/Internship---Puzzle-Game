// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Connections.generated.h"

UCLASS()
class STAZZAGADKA_API AConnection : public AActor
{
	GENERATED_BODY()
	
public:	
	AConnection();
	virtual void Tick(float DeltaTime) override;

	void UpdateToUsedConnection();
	void UpdateToUnusedConnection();
	bool CheckStatus();

	void RotateFlipbook();
	FVector GetSphereLocation();

protected:
	virtual void BeginPlay() override;

private:
	bool ConnectionUsed;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperFlipbookComponent> ConnectionFlipbook;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperFlipbook> ActiveConnection;

	UPROPERTY(EditAnywhere, Category = "Scene")
	TObjectPtr<class USphereComponent> SphereComponent;
};
