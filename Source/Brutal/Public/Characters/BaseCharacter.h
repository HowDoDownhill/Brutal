// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BRUTAL_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Components
protected:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* FPMesh;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* FPCamera; 

public:
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetFPMesh(){return FPMesh;}

	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetFPCamera(){return FPCamera;}
	
	
	//********Movement********//
protected:
	UPROPERTY(EditDefaultsOnly)
	UCharacterMovementComponent* CharacterMovementComponent;
	
	UPROPERTY(EditDefaultsOnly); 
	float MaxWalkSpeed = 750;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentWalkSpeed); 
	float CurrentWalkSpeed; 

public:
	UFUNCTION(BlueprintCallable)
	UCharacterMovementComponent* GetCharacterMovementComponent(){return CharacterMovementComponent;};

	UFUNCTION(BlueprintCallable)
	void SetCharacterMovementComponent(UCharacterMovementComponent* NewCharacterMovementComponent) {CharacterMovementComponent = NewCharacterMovementComponent;}

	UFUNCTION(BlueprintCallable)
	float GetMaxWalkSpeed() {return MaxWalkSpeed;}
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SetCurrentWalkSpeed(float NewCurrentWalkSpeed);

	UFUNCTION(BlueprintCallable)
	float GetCurrentWalkSpeed(){return CurrentWalkSpeed;}
	
	UFUNCTION()
	void OnRep_CurrentWalkSpeed();
	
	//********Health and Shields********// 
	
	

};
