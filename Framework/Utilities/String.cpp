#include "Framework.h"
#include "String.h"

#include <iomanip>  // 입출력 스트림의 조작자 정의 헤더, 조작자는 스트림의 출력 형식 제어
#include <sstream>  // 문자열 스트림을 정의, 메모리 버퍼에 데이터를 읽고 쓰는데 사용


// "one, two, three" -> "one" "two" "three"
#pragma region SplitString(문자열을 지정된 구분자로 분할하는 기능)
// 결과출력벡터, 문자열, 문자열 구분 문자
void String::SplitString(std::vector<std::string>* result, std::string origin,
                         std::string tok) {
  int cutAt = 0;  // 자를 위치
  while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos) {
    if (cutAt > 0) {  // 자르는 위치가 0보다 크다면
      result->push_back(origin.substr(0, cutAt));
    }
    origin = origin.substr(cutAt + 1);
  }

  if (origin.length() > 0) {  // 자르고도 남은게 있다면
    result->push_back(origin.substr(0, cutAt));
  }
}

void String::SplitString(std::vector<std::wstring>* result, std::wstring origin,
                         std::wstring tok) {
  result->clear();
  int cutAt = 0;  // 자를 위치
  while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos) {
    if (cutAt > 0) {
      result->push_back(origin.substr(0, cutAt));
    }
    origin = origin.substr(cutAt + 1);
  }

  if (origin.length() > 0) {
    result->push_back(origin.substr(0, cutAt));
  }
}
#pragma endregion

// 특정 문자로 시작하는지 검사
#pragma region StartWith
bool String::StartWith(std::string str, std::string comp) {
  std::wstring::size_type index = str.find(comp);

  // npos(no position) = 못 찾았음
  if (index != std::wstring::npos && (int)index == 0) {
    return true;
  }
  return false;
}

bool String::StartWith(std::wstring str, std::wstring comp) {
  std::wstring::size_type index = str.find(comp);

  if (index != std::wstring::npos && (int)index == 0) {
    return true;
  }
  return false;
}

#pragma endregion

// 특정 문자를 포함하는지 검사
#pragma region Contain

bool String::Contain(std::string str, std::string comp) {
  size_t found = str.find(comp);

  return found != std::wstring::npos;
}

bool String::Contain(std::wstring str, std::wstring comp) {
  size_t found = str.find(comp);

  return found != std::wstring::npos;
}

#pragma endregion

// 특정한 문자들을 다른 문자들로 대체
#pragma region Replace

void String::Replace(std::string* str, std::string comp, std::string rep) {
  std::string temp = *str;

  size_t startPos = 0;
  while (startPos = temp.find(comp, startPos) != std::wstring::npos) {
    temp.replace(startPos, comp.length(), rep);
    startPos += rep.length();
  }

  *str = temp;
}

void String::Replace(std::wstring* str, std::wstring comp, std::wstring rep) {
  std::wstring temp = *str;

  size_t startPos = 0;
  while (startPos = temp.find(comp, startPos) != std::wstring::npos) {
    temp.replace(startPos, comp.length(), rep);
    startPos += rep.length();
  }

  *str = temp;
}

#pragma endregion

#pragma region ToString
// setprecision : 부동 소수점 숫자의 정밀도를 설정하는 조작자
std::string String::ToString(Vector3 vec3, int precision) {
  std::string temp;
  std::stringstream stream1, stream2, stream3;

  stream1 << std::fixed << setprecision(precision) << vec3.x;
  stream2 << std::fixed << setprecision(precision) << vec3.y;
  stream3 << std::fixed << setprecision(precision) << vec3.z;

  temp = "X : " + stream1.str() + " Y : " + stream2.str() +
         " Z : " + stream3.str();

  return temp;
}

std::wstring String::ToWstring(Vector3 vec3, int precision) {
  std::wstring temp;
  std::wstringstream stream1, stream2, stream3;

  stream1 << std::fixed << setprecision(precision) << vec3.x;
  stream2 << std::fixed << setprecision(precision) << vec3.y;
  stream3 << std::fixed << setprecision(precision) << vec3.z;

  temp = L"X : " + stream1.str() + L" Y : " + stream2.str() + L" Z : " +
         stream3.str();

  return temp;
}

// wstring -> string
std::string String::ToString(std::wstring str) {
  std::string temp = "";
  temp.assign(str.begin(), str.end());

  return temp;
}

// string -> wstring
std::wstring String::ToWstring(std::string str) {
  std::wstring temp = L"";
  temp.assign(str.begin(), str.end());

  return temp;
}

#pragma endregion
