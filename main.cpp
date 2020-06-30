#include <iostream>
#include <string>
#include <cassert>
#include <mem.h>

struct ci_char_traits: public std::char_traits<char>
{
  static bool eq(char c1, char c2)
  {
    return toupper(c1) == toupper(c2);
  }
  static bool lt(char c1, char c2)
  {
    return toupper(c1) < toupper(c2);
  }
  static int compare(const char* s1, const char* s2, size_t n)
  {
    return memicmp(s1, s2, n);
  }
  static const char* find(const char* s, int n, char a)
  {
    while(n-- > 0 && toupper(*s) != toupper(a))
    {
      ++s;
    }
    return n >= 0 ? s : 0;
  }
};

typedef std::basic_string<char, ci_char_traits> ci_string;

int main()
{
  ci_string s("AbCde");
  assert(s == "abcde");
  assert(s == "ABCDE");

  assert(strcmp(s.c_str(), "AbCde") == 0);
  assert(strcmp(s.c_str(), "abcde") != 0);

  std::cout << s.c_str() << std::endl;

  std::string a = "aaa";
  ci_string   b = "bbb";
  std::string c = a + b.c_str();
}
