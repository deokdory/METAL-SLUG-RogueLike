#pragma once
#include <functional>

class Path {
 public:
  static bool ExistFile(std::string path);
  static bool ExistFile(std::wstring path);

  static bool ExistDirectory(std::string path);
  static bool ExistDirectory(std::wstring path);

  static std::string Combine(std::string path1, std::string path2);
  static std::wstring Combine(std::wstring path1, std::wstring path2);

  static std::string Combine(std::vector<std::string> paths);
  static std::wstring Combine(std::vector<std::wstring> paths);

  static std::string GetDirectoryName(std::string path);
  static std::wstring GetDirectoryName(std::wstring path);

  static std::string GetExtension(std::string path);
  static std::wstring GetExtension(std::wstring path);

  static std::string GetFileName(std::string path);
  static std::wstring GetFileName(std::wstring path);

  static std::string GetFileNameWithoutExtension(std::string path);
  static std::wstring GetFileNameWithoutExtension(std::wstring path);

  const static WCHAR* ImageFilter;
  const static WCHAR* ShaderFilter;
  const static WCHAR* TextFilter;
  const static WCHAR* TileFilter;
  const static WCHAR* TMapFilter;

  static void OpenFileDialog(std::wstring defaultFileName, const WCHAR* fileTypeFilter, const std::wstring defaultFolder, const function<void(std::wstring)> callback, HWND parentWindowHandle = NULL);
  static void SaveFileDialog(std::wstring defaultFileName, const WCHAR* fileTypeFilter, const std::wstring defaultFolder, const function<void(std::wstring)> callback, HWND parentWindowHandle = NULL);

  static void GetFiles(std::vector<std::string>* files, std::string path,
                       std::string filter, bool bFindSubFolder);
  static void GetFiles(std::vector<std::wstring>* files, std::wstring path,
                       std::wstring filter, bool bFindSubFolder);

  static void CreateFolder(std::string path);
  static void CreateFolder(std::wstring path);

  static void CreateFolders(std::string path);
  static void CreateFolders(std::wstring path);

  };








