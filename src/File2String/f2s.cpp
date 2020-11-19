// Reads a file into a macro using the #read macro

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> files;

void lexFlags(int argc, char* argv[]);
void searchFiles();

int main(int argc, char* argv[])
{
  lexFlags(argc, argv);

  searchFiles();
}

void lexFlags(int argc, char* argv[])
{
  for (int i = 1; i < argc; ++i)
  {
    std::ifstream file(argv[i]);

    if (file.good())
      files.push_back(argv[i]);
  }
}

void searchFiles()
{
  for (auto& f : files) // go through every file
  {
    std::ifstream text(f); // read the file data into the buffer
    std::stringstream ss;
    ss << text.rdbuf();
    f = ss.str();

    std::stringstream buf;
    std::stringstream readFile;

    for (auto i = 0; i < f.size(); ++i)
    {
      if (f[i] == '#' &&
        f[i + 1] == 'r' &&
        f[i + 2] == 'e' &&
        f[i + 3] == 'a' &&
        f[i + 4] == 'd' &&
        f[i + 5] == ' ' &&
        f[i + 6] == '"') // found read macro
      {
        i += 7;
        while (f[i] != '"')
        {
          readFile << f[i];
          i++;
        }

        continue;
      }

      buf << f[i];
    }
  }
}
