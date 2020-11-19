#include "Logger.h"

#include <iostream>

namespace Doc
{

  void Logger::Log(const std::string& data)
  {
    std::cout << "Doccable: " << data << std::endl;
  }

} // namespace Doc