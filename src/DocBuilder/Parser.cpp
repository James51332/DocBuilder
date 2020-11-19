#include "Parser.h"

#include <iostream>
#include <fstream>
#include <sstream>

static bool isHeading(int index, std::string& data)
{
  if (index + 1 >= data.size())
    return false;

  if (index == 0) //If were on our first character, we can't check earlier
    return data[index] == '#' && data[index + 1] == ' ';
  else
    return data[index] == '#' && data[index + 1] == ' ' && data[index - 1] == '\n'; // make sure we're at start of line
}

static bool isSubHeading(int index, std::string& data)
{
  if (index + 2 >= data.size())
    return false;

  if (index == 0)
    return data[index] == '#' && data[index + 1] == '#' && data[index + 2] == ' ';
  else
    return data[index] == '#' && data[index + 1] == '#' && data[index + 2] == ' ' && data[index - 1] == '\n';
}

static bool isEmptyLine(int index, std::string& data)
{
  if (index == 0) // we don't care if the first line is empty
    return false;

  if (data[index - 1] == '\n') // if were on start of new line
    for (; data[index] != '\n' && data[index] != EOF; ++index) // loop through line
      if (data[index] != ' ' && data[index] != '\n' && data[index] != EOF) // if not blank, line isn't blank
        return false;

  return true; // if all line is clear, line is empty
}

static std::string tokenize(int index, std::string& data)
{
  std::stringstream ss;

  for (auto i = index; data[index] != '\n' && data[index] != EOF; ++index)
    if (isalpha(data[index]) || data[index] == '-')
      ss << data[index];

  return ss.str();
}

static std::string tokenizeWithSpace(std::string data)
{
  std::stringstream ss;

  for (auto& c : data)
    if (isalpha(c) || c == '-' || c == ' ')
      ss << c;

  return ss.str();
}

namespace Doc
{

  Parser::Parser()
  {

  }

  Parser::~Parser()
  {

  }

  HeaderList Parser::GetHeadings(const std::string& file)
  {
    fileName = file;
    ReadFile();

    std::vector<std::string> headers;
    std::vector<bool> isHeader;

    for (auto i = 0; i < fileData.size(); ++i) // we add two as a safety for checking in the future
    {
      if (isHeading(i, fileData))
      {
        std::stringstream ss;

        for (auto index = i; fileData[index] != '\n' && fileData[index] != EOF; ++index)
          ss << fileData[index];

        headers.push_back(tokenizeWithSpace(ss.str()));
        isHeader.push_back(true);
      }

      if (isSubHeading(i, fileData))
      {
        std::stringstream ss;

        for (auto index = i; fileData[index] != '\n' && fileData[index] != EOF; ++index)
          ss << fileData[index];

        headers.push_back(tokenizeWithSpace(ss.str()));
        isHeader.push_back(false);
      }
    }

    HeaderList h{ headers, isHeader };
    return h;
  }

  std::string& Parser::Parse(const std::string& file)
  {
    fileName = file;
    ReadFile();

    std::stringstream buf; // we write our parsed characters into here

    bool isBold = false;
    bool isCode = false;

    bool isHeadingLine = false;
    bool isSubHeadingLine = false;

    bool shouldRemoveLineIfEmpty = false;
    bool skipCharsForRestOfLine = false;

    for (auto i = 0; i < fileData.size(); ++i)
    {
      if (fileData[i] == EOF) // guarantees that we can check the next character without index out of bounds
        break;

      char c = fileData[i]; // get our current char
      char next = fileData[i + 1]; // get our future char

      ///// New Lines ////////////////////////////////////////
      if (c == '\n')
      {
        if (isHeadingLine) // end of heading line
        {
          buf << "</h2>";
          isHeadingLine = false;
          shouldRemoveLineIfEmpty = true;
          continue; // h2's create their own line break
        }

        if (isSubHeadingLine)
        {
          buf << "</h3>";// << std::endl;
          isSubHeadingLine = false;
          shouldRemoveLineIfEmpty = true;
          continue;
        }

        if (shouldRemoveLineIfEmpty)
        {
          shouldRemoveLineIfEmpty = false;
          skipCharsForRestOfLine = false;
          continue; // don't create html line break
        }

        buf << "<br/>"; // place an html break in place of a new line
      }

      ///// Boldness /////////////////////////////////////////
      if (c == '*' && next == '*')
      {
        if (!isBold) // if not bold, opening strong tag
          buf << "<strong>";
        else // otherwise, closing strong tag
          buf << "</strong>";

        isBold = !isBold; // toggle boldness
        ++i; // skip next '*'
        continue;
      }

      ///// Code Sections ////////////////////////////////////
      if (c == '\'' && next == '\'' && fileData[i + 2] == '\'')
      {
        if (!isCode) // if not code, open code div
          buf << "<div class=\"code\">";
        else
          buf << "</div>";

        isCode = !isCode;
        i += 2;
        continue;
      }

      ///// Heading //////////////////////////////////////////
      if (isHeading(i, fileData)) // detect if this character is the start of a heading line
      {
        buf << "<h2 id=\"" << tokenize(i, fileData) << "\">";
        isHeadingLine = true; // we close the heading at the end of the line
        i += 1; // skip whitespace
        continue; // don't put '#' into file buffer
      }

      ///// Subheading ///////////////////////////////////////
      if (isSubHeading(i, fileData)) // detect if this character is the start of a heading line
      {
        buf << "<h3 id=\"" << tokenize(i, fileData) << "\">";
        isSubHeadingLine = true; // we close the heading at the end of the line
        i += 2; // skip whitespace
        continue; // don't put '##' into file buffer
      }

      ///// Tabs ///////////////////////////////////////
      if (c == '\t')
      {
        buf << "&emsp;";
        continue;
      }

      ///// Empty Lines ///////////////////////////////////////
      if (isEmptyLine(i, fileData) && shouldRemoveLineIfEmpty) // check if this line is empty and we should remove it
      {
        skipCharsForRestOfLine = true;
      }

      if (skipCharsForRestOfLine) // we create separate if because isEmptyLine only returns true on first char in line
      {
        continue;
      }

      buf << fileData[i]; // Place the character into buffer unless otherwise specified
    }

    return fileData = buf.str();
  }

  void Parser::ReadFile()
  {
    std::ifstream f(fileName);

    if (!f.good())
      std::cout << "File Not Found!" << std::endl;
    else
    {
      std::stringstream ss;
      ss << f.rdbuf();
      fileData = ss.str();
    }

  }

} // namespace Doc