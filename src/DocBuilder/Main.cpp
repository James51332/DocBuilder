#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>

#include "Parser.h"
#include "FileManager.h"

std::string htmlBase = R"(
<!DOCTYPE html>
<html>
  <head>
    <title>Test</title>
    <link rel="preconnect" href="https://fonts.gstatic.com">
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;500&display=swap" rel="stylesheet">
    <style>
      html, body
      {
        padding: 0;
        margin: 0;
        font-family: 'Roboto', sans-serif;
        font-weight: 300;
      }

      h2 {
        margin: 0;
        padding: 0.25em 0em;
        font-weight: 500;
      }

      h3 {
        margin: 0;
        padding: 0.25em 0em;
        font-weight: 500;
      }

      p {
        margin: 0;
        padding: 0;
      }

      ul {
        list-style-type: none;
        margin: 0;
        padding: 1em;
        width: calc(25% - 2em);
        position: fixed;
        background-color: gray;
        height: 100%;
        display:block;
      }

      li {
        display: block;
      }
      
      a {
        padding: 0.5em;
        text-decoration: none;
        color: black;
        display: block;
        margin
      }

      a:hover, a:focus {
        background-color: darkgray;
      }

      .text {
        width: calc(75% - 2em);
        float: right;
        padding: 1em;
      }

      .code {
        width:calc(100% - 2em);
        padding: 1em;
        margin: 0 auto;
        border-radius: 10px;
        background-color:lightgray;
        line-height:1.2em;
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
std::string writeFile();

int main(int argc, char* argv[])
{
  checkArgs(argc, argv);

  Doc::Parser* p = new Doc::Parser();
  file = p->Parse(argv[1]);

  Doc::HeaderList h = p->GetHeadings(argv[1]);
  headings = h.Headers;
  isHeading = h.IsHeader;


  std::string compiled = writeFile();

  Doc::FileManager* fm = new Doc::FileManager();
  fm->WriteFile("index.html", compiled);

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

static std::string tokenize(std::string& data)
{
  std::stringstream ss;

  for (auto& c : data)
    if (isalpha(c) || c == '-')
      ss << c;

  return ss.str();
}

std::string writeFile()
{
  std::stringstream p;
  p << htmlBase;

  p << "<ul>" << std::endl;
  int headingIndex = 0;
  for (bool s : isHeading)
  {
    if (s)
      p << "<li><a href=\"#" << tokenize(headings[headingIndex]) << "\">" << headings[headingIndex] << "</a></li> " << std::endl;
    else
      p << "<li style=\"margin-left:20px;\"><a href=\"#" << tokenize(headings[headingIndex]) << "\">" << headings[headingIndex] << "</a></li>" << std::endl;

    headingIndex++;
  }
  p << "</ul>" << std::endl;
  p << "<div class=\"text\">" << file << "</div>";
  p << htmlFinal;

  return p.str();
}