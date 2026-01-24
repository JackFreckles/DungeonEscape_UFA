// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	float MyFloat = 6.9f;
	float *FloatPtr = &MyFloat;

	float Result = *FloatPtr + 5.0f;

	UE_LOG(LogTemp, Warning, TEXT("Value of Result is: %f"), Result);
	
	*FloatPtr = 30.0f;
	UE_LOG(LogTemp, Warning, TEXT("Value of *FloatPtr is: %f"), *FloatPtr);

	UE_LOG(LogTemp, Warning, TEXT("FloatPtr points to: %p"), FloatPtr);

	// ---------------------------

	FVector MyFVector = FVector(1.0f, 1.0f, 1.0f);
	FVector *FVectorPtr = &MyFVector;

	FVectorPtr->X = 5.0f;
	FVectorPtr->Y = 32.0f;
	FVectorPtr->Z = 6.9f;

	UE_LOG(LogTemp, Warning, TEXT("MyFVector is: %s"), *FVectorPtr->ToCompactString());
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

