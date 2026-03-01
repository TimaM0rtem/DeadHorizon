// Tima.

#include "MyActorTest.h"
#include "Components/SceneComponent.h"
#include "NiagaraSystem.h"

AMyActorTest::AMyActorTest()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create root component
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    // Create Niagara component
    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(RootComponent);
}

void AMyActorTest::BeginPlay()
{
    Super::BeginPlay();

    // Call the BlueprintImplementableEvent to log component name
    PrintComponentName();
}

void AMyActorTest::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyActorTest::SetNiagaraSystem_Implementation(UNiagaraSystem* NewSystem)
{
    if (NiagaraComponent && NewSystem)
    {
        NiagaraComponent->SetAsset(NewSystem);
        UE_LOG(LogTemp, Log, TEXT("Niagara system set successfully: %s"), *NewSystem->GetName());
    }
    else
    {
        FString AssetName = NewSystem ? NewSystem->GetName() : TEXT("None");
        UE_LOG(LogTemp, Warning, TEXT("Failed to set Niagara system. Asset: %s, Component valid: %d"),
            *AssetName, NiagaraComponent ? 1 : 0);
    }
}

UNiagaraComponent* AMyActorTest::GetNiagaraComponent() const
{
    // Возвращаем указатель на компонент (в Blueprint будет ссылкой)
    return NiagaraComponent;
}