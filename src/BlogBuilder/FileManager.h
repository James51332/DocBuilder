#ifndef FileManager_h
#define FileManager_h

#include <string>

class FileManager
{
public:
  FileManager();
  ~FileManager();

  std::string& LoadFile(const std::string& fileName);
  void WriteFile(const std::string& fileName, std::string& data);

private:
  std::string m_Buffer;
};

#endif /* end of include guard: FileManager_h */