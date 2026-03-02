// Tima

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UE08SpiralStairs.generated.h"

UCLASS()
class DEADHORIZON_API AUE08SpiralStairs : public AActor
{
    GENERATED_BODY()

public:
    AUE08SpiralStairs();

    // Ступени
    UPROPERTY(EditAnywhere, Category = "Stair Settings")
    UStaticMesh* StepMesh;

    // Высота подъёма одной ступени
    UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "1"))
    int32 Height = 20;

    // Радиус лестницы
    UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "-2000.0", ClampMax = "2000.0"))
    float Radius = 200.0f;

    // Количество ступеней на один оборот
    UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "3"))
    int32 StepsPerTurn = 12;

    // Количество оборотов
    UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "1"))
    int32 NumberOfTurns = 3;

    // Толщина ступени (в мировых единицах)
    UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "1"))
    float StepThickness = 10.0f;

    // Меш для центральной колонны (может быть любой)
    UPROPERTY(EditAnywhere, Category = "Stair Settings")
    UStaticMesh* CenterMesh;

    // Компонент центральной колонны (создаётся в конструкторе)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stair Settings")
    UStaticMeshComponent* CenterColumn;

protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

    // Построить / перестроить лестницу
    void BuildStair();

    // Удалить все существующие ступени
    void DestroyStairComponents();

private:
    // Массив созданных ступеней
    TArray<UStaticMeshComponent*> StepComponents;
};