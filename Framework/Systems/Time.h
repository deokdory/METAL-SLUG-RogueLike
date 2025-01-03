#pragma once

class Time : public SingletonBase<Time> {
 public:
  friend class SingletonBase<Time>;

  bool Stopped() { return isTimerStopped; }
  double Delta() { return isTimerStopped ? 0.0f : timeElapsed; }

  // ���� ����� �ð�
  double WorldOriginDelta() { return isTimerStopped ? 0.0 : runningTime - lastWorldUpdate; } 
  // ���� �ӵ� �ݿ��ؼ� ����� �ð�
  double WorldDelta() { return isTimerStopped ? 0.0f : (runningTime - lastWorldUpdate) * globalSpeed; } 

  void WorldUpdate() { this->lastWorldUpdate = runningTime; }

  void Update();

  void Start();
  void Stop();

  double FPS() const { return framePerSecond; }
  double Running() const { return runningTime; }

  void InitNewTimer(std::string name);
  void UpdateTimer(std::string name);
  void DeleteTimer(std::string name);

  double GetTimer(std::string name);
  double GetTimerDelta(std::string name);
  double GetTimerWorldDelta(std::string name);

  void SetGlobalSpeed(double globalSpeed) { this->globalSpeed = globalSpeed; }
  double GetGlobalSpeed() { return globalSpeed; }

 private:
  Time(void);
  ~Time(void);

  bool isTimerStopped;// Ÿ�̸� ����
  double timeElapsed;// ���� ���������κ��� ����ð�

	INT64 ticksPerSecond;// �ʴ� ƽī��Ʈ
	INT64 currentTime;// ���� �ð�
	INT64 lastTime;// �����ð�
	INT64 lastFPSUpdate;// ������ FPS ������Ʈ �ð�
	INT64 fpsUpdateInterval;// fps ������Ʈ ����

	UINT frameCount;// ������ ��
	double runningTime;// ���� �ð�
	double framePerSecond;// FPS

  double globalSpeed = 1.0; // ���� �� �ð� �帧 ����
  double lastWorldUpdate = -1.0; // ������ ���� ������Ʈ �ð�

	std::map<std::string, double> timer;
};