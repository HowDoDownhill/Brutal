// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	GetFPCamera()->SetupAttachment(GetRootComponent());
	GetFPCamera()->bUsePawnControlRotation = true; 

	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Arms"));
	GetFPMesh()->SetupAttachment(GetFPCamera());
	GetFPMesh()->SetCastShadow(false);
	GetFPMesh()->SetOnlyOwnerSee(true);

	CurrentWalkSpeed = GetMaxWalkSpeed(); 
	SetCharacterMovementComponent(GetCharacterMovement());
	GetCharacterMovementComponent()->MaxWalkSpeed = CurrentWalkSpeed; 

	GetMesh()->SetOwnerNoSee(true);
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, CurrentWalkSpeed); 
}

void ABaseCharacter::Server_SetCurrentWalkSpeed_Implementation(float NewCurrentWalkSpeed)
{
	this->CurrentWalkSpeed = NewCurrentWalkSpeed;
	OnRep_CurrentWalkSpeed(); 
}

void ABaseCharacter::OnRep_CurrentWalkSpeed()
{
	GetCharacterMovementComponent()->MaxWalkSpeed = GetCurrentWalkSpeed(); 
}


