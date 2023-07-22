#include "stdafx.h"
#include "Character/Enemy.h"

#include "Utilities/EnemyState/EnemyState.h"
#include "Character/Animations.h"

ENM_SoldierKnife::ENM_SoldierKnife(Vector3 position, Vector3 size, Room* spawnedRoom)
  : Enemy(position, size, spawnedRoom)
{
  graphic->InitAnimation(Animations::GetSoldierKnife());

  init({ 96, 64 });
  initStates();
}

ENM_SoldierKnife::~ENM_SoldierKnife()
{
}

void ENM_SoldierKnife::initStates()
{
  stateComps[EnemyState::NONE] = &EnemyStates::es_none;
  stateComps[EnemyState::SPAWNED] = &EnemyStates::es_spawned;
  stateComps[EnemyState::SCREAM] = &EnemyStates::es_scream;
  stateComps[EnemyState::STANDBY] = &EnemyStates::es_standBy;
  stateComps[EnemyState::COMBAT] = &EnemyStates::es_combatKnife;
  stateComps[EnemyState::ATTACK] = &EnemyStates::es_attackKnife;
  stateComps[EnemyState::RETURN] = &EnemyStates::es_return;
  stateComps[EnemyState::HIT] = &EnemyStates::es_hit;

  currStateComp = stateComps[EnemyState::SPAWNED];
}

ENM_SoldierBZK::ENM_SoldierBZK(Vector3 position, Vector3 size, Room* spawnedRoom)
  : Enemy(position, size, spawnedRoom)
{
  graphic->InitAnimation(Animations::GetSoldierBazooka());

  init({ 500, 250 });
  initStates();
}

ENM_SoldierBZK::~ENM_SoldierBZK()
{
}

void ENM_SoldierBZK::initStates()
{
  stateComps[EnemyState::NONE] = &EnemyStates::es_none;
  stateComps[EnemyState::SPAWNED] = &EnemyStates::es_spawned;
  stateComps[EnemyState::SCREAM] = &EnemyStates::es_scream;
  stateComps[EnemyState::STANDBY] = &EnemyStates::es_standBy;
  stateComps[EnemyState::COMBAT] = &EnemyStates::es_combatBZK;
  stateComps[EnemyState::ATTACK] = &EnemyStates::es_attackBZK;
  stateComps[EnemyState::RETURN] = &EnemyStates::es_return;
  stateComps[EnemyState::HIT] = &EnemyStates::es_hit;

  currStateComp = stateComps[EnemyState::SPAWNED];
}