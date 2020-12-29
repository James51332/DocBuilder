#ifndef HTMLBuilder_h
#define HTMLBuilder_h

#include <string>
#include <sstream>
#include <vector>

struct AttribsList {
  std::vector<std::string> Attribs;
  std::vector<std::string> Values;

  AttribsList(std::vector<std::string> a, std::vector<std::string> v)
    : Attribs(a), Values(v) {}

  AttribsList()
    : Attribs(), Values() {}
};

struct HTMLTag
{
  std::string Name;
  AttribsList Attribs;
  std::vector<HTMLTag*> InnerTags;
  std::string Content;
  bool Closable;

  HTMLTag()
    : Name(""), Attribs(AttribsList()), InnerTags(), Content(""), Closable(true) {}

  HTMLTag(std::string name, AttribsList attribs, bool closable = true)
    : Name(name), Attribs(attribs), InnerTags(), Content(""), Closable(closable) {}

  HTMLTag(std::string name, AttribsList attribs, std::string innerHTML, bool closable = true)
    : Name(name), Attribs(attribs), InnerTags(), Content(innerHTML), Closable(closable) {}

  void AddTag(HTMLTag* tag) {
    InnerTags.push_back(tag);
  }
};

class HTMLBuilder
{
public:
  HTMLBuilder();
  ~HTMLBuilder();

  void PushDoctype();
  std::string Build(HTMLTag* tag);

private:
  HTMLTag m_TagRef;
};

#endif /* end of include guard: HTMLBuilder_h */