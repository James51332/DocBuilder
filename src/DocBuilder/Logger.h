#ifndef Logger_h
#define Logger_h

#include <string>

namespace Doc
{

  class Logger {
  public:
    static void Log(const std::string& data);
  };

} // namespace Doc

#endif /* end of include guard: Logger_h */