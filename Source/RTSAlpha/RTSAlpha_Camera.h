// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSAlpha_Camera.generated.h"

UCLASS()
class RTSALPHA_API ARTSAlpha_Camera : public AActor
{
	GENERATED_BODY()
	
public:	// functions
	
	ARTSAlpha_Camera(); // constructor

	/*
	* Movement functions that translate cursor location 
	* to move the camera in that direction
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void MoveLeft();
	UFUNCTION(BlueprintImplementableEvent)
	void MoveRight();
	UFUNCTION(BlueprintImplementableEvent)
	void MoveUp();
	UFUNCTION(BlueprintImplementableEvent)
	void MoveDown();

	/*
	* Camera speed function to dictate how fast the camera 
	* should move dependant on screen space left 
	*/
	UFUNCTION(BlueprintCallable) 
	float GetCameraSpeed(float sFactor);


public:	// variables

	FVector2D mousePos;
	FVector2D screenSize;

	/* camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Main)
	class UCameraComponent* mainCamera;

	/** camera boom to distance from the ground */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Main)
	class USpringArmComponent* mainCameraBoom;

	/*Scene root object*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Main)
	class USceneComponent* defaultSceneRoot;

protected:

	//virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override; // controls mouse location / movement of camera

};
