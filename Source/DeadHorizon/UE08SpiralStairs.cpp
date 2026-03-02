// Tima

// Fill out your copyright notice in the Description page of Project Settings.

#include "UE08SpiralStairs.h"
#include "Components/SceneComponent.h"

AUE08SpiralStairs::AUE08SpiralStairs()
{
    PrimaryActorTick.bCanEverTick = false;

    // Создаём корневой компонент (обязательно для отображения в редакторе)
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    // Создаём центральную колонну (будет настраиваться в BuildStair)
    CenterColumn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CenterColumn"));
    CenterColumn->SetupAttachment(RootComponent);
}

void AUE08SpiralStairs::BeginPlay()
{
    Super::BeginPlay();
    BuildStair(); // Для игры
}

void AUE08SpiralStairs::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    BuildStair(); // Для редактора (позволяет видеть изменения сразу)
}

void AUE08SpiralStairs::BuildStair()
{
    // Удаляем старые ступени
    DestroyStairComponents();

    if (!StepMesh)
        return;

    // Основные параметры
    int32 TotalSteps = NumberOfTurns * StepsPerTurn;          // всего ступеней
    float AngleStep = 360.0f / StepsPerTurn;                  // угол поворота между ступенями

    // --- Масштабирование ступеней (делаем их плоскими) ---
    FVector StepScale(1.0f, 1.0f, 1.0f);
    FBoxSphereBounds StepBounds = StepMesh->GetBounds();
    float OriginalStepHeight = StepBounds.BoxExtent.Z * 2.0f; // полная высота исходного меша
    if (OriginalStepHeight > 0.0f)
    {
        StepScale.Z = StepThickness / OriginalStepHeight;     // сжимаем по Z до нужной толщины
    }

    // Создаём ступени динамически
    for (int32 i = 0; i < TotalSteps; i++)
    {
        FString Name = FString::Printf(TEXT("Step_%d"), i);
        UStaticMeshComponent* Step = NewObject<UStaticMeshComponent>(this, *Name);

        Step->SetStaticMesh(StepMesh);
        Step->SetWorldScale3D(StepScale);                     // применяем масштаб
        Step->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

        // Позиция на окружности
        float AngleRad = FMath::DegreesToRadians(i * AngleStep);
        float X = FMath::Cos(AngleRad) * Radius;
        float Y = FMath::Sin(AngleRad) * Radius;
        float Z = i * Height;                                 // подъём по высоте

        Step->SetRelativeLocation(FVector(X, Y, Z));

        // Поворот ступени (направлена по касательной к окружности)
        FRotator Rotation(0.0f, i * AngleStep, 0.0f);
        Step->SetRelativeRotation(Rotation);

        Step->RegisterComponent();                             // делаем компонент активным

        StepComponents.Add(Step);
    }

    // --- Настройка центральной колонны ---
    if (CenterMesh)
    {
        CenterColumn->SetStaticMesh(CenterMesh);

        FBoxSphereBounds ColumnBounds = CenterMesh->GetBounds();
        float OriginalWidth = FMath::Max(ColumnBounds.BoxExtent.X * 2.0f, ColumnBounds.BoxExtent.Y * 2.0f); // диаметр в плоскости XY
        float OriginalHeight = ColumnBounds.BoxExtent.Z * 2.0f;                                              // полная высота меша

        float TotalStairHeight = TotalSteps * Height;          // общая высота лестницы

        FVector ColumnScale(1.0f, 1.0f, 1.0f);
        if (OriginalWidth > 0.0f)
        {
            float ScaleXY = (2.0f * Radius) / OriginalWidth;  // масштаб по X и Y, чтобы колонна заполнила внутренний диаметр
            ColumnScale.X = ScaleXY;
            ColumnScale.Y = ScaleXY;
        }
        if (OriginalHeight > 0.0f)
        {
            ColumnScale.Z = TotalStairHeight / OriginalHeight; // масштаб по высоте
        }

        CenterColumn->SetWorldScale3D(ColumnScale);
        CenterColumn->SetRelativeLocation(FVector::ZeroVector); // колонна в центре
        CenterColumn->SetRelativeRotation(FRotator::ZeroRotator);
    }
    else
    {
        // Если меш не назначен, убираем видимость колонны
        CenterColumn->SetStaticMesh(nullptr);
    }
}

void AUE08SpiralStairs::DestroyStairComponents()
{
    for (UStaticMeshComponent* Comp : StepComponents)
    {
        if (Comp && !Comp->IsBeingDestroyed())
        {
            Comp->DestroyComponent();
        }
    }
    StepComponents.Empty();
}