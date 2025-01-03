#include "Framework.h"
#include "Time.h"

Time::Time(void) :
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0), isTimerStopped(true), timeElapsed(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	fpsUpdateInterval = ticksPerSecond >> 1;
}

Time::~Time(void)
{

}

void Time::Update()
{
	if (isTimerStopped) return;

	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	runningTime += timeElapsed;

	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;

		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}

	lastTime = currentTime;
}

void Time::Start()
{
	if (!isTimerStopped)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime);
	isTimerStopped = false;
}

void Time::Stop()
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond;
	isTimerStopped = true;
}

void Time::InitNewTimer(std::string name) { timer.insert(std::make_pair(name, runningTime)); }

void Time::UpdateTimer(std::string name) {
  if (timer.empty()) return;

  auto find = timer.find(name);
  if (find != timer.end()) find->second = runningTime;
}

void Time::DeleteTimer(std::string name)
{
	if (timer.find(name) != timer.end())
		timer.erase(name);
}

double Time::GetTimer(std::string name) {
  if (timer.empty()) return 0;

  auto find = timer.find(name);
  if (find != timer.end())
    return find->second;
  else
    return 0;
}

double Time::GetTimerDelta(std::string name) {
  if (timer.empty()) return 0;

  auto find = timer.find(name);

  if (find != timer.end())
    return runningTime - find->second;
  else
    return 0;

}

double Time::GetTimerWorldDelta(std::string name)
{
	if (timer.empty()) return 0;

	auto find = timer.find(name);

	if (find != timer.end())
		return (runningTime - find->second) * globalSpeed;
	else
		return 0;
}
