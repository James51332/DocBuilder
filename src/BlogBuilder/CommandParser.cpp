#include "CommandParser.h"

#include <cstring>

CommandParser::CommandParser()
  : m_Command() {

}

CommandParser::~CommandParser() {

}

Command& CommandParser::Parse(int argc, char** argv) {
  for (int i = 1; i < argc; i++)
  {
    // Check If Flag
    if (strcmp(argv[i], "-o") && i + 1 < argc) // is -o flag and argument after value
    {
      m_Command.Flags.push_back({ FlagType::Output, std::string(argv[i + 1]) });
      i++; // skip next argument
      continue; // go to next loop
    }

    // Add File
    m_Command.Files.push_back(argv[i]);
  }

  return m_Command;
}

Command& CommandParser::GetCommand() {
  return m_Command;
}
