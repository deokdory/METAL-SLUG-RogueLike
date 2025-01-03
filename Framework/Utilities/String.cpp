#include "Framework.h"
#include "String.h"

#include <iomanip>  // ����� ��Ʈ���� ������ ���� ���, �����ڴ� ��Ʈ���� ��� ���� ����
#include <sstream>  // ���ڿ� ��Ʈ���� ����, �޸� ���ۿ� �����͸� �а� ���µ� ���


// "one, two, three" -> "one" "two" "three"
#pragma region SplitString(���ڿ��� ������ �����ڷ� �����ϴ� ���)
// �����º���, ���ڿ�, ���ڿ� ���� ����
void String::SplitString(std::vector<std::string>* result, std::string origin,
                         std::string tok) {
  int cutAt = 0;  // �ڸ� ��ġ
  while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos) {
    if (cutAt > 0) {  // �ڸ��� ��ġ�� 0���� ũ�ٸ�
      result->push_back(origin.substr(0, cutAt));
    }
    origin = origin.substr(cutAt + 1);
  }

  if (origin.length() > 0) {  // �ڸ��� ������ �ִٸ�
    result->push_back(origin.substr(0, cutAt));
  }
}

void String::SplitString(std::vector<std::wstring>* result, std::wstring origin,
                         std::wstring tok) {
  result->clear();
  int cutAt = 0;  // �ڸ� ��ġ
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

// Ư�� ���ڷ� �����ϴ��� �˻�
#pragma region StartWith
bool String::StartWith(std::string str, std::string comp) {
  std::wstring::size_type index = str.find(comp);

  // npos(no position) = �� ã����
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

// Ư�� ���ڸ� �����ϴ��� �˻�
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

// Ư���� ���ڵ��� �ٸ� ���ڵ�� ��ü
#pragma region Replace

void String::Replace(std::string* str, std::string comp, std::string rep) {
  std::string temp = *str;

  size_t startPos = 0;
  while (true) {
    startPos = temp.find(comp, startPos);
    if (startPos == std::wstring::npos) break;

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
// setprecision : �ε� �Ҽ��� ������ ���е��� �����ϴ� ������
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
