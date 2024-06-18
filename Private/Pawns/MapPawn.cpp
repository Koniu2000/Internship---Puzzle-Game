// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/MapPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"


AMapPawn::AMapPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	ScaleVector = FVector(0.5f, 0.5f, 0.5f);
	MaxScaleValue = 1.2f;

	MapSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MapSprite"));
	MapSpriteComponent->SetupAttachment(RootComponent);

	KeySpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("KeySprite"));
	KeySpriteComponent->SetupAttachment(MapSpriteComponent);
	KeySpriteComponent->SetRelativeLocation(FVector(0.f, 50.f, 40.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(MapSpriteComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 1200.f;
}

void AMapPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (KeySpriteComponent->GetSprite() == KeySprite && ScaleVector.X < MaxScaleValue)
	{
		ScaleVector.X += 0.002f;
		ScaleVector.Y += 0.002f;
		ScaleVector.Z += 0.002f;


		KeySpriteComponent->SetWorldScale3D(ScaleVector);
	}
}

void AMapPawn::BeginPlay()
{
	Super::BeginPlay();

	MapSpriteComponent->SetSprite(MapSprite);
	KeySpriteComponent->SetWorldScale3D(ScaleVector);
}

void AMapPawn::ChangeMap()
{
	MapSpriteComponent->SetSprite(EndMapSprite);
	KeySpriteComponent->SetSprite(KeySprite);
}