// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/StazZagadkaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/Vertex.h"
#include "Pawns/Connections.h"
#include "Pawns/MapPawn.h"
#include "Controller/StazZagadkaPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

AStazZagadkaGameMode::AStazZagadkaGameMode()
{
	BackgroundMusicAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundMusic"));
	BackgroundMusicAudio->SetupAttachment(RootComponent);

	LoseSoundAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("LoseSound"));
	LoseSoundAudio->SetupAttachment(RootComponent);

	WinSoundAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("WinSound"));
	WinSoundAudio->SetupAttachment(RootComponent);

	GameStart = true;
	GameWon = false;
	GameLost = false;
	ShouldBreak = false;
	ResetButtonUsed = false;
	ResetsLeft = 3;
}

void AStazZagadkaGameMode::Tick(float DeltaTime)
{
	if (PlayerController->VertexClicked == true && GameWon == false && GameLost == false)
	{
		if (GameStart == true)
		{
			HandleGameStart();
		}
		else
		{
			HandleVertexClick();
		}

		WinCondition();

		if (ResetsLeft == 0)
		{
			LoseCondition();
		}
		
		PlayerController->VertexClicked = false;
	}

	EnableOrDisableResetOneTurn();
}

void AStazZagadkaGameMode::BeginPlay()
{
	GetAllVertices();

	PlayerController = Cast<AStazZagadkaPlayerController>(GetWorld()->GetFirstPlayerController());

	SetSounds();
}

void AStazZagadkaGameMode::SetSounds()
{
	BackgroundMusicAudio->SetSound(BackgroundMusic);
	BackgroundMusicAudio->Play();
	LoseSoundAudio->SetSound(LoseSound);
	WinSoundAudio->SetSound(WinSound);
}

void AStazZagadkaGameMode::GetAllVertices()
{
	TArray<AActor*> VerticesActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVertex::StaticClass(), VerticesActors);
	for (auto i : VerticesActors)
	{
		AVertex* Vertex = Cast<AVertex>(i);
		if (Vertex)
		{
			Vertices.Add(Vertex);
		}
	}
}

void AStazZagadkaGameMode::HandleVertexClick()
{
	ClickedVertex = PlayerController->HittedVertex;
	ShouldBreak = false;
	if (ClickedVertex != CurrentVertex)
	{
		CheckVertexConnections();
	}
	else
	{
		ClickedVertex = nullptr;
	}

	ResetButtonUsed = false;
}

void AStazZagadkaGameMode::HandleGameStart()
{
	CurrentVertex = PlayerController->HittedVertex;
	CurrentVertex->VertexStatus = EVertexStatus::InUse;
	CurrentVertex->InUseStatus();
	GameStart = false;
	ResetButtonUsed = false;
}

void AStazZagadkaGameMode::HandlePrevVertexButtonClick()
{
	if (!ResetButtonUsed)
	{
		if (CurrentVertex && PreviousVertex)
		{
			if (CurrentVertex->GetUsedConnections() > 1)
			{
				CurrentVertex->UsedStatus();
				UpdateCurrentToPreviousVertex();
			}
			else
			{
				CurrentVertex->UnusedStatus();
				UpdateCurrentToPreviousVertex();
			}

			ResetButtonUsed = true;
			ResetsLeft--;
		}
		else if (CurrentVertex)
		{
			CurrentVertex->UnusedStatus();
			CurrentVertex = nullptr;
			GameStart = true;

			ResetButtonUsed = true;
			ResetsLeft--;
		}
	}
}

void AStazZagadkaGameMode::UpdateCurrentToPreviousVertex()
{
	CurrentVertex = PreviousVertex;
	CurrentVertex->InUseStatus();
	UsedConnection->UpdateToUnusedConnection();
	UsedConnection = nullptr;
	PreviousVertex = nullptr;
}

void AStazZagadkaGameMode::EnableOrDisableResetOneTurn()
{
	if (ResetButtonUsed || ResetsLeft == 0 || GameWon || GameLost)
	{
		PlayerController->DisableGameUIResetOneTurnButton();
	}
	else
	{
		PlayerController->EnableGameUIResetOneTurnButton();
	}
}

