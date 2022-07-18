// Quantum.All rights reserved!


#include "UI/PlayerHUDWidget.h"
#include "Weapon/WeaponComponent.h"
#include "Engine/World.h"
#include "QuantumBaseCharacter.h"
#include "Weapons/Projectile.h"
#include "Weapons/M16Weapon.h"
#include "ComponentGetter.h"
#include "Components/HealthComponent.h"

float UPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = GetHealthComponent();
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const auto Component = Player->FindComponentByClass(UWeaponComponent::StaticClass());

	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	
	if (!WeaponComponent) return false;
	
	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UPlayerHUDWidget::GetAmmoData(FAmmoData& AmmoData) const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const auto Component = Player->FindComponentByClass(UWeaponComponent::StaticClass());

	const auto WeaponComponent = UComponentGetter::GetPlayerComponent<UWeaponComponent>(Player);
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);

}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = GetHealthComponent();
	
	return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUDWidget::IsPlayerSpectator() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UPlayerHUDWidget::IsWeaponUpdating() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const auto Component = Player->FindComponentByClass(UWeaponComponent::StaticClass());

	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	if (!WeaponComponent) return false;

	return WeaponComponent->IsNextWeapon;
}




void  UPlayerHUDWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}



UHealthComponent* UPlayerHUDWidget::GetHealthComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return nullptr;

	const auto Component = Player->FindComponentByClass(UHealthComponent::StaticClass());
	const auto HealthComponentt = Cast<UHealthComponent>(Component);

	return HealthComponentt;
}

void UPlayerHUDWidget::OnHealthChanged(float Health,float HealthDelta)
{
	if (HealthDelta > 0.0f)
	{
		OnTakeDamage();
	}
	
}

void UPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
	const auto HealthComponent = UComponentGetter::GetPlayerComponent<UHealthComponent>(Pawn);

	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPlayerHUDWidget::OnHealthChanged);
	}
}





