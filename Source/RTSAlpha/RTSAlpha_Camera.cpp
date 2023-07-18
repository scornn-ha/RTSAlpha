// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSAlpha_Camera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"

// Sets default values
ARTSAlpha_Camera::ARTSAlpha_Camera()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = defaultSceneRoot;

	// Create a camera boom...
	mainCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	mainCameraBoom->SetupAttachment(RootComponent);
	mainCameraBoom->SetUsingAbsoluteRotation(true);
	mainCameraBoom->TargetArmLength = 3000.f;
	mainCameraBoom->SetRelativeRotation(FRotator(-70.f, 90.f, 0.f));
	mainCameraBoom->bDoCollisionTest = false;

	// Create a camera...
	mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mainCamera->SetupAttachment(mainCameraBoom, USpringArmComponent::SocketName);
	mainCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

/*
void ARTSAlpha_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}*/

// Called every frame
void ARTSAlpha_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	mousePos *= UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	screenSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

	this->MoveLeft();
	this->MoveRight();
	this->MoveUp();
	this->MoveDown();


}

float ARTSAlpha_Camera::GetCameraSpeed(float sFactor)
{
	float zoomLoc = UKismetMathLibrary::NormalizeToRange(mainCameraBoom->TargetArmLength, 1000.f, 3000.f);
	zoomLoc *= 40.f;
	zoomLoc += 60.f;

	zoomLoc *= sFactor;
	return zoomLoc;
}

