// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vertex.generated.h"

UENUM(BlueprintType)
enum class EVertexStatus : uint8
{
	Unused UMETA(DisplayName = "Unused"),
	Used UMETA(DisplayName = "Used"),
	InUse UMETA(DisplayName = "InUse")
};

UCLASS()
class STAZZAGADKA_API AVertex : public AActor
{
	GENERATED_BODY()
	
public:	
	AVertex();
	virtual void Tick(float DeltaTime) override;

	void InUseStatus();
	void UsedStatus();
	void UnusedStatus();
	void UpdateLook();

	int GetUsedConnections();
	
	EVertexStatus VertexStatus;
	TArray<AActor*> OverlappingConnections;

protected:
	virtual void BeginPlay() override;
	void GetOverlappingConnections();

	void ChangeSprite();
	void ChangeFlipbookToNull();

private:
	float FlipbookDuration;
	FTimerHandle FlipbookTimer;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSpriteComponent> VertexSprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperFlipbookComponent> VertexFlipbook;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSprite> UnusedVertexSprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSprite> UsedVertexSprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperSprite> InUseVertexSprite;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	TObjectPtr<class UPaperFlipbook> ChangeFlipbook;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TObjectPtr<class USoundBase> ChangeSound;

};
