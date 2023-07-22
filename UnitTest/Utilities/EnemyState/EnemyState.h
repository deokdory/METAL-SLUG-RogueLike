#pragma once

class EnemyState
{
public:
  enum State
  {
    NONE,
    SPAWNED, SCREAM, STANDBY, 
    COMBAT, ATTACK, 
    RETURN, HIT
  };

  virtual ~EnemyState() {}
  virtual EnemyState::State Update(class Enemy& enemy) { return State::NONE; }
  virtual void Enter(class Enemy& enemy) {}

protected:
  virtual void movementBasic(class Enemy& enemy);

};

class ES_Spawned : public EnemyState
{
public:
    virtual EnemyState::State Update(Enemy& enemy);
    virtual void Enter(Enemy& enemy);
};

class ES_Scream : public EnemyState
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_StandBy : public EnemyState
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_Combat : public EnemyState
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_CombatKnife : public ES_Combat
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_CombatBZK : public ES_Combat
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_Attack : public EnemyState
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_AttackKnife : public ES_Attack
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_AttackBZK : public ES_Attack
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_Return : public EnemyState
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class ES_Hit : public EnemyState
{
public:
  virtual EnemyState::State Update(class Enemy& enemy);
  virtual void Enter(class Enemy& enemy);
};

class EnemyStates
{
public:
  static EnemyState es_none;
  static ES_Spawned es_spawned;
  static ES_Scream es_scream;
  static ES_StandBy es_standBy;
  static ES_Combat es_combat;
  static ES_CombatKnife es_combatKnife;
  static ES_CombatBZK es_combatBZK;
  static ES_Attack es_attack;
  static ES_AttackKnife es_attackKnife;
  static ES_AttackBZK es_attackBZK;
  static ES_Return es_return;
  static ES_Hit es_hit;
};