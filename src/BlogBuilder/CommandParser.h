#ifndef CommandParser_h
#define CommandParser_h

#include <string>
#include <vector>

enum class FlagType {
  Output
};

struct Flag {
  FlagType Type;
  std::string Value;
};

struct Command {
  std::vector<Flag> Flags;
  std::vector<std::string> Files;
};

class CommandParser {
public:
  CommandParser();
  ~CommandParser();

  Command& Parse(int argc, char** argv);
  Command& GetCommand();
private:
  Command m_Command;
};

#endif /* end of include guard: CommandParser_h */