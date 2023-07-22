#pragma once

class Time : public SingletonBase<Time> {
 public:
  friend class SingletonBase<Time>;

  bool Stopped() { return isTimerStopped; }
  double Delta() { return isTimerStopped ? 0.0f : timeElapsed; }

  // 실제 경과한 시간
  double WorldOriginDelta() { return isTimerStopped ? 0.0 : runningTime - lastWorldUpdate; } 
  // 게임 속도 반영해서 경과한 시간
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

  bool isTimerStopped;// 타이머 중지
  double timeElapsed;// 이전 프레임으로부터 경과시간

	INT64 ticksPerSecond;// 초당 틱카운트
	INT64 currentTime;// 현재 시간
	INT64 lastTime;// 이전시간
	INT64 lastFPSUpdate;// 마지막 FPS 업데이트 시간
	INT64 fpsUpdateInterval;// fps 업데이트 간격

	UINT frameCount;// 프레임 수
	double runningTime;// 진행 시간
	double framePerSecond;// FPS

  double globalSpeed = 1.0; // 게임 내 시간 흐름 보정
  double lastWorldUpdate = -1.0; // 마지막 게임 업데이트 시간

	std::map<std::string, double> timer;
};