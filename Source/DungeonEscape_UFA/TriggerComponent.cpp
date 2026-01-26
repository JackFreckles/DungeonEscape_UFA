// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

    if (MyMover)
    {
        Mover = MyMover->FindComponentByClass<UMoverComponent>();
        if (Mover)
        {
            UE_LOG(LogTemp, Display, TEXT("Successfully found mover component"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find mover component"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("A trigger is not assigned a mover"));
    }

    if (IsPressurePlate)
    {
        OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
        OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
    }

}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
    {
        ActivatorCount = ActivatorCount + 1;
        if (!IsTriggered)
        {
            Trigger(true);
        }
    }
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
    {
        if (ActivatorCount)// If ActivatorCount != 0
        {
            ActivatorCount = ActivatorCount - 1;
        }
        if (IsTriggered && !ActivatorCount) // if IsTriggered == true and ActivatorCount == 0
        {
            Trigger(false);
        }
    }
}

void UTriggerComponent::Trigger(bool NewTriggerValue)
{
    IsTriggered = NewTriggerValue;

    if(Mover)
    {
        Mover->SetShouldMove(IsTriggered);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s doesn't have a mover component!"), *GetOwner()->GetActorNameOrLabel())
    }
}