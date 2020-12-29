#include "HTMLBuilder.h"

#include <sstream>
#include <iostream>

static void printTag(std::stringstream& ss, HTMLTag* tag, int tab) {

  for (int i = 0; i < tab; i++) {
    ss << '\t';
  }

  ss << "<" << tag->Name;

  if (tag->Attribs.Attribs.size() > 0)
  {
    for (int i = 0; i < tag->Attribs.Attribs.size(); i++)
    {
      ss << " " << tag->Attribs.Attribs.at(i) << "=\"" << tag->Attribs.Values.at(i) << "\"";
    }
  }

  ss << ">";

  if (!tag->InnerTags.empty())
    ss << std::endl;

  for (auto& inner : tag->InnerTags) {
    printTag(ss, inner, tab + 1);
    for (int i = 0; i < tab; i++) {
      ss << '\t';
    }
  }

  ss << tag->Content;

  if (tag->Closable)
  {
    ss << "</" << tag->Name << ">";
  }

  //if (!tag->InnerTags.empty())
  ss << std::endl;
}

HTMLBuilder::HTMLBuilder() {

}

HTMLBuilder::~HTMLBuilder() {

}

std::string HTMLBuilder::Build(HTMLTag* tag) {
  std::stringstream ss;

  ss << "<!DOCTYPE html>" << std::endl;
  printTag(ss, tag, 0);

  return ss.str();
}