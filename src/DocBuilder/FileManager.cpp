#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Logger.h"

namespace Doc
{

  FileManager::FileManager()
  {

  }

  FileManager::~FileManager()
  {

  }

  std::string& FileManager::LoadFile(const std::string& fileName)
  {
    std::stringstream ss;
    std::ifstream fileData(fileName);

    if (!fileData.good())
    {
      ss << "File Not Found: " << fileName;
      Logger::Log(ss.str());
      m_Buffer = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
      return m_Buffer;
    }

    ss << fileData.rdbuf();
    m_Buffer = ss.str();
    return m_Buffer;
  }

  void FileManager::WriteFile(const std::string& fileName, std::string& data)
  {
    std::stringstream ss;
    std::ofstream file(fileName);
    file << data;
  }

} // namespace Doc