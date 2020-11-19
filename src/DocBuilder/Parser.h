#ifndef Parser_h
#define Parser_h

#include <vector>
#include <string>

namespace Doc
{

  struct HeaderList
  {
    std::vector<std::string> Headers;
    std::vector<bool> IsHeader;

    HeaderList(std::vector<std::string> h, std::vector<bool> b)
      : Headers(h), IsHeader(b) {}
  };

  class Parser
  {
  public:
    Parser();
    ~Parser();

    HeaderList GetHeadings(const std::string& fileName);
    std::string& Parse(const std::string& fileName);
  private:
    void ReadFile();
  private:

    std::string fileName;
    std::string fileData;
  };

} // namespace Doc

#endif /* end of include guard: Parser_h */