void AStazZagadkaGameMode::CheckVertexConnections()
{
	//CurVerConNum = CurrentVertexConnectionNumber && CliVerConNum = ClickedVertexConnectionNumber
	for (int CurVerConNum = 0; CurVerConNum < CurrentVertex->OverlappingConnections.Num(); CurVerConNum++)
	{
		AConnection* CurrentVertexConnection = Cast<AConnection>(CurrentVertex->OverlappingConnections[CurVerConNum]);
		for (int CliVerConNum = 0; CliVerConNum < ClickedVertex->OverlappingConnections.Num(); CliVerConNum++)
		{
			if (CurrentVertex->OverlappingConnections[CurVerConNum] == ClickedVertex->OverlappingConnections[CliVerConNum] && CurrentVertexConnection->CheckStatus() != true)
			{
				AConnection* ClickedVertexConnection = Cast<AConnection>(ClickedVertex->OverlappingConnections[CliVerConNum]);

				UsedConnection = ClickedVertexConnection;

				float Distance = FVector::Dist(CurrentVertexConnection->GetSphereLocation(), CurrentVertex->GetActorLocation());

				if (Distance > 50.f)
				{
					CurrentVertexConnection->RotateFlipbook();
				}

				ClickedVertexConnection->UpdateToUsedConnection();
				ChangeVertexStatus();
				break;
			}
		}
		if (ShouldBreak == true)
		{
			break;
		}
	}
}

void AStazZagadkaGameMode::ChangeVertexStatus()
{
	PreviousVertex = CurrentVertex;

	CurrentVertex->UsedStatus();
	CurrentVertex = ClickedVertex;
	CurrentVertex->InUseStatus();
	ClickedVertex = nullptr;
	ShouldBreak = true;
}

void AStazZagadkaGameMode::LoseCondition()
{
	int AvailableConnections = CurrentVertex->OverlappingConnections.Num();
	for (auto ConnectionActor : CurrentVertex->OverlappingConnections)
	{
		AConnection* Connection = Cast<AConnection>(ConnectionActor);
		if (Connection->CheckStatus() == true)
		{
			AvailableConnections--;
		}
	}

	if (AvailableConnections == 0 && GameWon != true)
	{
		GameLost = true;
		UpdateMusic();
		PlayerController->DisableUI();
		GetWorld()->GetTimerManager().SetTimer(WidgetAddTimerHandle, this, &AStazZagadkaGameMode::AddLoseSummaryWidgetAfterTime, 4.f, false);
	}
}

void AStazZagadkaGameMode::WinCondition()
{
	int NumOfUsedVertices = 0;
	for (AVertex* Vertex : Vertices)
	{
		if (Vertex->VertexStatus == EVertexStatus::InUse || Vertex->VertexStatus == EVertexStatus::Used)
		{
			NumOfUsedVertices++;
		}
	}

	if (NumOfUsedVertices == Vertices.Num())
	{
		GameWon = true;
		UpdateMusic();
		ChangeMapSprite();
		PlayerController->DisableUI();
		GetWorld()->GetTimerManager().SetTimer(WidgetAddTimerHandle, this, &AStazZagadkaGameMode::AddWinSummaryWidgetAfterTime, 4.f, false);
	}
}

void AStazZagadkaGameMode::UpdateMusic()
{
	BackgroundMusicAudio->Stop();

	if (GameWon) 
	{
		WinSoundAudio->Play();
	}
	
	if (GameLost)
	{
		LoseSoundAudio->Play();
	}
}

void AStazZagadkaGameMode::ChangeMapSprite()
{
	AMapPawn* MapPawn = Cast<AMapPawn>(PlayerController->GetPawn());
	MapPawn->ChangeMap();
}

void AStazZagadkaGameMode::AddLoseSummaryWidgetAfterTime()
{
	PlayerController->AddLoseSummaryWidget();
	PlayerController->RemoveUI();
}

void AStazZagadkaGameMode::AddWinSummaryWidgetAfterTime()
{
	PlayerController->AddWinSummaryWidget();
	PlayerController->RemoveUI();
}
