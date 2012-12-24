#ifndef SPELLS_FILTER_H
#define SPELLS_FILTER_H

#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

class spells;

struct filter_rule
{
  template <class U, class V>
  filter_rule(U&& attr, V&& rgx)
      : attribute(std::forward<U>(attr)),
        match(std::forward<V>(rgx), std::regex_constants::icase) {}

  std::string attribute;
  std::regex match;
};

class filter
{
public:
  typedef std::map<std::string, std::string> value_type;

  bool match(const value_type& value) const;

  void print_matching(class spells& cont) const;

  template <typename... Args>
  void add_filter(Args&&... args)
    { rules.emplace_back(std::forward<Args>(args)...); }

  std::vector<filter_rule> rules;
};

#endif /* SPELLS_FILTER_H */
