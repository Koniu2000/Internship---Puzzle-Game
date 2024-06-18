// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Connections.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

AConnection::AConnection()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetCollisionObjectType(ECC_WorldStatic);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	ConnectionFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ConnectionFlipbook"));
	ConnectionFlipbook->SetupAttachment(BoxComponent);
	ConnectionFlipbook->SetCollisionResponseToAllChannels(ECR_Overlap);
	ConnectionFlipbook->SetCollisionObjectType(ECC_WorldStatic);
	ConnectionFlipbook->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Scene"));
	SphereComponent->SetSphereRadius(1.f);
	SphereComponent->SetupAttachment(ConnectionFlipbook);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->SetCollisionObjectType(ECC_WorldStatic);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	ConnectionUsed = false;
}

void AConnection::BeginPlay()
{
	Super::BeginPlay();
}

void AConnection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AConnection::UpdateToUsedConnection()
{
	ConnectionUsed = true;
	ConnectionFlipbook->SetFlipbook(ActiveConnection);
	ConnectionFlipbook->SetLooping(false);
	ConnectionFlipbook->PlayFromStart();
}

void AConnection::UpdateToUnusedConnection()
{
	ConnectionUsed = false;
	ConnectionFlipbook->Stop();
	ConnectionFlipbook->SetFlipbook(nullptr);
}

bool AConnection::CheckStatus()
{
	return ConnectionUsed;
}

void AConnection::RotateFlipbook()
{
	ConnectionFlipbook->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
}

FVector AConnection::GetSphereLocation()
{
	return SphereComponent->GetComponentLocation();
}

