#include "UnitStats.h"
#include "Definitions.h"

UnitStats::UnitStats(double hp, double damage, double attackSpeed, double moveSpeed)
	:hp(hp),
	damage(damage),
	attackSpeed(attackSpeed),
	moveSpeed(moveSpeed)
{}

void UnitStats::UpHP() {
	hp += 0.1;
}

void UnitStats::DownHP() {
	hp -= 0.1;
}

void UnitStats::UpDamage() {
	damage += 0.1;
}

void UnitStats::DownDamage() {
	damage -= 0.1;
}

void UnitStats::UpMoveSpeed() {
	moveSpeed += 0.1;
}

void UnitStats::DownMoveSpeed() {
	moveSpeed -= 0.1;
}

void UnitStats::UpAttackSpeed() {
	attackSpeed += 0.1;
}

void UnitStats::DownAttackSpeed() {
	attackSpeed -= 0.1;
}