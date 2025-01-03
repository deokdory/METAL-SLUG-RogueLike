#include "Framework.h"
#include "Path.h"


bool Path::ExistFile(std::string path) {
  return ExistFile(String::ToWstring(path));
}

bool Path::ExistFile(std::wstring path) {
  // 파일이나 폴더의 속성을 알아보는 함수 (DWORLD를 반환)
// 실패하면 INVALID_FILE_ATTRIBUTES를 반환
  DWORD fileValue = GetFileAttributes(path.c_str());

  // 파일이 존재하면 true / false 를 반환
  return fileValue != INVALID_FILE_ATTRIBUTES;
}

// 폴더 존재 여부
bool Path::ExistDirectory(std::string path) {
  return ExistDirectory(String::ToWstring(path));
}

bool Path::ExistDirectory(std::wstring path) {

  DWORD attributes = GetFileAttributes(path.c_str());

  BOOL temp = (attributes != INVALID_FILE_ATTRIBUTES &&
               attributes & FILE_ATTRIBUTE_DIRECTORY);
  
  return temp == TRUE;
  
}

// 병합
std::string Path::Combine(std::string path1, std::string path2) {
  return path1 + path2;
}

std::wstring Path::Combine(std::wstring path1, std::wstring path2) {
  return path1 + path2;
}

std::string Path::Combine(std::vector<std::string> paths) {

  std::string temp = "";

  for (std::string path : paths) {
    temp += path;
  }
  return temp;
}

std::wstring Path::Combine(std::vector<std::wstring> paths) {
  
  std::wstring temp = L"";

  for (std::wstring path : paths) {
    temp += path;
  }
  return temp;
}
// 입력된 경로에서 폴더 이름을 반환
std::string Path::GetDirectoryName(std::string path) {
  String::Replace(&path, "\\", "/");
  size_t index = path.find_last_of('/');

  return path.substr(0, index + 1);
}

std::wstring Path::GetDirectoryName(std::wstring path) {
  String::Replace(&path, L"\\", L"/");
  size_t index = path.find_last_of('/');

  return path.substr(0, index + 1);
}

// 파일의 확장자를 반환
std::string Path::GetExtension(std::string path) { 
  String::Replace(&path, "\\", "/");
  size_t index = path.find_last_of('.');

  return path.substr(index + 1, path.length());
}

std::wstring Path::GetExtension(std::wstring path) {
  String::Replace(&path, L"\\", L"/");
  size_t index = path.find_last_of('.');

  return path.substr(index + 1, path.length());
}

// 파일 이름과 확장자를 반환
std::string Path::GetFileName(std::string path) { 
    String::Replace(&path, "\\", "/");
  size_t index = path.find_last_of('/');

  return path.substr(index + 1, path.length());

}

std::wstring Path::GetFileName(std::wstring path) {
  String::Replace(&path, L"\\", L"/");
  size_t index = path.find_last_of('/');

  return path.substr(index + 1, path.length());
}

// 파일 이름만 반환 ( 확장자 제외 )
std::string Path::GetFileNameWithoutExtension(std::string path) {
  std::string fileName = GetFileName(path);
  size_t index = fileName.find_last_of('.');

  return fileName.substr(0, index);
}

std::wstring Path::GetFileNameWithoutExtension(std::wstring path) {
  std::wstring fileName = GetFileName(path);
  size_t index = fileName.find_last_of('.');

  return fileName.substr(0, index);
}

const WCHAR* ImageFilter  = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* TextFilter   = L"Text file\0*.txt";
const WCHAR* TileFilter   = L"Tile file\0*.png;*.bmp;*.jpg;*.json;*.data";
const WCHAR* TMapFilter   = L"TMap file\0*.tmap";

void Path::OpenFileDialog(std::wstring defaultFileName,
                          const WCHAR* fileTypeFilter,
                          const std::wstring defaultFolder,
                          const function<std::wstring(std::wstring)> callback,
                          HWND parentWindowHandle) {

  WCHAR name[255];
  wcscpy_s(name, defaultFileName.c_str());

  std::wstring tempFolder = defaultFolder;

  OPENFILENAME ofn;
  ZERO_MEMORY(ofn);

  ofn.lStructSize = sizeof(OPENFILENAME);     // 
  ofn.hwndOwner = parentWindowHandle;         // 부모창 핸들
  ofn.lpstrFilter = fileTypeFilter;           // 파일 유형 필터
  ofn.lpstrFile = name;                       // 파일 이름
  ofn.lpstrFileTitle = L"불러오기";           // 대화 상자 제목
  ofn.nMaxFile = 255;                         // 파일 이름 최대 크기
  ofn.lpstrInitialDir = tempFolder.c_str();   // 기본 폴더 경로
  ofn.Flags = OFN_NOCHANGEDIR;                // 대화 상자 옵션

  if (GetOpenFileName(&ofn) == TRUE) {          // 대화 상자 열고 사용자가 파일을 선택하면
    if (callback != NULL) {                     // 콜백 함수가 지정되어 있으면
      std::wstring loadName = name;             // 선택된 파일의 경로를 저장
      String::Replace(&loadName, L"\\", L"/");  // 경로에서 역슬래시를 슬래시로 변환
                                                //
      callback(loadName);                       // 콜백 함수 호출
    }
  }
}

