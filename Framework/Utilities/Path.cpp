#include "Framework.h"
#include "Path.h"


bool Path::ExistFile(std::string path) {
  return ExistFile(String::ToWstring(path));
}

bool Path::ExistFile(std::wstring path) {
  // �����̳� ������ �Ӽ��� �˾ƺ��� �Լ� (DWORLD�� ��ȯ)
// �����ϸ� INVALID_FILE_ATTRIBUTES�� ��ȯ
  DWORD fileValue = GetFileAttributes(path.c_str());

  // ������ �����ϸ� true / false �� ��ȯ
  return fileValue != INVALID_FILE_ATTRIBUTES;
}

// ���� ���� ����
bool Path::ExistDirectory(std::string path) {
  return ExistDirectory(String::ToWstring(path));
}

bool Path::ExistDirectory(std::wstring path) {

  DWORD attributes = GetFileAttributes(path.c_str());

  BOOL temp = (attributes != INVALID_FILE_ATTRIBUTES &&
               attributes & FILE_ATTRIBUTE_DIRECTORY);
  
  return temp == TRUE;
  
}

// ����
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
// �Էµ� ��ο��� ���� �̸��� ��ȯ
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

// ������ Ȯ���ڸ� ��ȯ
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

// ���� �̸��� Ȯ���ڸ� ��ȯ
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

// ���� �̸��� ��ȯ ( Ȯ���� ���� )
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
  ofn.hwndOwner = parentWindowHandle;         // �θ�â �ڵ�
  ofn.lpstrFilter = fileTypeFilter;           // ���� ���� ����
  ofn.lpstrFile = name;                       // ���� �̸�
  ofn.lpstrFileTitle = L"�ҷ�����";           // ��ȭ ���� ����
  ofn.nMaxFile = 255;                         // ���� �̸� �ִ� ũ��
  ofn.lpstrInitialDir = tempFolder.c_str();   // �⺻ ���� ���
  ofn.Flags = OFN_NOCHANGEDIR;                // ��ȭ ���� �ɼ�

  if (GetOpenFileName(&ofn) == TRUE) {          // ��ȭ ���� ���� ����ڰ� ������ �����ϸ�
    if (callback != NULL) {                     // �ݹ� �Լ��� �����Ǿ� ������
      std::wstring loadName = name;             // ���õ� ������ ��θ� ����
      String::Replace(&loadName, L"\\", L"/");  // ��ο��� �������ø� �����÷� ��ȯ
                                                //
      callback(loadName);                       // �ݹ� �Լ� ȣ��
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
  ofn.hwndOwner = parentWindowHandle;        // �θ�â �ڵ�
  ofn.lpstrFilter = fileTypeFilter;          // ���� ���� ����
  ofn.lpstrFile = name;                      // ���� �̸�
  ofn.lpstrFileTitle = L"�����ϱ�";          // ��ȭ ���� ����
  ofn.nMaxFile = 255;                        // ���� �̸� �ִ� ũ��
  ofn.lpstrInitialDir = tempFolder.c_str();  // �⺻ ���� ���
  ofn.Flags = OFN_NOCHANGEDIR;               // ��ȭ ���� �ɼ�

  if (GetOpenFileName(&ofn) ==
      TRUE) {  // ��ȭ ���� ���� ����ڰ� ������ �����ϸ�
    if (callback != NULL) {          // �ݹ� �Լ��� �����Ǿ� ������
      std::wstring saveName = name;  // ���õ� ������ ��θ� ����
      String::Replace(&saveName, L"\\",
                      L"/");  // ��ο��� �������ø� �����÷� ��ȯ
                              //
      callback(saveName);  // �ݹ� �Լ� ȣ��
    }
  }

}

// ������ �������� Ư�� ������ ���ϵ��� ã�� ��ȯ�ϴ� �Լ�
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

  // ù ��° ���� Ž��
  HANDLE handle = FindFirstFile(file.c_str(), &findData);

  // ������ �߰ߵǸ�
  if (handle != INVALID_HANDLE_VALUE) {
    do {
      // �߰ߵ� ������ ���丮�� ���
      if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
        // ���� ���� �˻� �ɼ� Ȱ��ȭ�� & �߰ߵ� ���丮�� '.'���� ��������
        // ����
        if (bFindSubFolder == true && findData.cFileName[0] != '.') {
          // �߰ߵ� ���丮�� ��ü ��� ����
          std::wstring folder = path + std::wstring(findData.cFileName) + L"/";
          // ��������� ���� �������� ���� �˻�
          GetFiles(files, folder, filter, bFindSubFolder);
        }
      } else {  // �߰ߵ� ������ ���丮�� �ƴ� ���
        // �߰ߵ� ������ ��ü ��� ����
        std::wstring fileName = path + std::wstring(findData.cFileName);
        // ���Ϳ� �߰ߵ� ������ ��ü ��� �߰�
        files->push_back(fileName);
      }
    } while (FindNextFile(handle, &findData));  // ���� ���� �˻�
    FindClose(handle);                          // ���� �˻� ����
  }
}

// �־��� ��ο� ������ �������� �ʴ� ��� ���� ����
void Path::CreateFolder(std::string path) {
  CreateFolder(String::ToWstring(path));
}

void Path::CreateFolder(std::wstring path) {
  if (ExistDirectory(path) == false) {
    CreateDirectory(path.c_str(), NULL);
  }
}
// �־��� ����� ��� ���� ���� ����
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