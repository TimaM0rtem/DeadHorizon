// Tima.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "MyActorTest.generated.h"

UCLASS()
class DEADHORIZON_API AMyActorTest : public AActor
{
    GENERATED_BODY()

public:
    AMyActorTest();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Niagara component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    UNiagaraComponent* NiagaraComponent;

    // ImplementableEvent: prints component name in log
    UFUNCTION(BlueprintImplementableEvent, Category = "Effects")
    void PrintComponentName();

    // BlueprintNativeEvent: sets Niagara system, logs error if fails
    UFUNCTION(BlueprintNativeEvent, Category = "Effects")
    void SetNiagaraSystem(UNiagaraSystem* NewSystem);
    virtual void SetNiagaraSystem_Implementation(UNiagaraSystem* NewSystem);

    // BlueprintCallable: returns reference to Niagara component
    UFUNCTION(BlueprintCallable, Category = "Effects")
    UNiagaraComponent* GetNiagaraComponent() const;
};