void Path::SaveFileDialog(std::wstring defaultFileName,
                          const WCHAR* fileTypeFilter,
                          const std::wstring defaultFolder,
                          const function<void(std::wstring)> callback,
                          HWND parentWindowHandle) {

    WCHAR name[255];
  wcscpy_s(name, defaultFileName.c_str());

  std::wstring tempFolder = defaultFolder;

  OPENFILENAME ofn;
  ZERO_MEMORY(ofn);

  ofn.lStructSize = sizeof(OPENFILENAME);    //
  ofn.hwndOwner = parentWindowHandle;        // 부모창 핸들
  ofn.lpstrFilter = fileTypeFilter;          // 파일 유형 필터
  ofn.lpstrFile = name;                      // 파일 이름
  ofn.lpstrFileTitle = L"저장하기";          // 대화 상자 제목
  ofn.nMaxFile = 255;                        // 파일 이름 최대 크기
  ofn.lpstrInitialDir = tempFolder.c_str();  // 기본 폴더 경로
  ofn.Flags = OFN_NOCHANGEDIR;               // 대화 상자 옵션

  if (GetOpenFileName(&ofn) ==
      TRUE) {  // 대화 상자 열고 사용자가 파일을 선택하면
    if (callback != NULL) {          // 콜백 함수가 지정되어 있으면
      std::wstring saveName = name;  // 선택된 파일의 경로를 저장
      String::Replace(&saveName, L"\\",
                      L"/");  // 경로에서 역슬래시를 슬래시로 변환
                              //
      callback(saveName);  // 콜백 함수 호출
    }
  }

}

// 지정된 폴더에서 특정 유형의 파일들을 찾아 반환하는 함수
void Path::GetFiles(std::vector<std::string>* files, std::string path,
                    std::string filter, bool bFindSubFolder) {
  std::vector<std::wstring> wFiles;
  std::wstring wPath = String::ToWstring(path);
  std::wstring wFilter = String::ToWstring(path);

  GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

  for (wstring str : wFiles) {
    files->push_back(String::ToString(str));
  }
}

void Path::GetFiles(std::vector<std::wstring>* files, std::wstring path,
                    std::wstring filter, bool bFindSubFolder) {

  std::wstring file = path + filter;

  WIN32_FIND_DATA findData;

  // 첫 번째 파일 탐색
  HANDLE handle = FindFirstFile(file.c_str(), &findData);

  // 파일이 발견되면
  if (handle != INVALID_HANDLE_VALUE) {
    do {
      // 발견된 파일이 디렉토리인 경우
      if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
        // 하위 폴더 검색 옵션 활성화됨 & 발견된 디렉토리가 '.'으로 시작하지
        // 않음
        if (bFindSubFolder == true && findData.cFileName[0] != '.') {
          // 발견된 디렉토리의 전체 경로 설정
          std::wstring folder = path + std::wstring(findData.cFileName) + L"/";
          // 재귀적으로 하위 폴더에서 파일 검색
          GetFiles(files, folder, filter, bFindSubFolder);
        }
      } else {  // 발견된 파일이 디렉토리가 아닌 경우
        // 발견된 파일의 전체 경로 생성
        std::wstring fileName = path + std::wstring(findData.cFileName);
        // 벡터에 발견된 파일의 전체 경로 추가
        files->push_back(fileName);
      }
    } while (FindNextFile(handle, &findData));  // 다음 파일 검색
    FindClose(handle);                          // 파일 검색 종료
  }
}

// 주어진 경로에 폴더가 존재하지 않는 경우 폴더 생성
void Path::CreateFolder(std::string path) {
  CreateFolder(String::ToWstring(path));
}

void Path::CreateFolder(std::wstring path) {
  if (ExistDirectory(path) == false) {
    CreateDirectory(path.c_str(), NULL);
  }
}
// 주어진 경로의 모든 하위 폴더 생성
void Path::CreateFolders(std::string path) {
  CreateFolders(String::ToWstring(path));
}

void Path::CreateFolders(std::wstring path) {
  String::Replace(&path, L"\\", L"/");

  std::vector<std::wstring> folders;
  String::SplitString(&folders, path, L"/");

  std::wstring temp = L"";
  for (std::wstring folder : folders) {
    temp += folder + L"/";
    CreateFolder(temp);
  }
}