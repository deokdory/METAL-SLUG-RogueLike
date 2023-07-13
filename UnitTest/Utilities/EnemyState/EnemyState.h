#pragma once

class EnemyState
{
public:
  virtual ~EnemyState() {}
  virtual void Update(Enemy& enemy) {};
  virtual void Enter(Enemy& enemy) {};

public:
  static ES_Spawned es_spawned;
  static ES_Scream es_scream;
  static ES_StandBy es_standBy;
  static ES_Detect es_detect;
  static ES_AttackKnife es_attackKnife;
  static ES_AttackBZK es_attackBZK;
  static ES_RETURN  es_return;
  static ES_HIT es_hit;
};

class ES_Spawned : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};

class ES_Scream : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};

class ES_StandBy : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};

class ES_Detect : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};

class ES_AttackKnife : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};

class ES_AttackBZK : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};

class ES_RETURN : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};

class ES_HIT : public EnemyState
{
public:
  virtual void Update(Enemy& enemy);
  virtual void Enter(Enemy& enemy);
};