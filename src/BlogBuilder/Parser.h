#ifndef Parser_h
#define Parser_h

#include "HTMLBuilder.h"

class Parser {
public:
  Parser() {}
  ~Parser() {}

  HTMLTag* Parse(std::string& data);
};

#endif /* end of include guard: Parser_h */