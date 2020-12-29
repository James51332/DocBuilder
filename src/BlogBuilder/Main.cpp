#include <iostream>
#include <vector>
#include <string>

#include "CommandParser.h"
#include "FileManager.h"
#include "Parser.h"

int main(int argc, char** argv) {
  // Step 0: Read Arguments and Create File List
  CommandParser* cp = new CommandParser();
  cp->Parse(argc, argv);

  // Step 1: Read Files
  std::vector<std::string> files;
  FileManager* fm = new FileManager();
  for (auto& file : cp->GetCommand().Files)
  {
    files.push_back(fm->LoadFile(file));
  }

  // Step 2: Parse Each File
  Parser* parser = new Parser();
  HTMLTag* html = parser->Parse(files.front()); // TODO: Parse and Write Multiple Files

  // Step 3: Build File
  HTMLBuilder* hb = new HTMLBuilder();
  std::string output = hb->Build(html);

  // Step 4: Write Files and Add Padding
  fm->WriteFile("output.html", output);
}