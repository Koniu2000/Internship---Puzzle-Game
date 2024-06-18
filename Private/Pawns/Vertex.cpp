// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Vertex.h"
#include "Pawns/Connections.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"


AVertex::AVertex()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetCollisionObjectType(ECC_WorldStatic);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	VertexSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("VertexSprite"));
	VertexSprite->SetupAttachment(BoxComponent);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	VertexFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("VertexFlipbook"));
	VertexFlipbook->SetupAttachment(VertexSprite);
	VertexFlipbook->SetRelativeLocation(FVector(0.f, 4.f, 0.f));
	VertexFlipbook->SetCollisionResponseToAllChannels(ECR_Overlap);
	VertexFlipbook->SetCollisionObjectType(ECC_WorldStatic);
	VertexFlipbook->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	VertexStatus = EVertexStatus::Unused;
}

void AVertex::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AVertex::GetOverlappingConnections);
	ChangeSprite();
}

void AVertex::ChangeSprite()
{
	switch (VertexStatus)
	{
		case EVertexStatus::Unused:
			VertexSprite->SetSprite(UnusedVertexSprite);
			break;
		case EVertexStatus::Used:
			VertexSprite->SetSprite(UsedVertexSprite);
			break;
		case EVertexStatus::InUse:
			VertexSprite->SetSprite(InUseVertexSprite);
			break;
	}
}

void AVertex::GetOverlappingConnections()
{
	BoxComponent->GetOverlappingActors(OverlappingConnections, AConnection::StaticClass());
}

void AVertex::ChangeFlipbookToNull()
{
	VertexFlipbook->SetFlipbook(nullptr);
}

void AVertex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVertex::InUseStatus()
{
	VertexStatus = EVertexStatus::InUse;
	UpdateLook();
	if (ChangeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ChangeSound, GetActorLocation());
	}
}

void AVertex::UsedStatus()
{
	VertexStatus = EVertexStatus::Used;
	UpdateLook();
}

void AVertex::UnusedStatus()
{
	VertexStatus = EVertexStatus::Unused;
	UpdateLook();
}

int AVertex::GetUsedConnections()
{
	int NumOfUsedConnections = 0;

	for (AActor* ConnectionActor : OverlappingConnections)
	{
		AConnection* Connection = Cast<AConnection>(ConnectionActor);
		if (Connection->CheckStatus() == true)
		{
			NumOfUsedConnections++;
		}
	}

	return NumOfUsedConnections;
}

void AVertex::UpdateLook()
{
	ChangeSprite();
	VertexFlipbook->SetFlipbook(ChangeFlipbook);
	FlipbookDuration = VertexFlipbook->GetFlipbook()->GetTotalDuration();
	GetWorldTimerManager().SetTimer(FlipbookTimer, this, &AVertex::ChangeFlipbookToNull, FlipbookDuration - 0.1, false);
}
