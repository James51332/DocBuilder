#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>

std::string htmlBase = R"(
<!DOCTYPE html>
<html>
  <head>
    <title>Test</title>
    <style>
      html, body
      {
        padding: 0;
        margin: 0;
      }

      body
      {
        width:50%;  
        margin: auto;
      }

      h2 {
        margin: 0;
        padding: 0em;
      }

      h3 {
        margin: 0;
        padding: 0em;
      }

      p {
        margin: 0;
        padding: 0;
      }
    </style>
  </head>
  <body>
)";

std::string htmlFinal = R"(
  </body>
</html>
)";

std::string file;

std::vector<std::string> headings;
std::vector<bool> isHeading;

void checkArgs(int argc, char* argv[]);
void readFile(const char* file);
void findHeaders();

void parseFile();

void writeFile(const char* path);

int main(int argc, char* argv[])
{
  checkArgs(argc, argv);
  readFile(argv[1]);

  findHeaders();
  parseFile();

  writeFile("index.html");

  return 0;
}

void checkArgs(int argc, char* argv[])
{
  if (argc < 1)
  {
    std::cout << "Please Give File!" << std::endl;
    exit(1);
  }

  if (argc > 2)
  {
    std::cout << "Too Many Arguments!" << std::endl;
    exit(1);
  }
}

void readFile(const char* f)
{
  std::ifstream t(f);

  if (!t.good())
  {
    std::cout << "File Not Found!" << std::endl;
    exit(1);
  }

  std::stringstream ss;
  ss << t.rdbuf();

  file = ss.str();
}

bool isHeader(int i)
{
  if (i == 0)
    return file[i] == '#' && file[i + 1] == ' ';
  else
    return file[i] == '#' && file[i + 1] == ' ' && file[i - 1] == '\n';
}

bool isSubheader(int i)
{
  if (i == 0)
    return file[i] == '#' && file[i + 1] == '#' && file[i + 2] == ' ';
  else
    return file[i] == '#' && file[i + 1] == '#' && file[i + 2] == ' ' && file[i - 1] == '\n';
}

bool isEmptyLine(int i)
{
  bool check = true;

  if (i == 0) // check if at beginning of file
  {
    for (int j = i; file[j] != '\n'; ++j) // loop through the rest of line
      if (file[j] != ' ') //&& file[j] != '')
        check = false;
  }
  else if (file[i - 1] == '\n')
  {
    bool endLoop = false;
    for (int j = i; endLoop; ++j)
    {
      if (j == file.size())
        return check;

      if (file[j] != ' ' && file[j] != '\n' && file[j] != EOF)
        check = false;
    }
  }

  return check;
}

bool isValidHeaderChar(char c)
{
  return isalnum(c) || c == ' ' || c == '-';
}

void findHeaders()
{
  for (auto i = 0; i < file.size(); ++i) // loop through every character in the file
    if (i != file.size() - 2) // no headers within last few letters (for index out of bounds)
    {
      if (isHeader(i))
      {
        std::stringstream ss;
        for (int j = i + 2; file[j] != '\n' && file[j] != EOF; ++j)
          if (isValidHeaderChar(file[j]))
            ss << file[j];

        headings.push_back(ss.str());
        isHeading.push_back(true);
      }
      else if (isSubheader(i))
      {

        std::stringstream ss;
        for (int j = i + 3; file[j] != '\n' && file[j] != EOF; ++j)
          if (isValidHeaderChar(file[j]))
            ss << file[j];

        headings.push_back(ss.str());
        isHeading.push_back(false);
      }
    }
}

std::vector<int> boldSpots;
std::vector<int> codeSpots;

void parseFile()
{
  bool isHeading = false;
  bool isSubHeading = false;
  bool isBold = false;
  bool lastLineIsHeading = false;
  bool shouldRemoveEmptyLine = false;

  std::stringstream buffer;

  for (auto i = 0; i < file.size(); ++i)
  {
    char c = file[i];

    if (c == EOF) // guarantees that we can check the next character without index out of bounds
      break;

    if (c != '\n' && shouldRemoveEmptyLine) // skips the white space line after headings
      continue;

    if (c == '\n')
    {
      if (isHeading) // if we are on a heading line
      {
        buffer << "</h2>" << std::endl << "<p>";
        isHeading = false;
        if (isEmptyLine(i + 1))
        {
          std::cout << "Line is empty" << std::endl;
          shouldRemoveEmptyLine = true;
        }
        continue; // we don't put a <br> after a heading
      }

      if (isSubHeading)
      {
        buffer << "</h3><p>";
        isSubHeading = false;

        if (isEmptyLine(i + 1))
          shouldRemoveEmptyLine = true;

        continue;
      }

      if (!shouldRemoveEmptyLine)
        buffer << "<br>" << std::endl;
      shouldRemoveEmptyLine = false;
      continue;
    }

    if (isHeader(i))
    {
      buffer << "<h2><p>";
      isHeading = true;
      ++i;
      continue;
    }

    if (isSubheader(i))
    {
      buffer << "<h3><p>";
      isSubHeading = true;
      i += 2;
      continue;
    }

    if (c == '*' && file[i + 1] == '*') // toggle boldness
    {
      if (!isBold)
        buffer << "<strong>";
      else
        buffer << "</strong>";

      isBold = !isBold;
      i++;

      continue;
    }

    buffer << file[i];
  }

  file = buffer.str();
}

void writeFile(const char* path)
{
  std::ofstream p(path);
  p << htmlBase;

  p << "<ul>" << std::endl;
  int headingIndex = 0;
  for (bool s : isHeading)
  {
    if (s)
      p << "<li>" << headings[headingIndex] << "</li>" << std::endl;
    else
      p << "<li style=\"margin-left:20px;\">" << headings[headingIndex] << "</li>" << std::endl;

    headingIndex++;
  }
  p << "</ul>" << std::endl;

  p << file;

  p << htmlFinal;
}