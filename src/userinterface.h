#pragma once

#include <string>
#include <algo/vector.hpp>

class UITable {
public:
  virtual void clear() = 0;
  virtual void set_title(algo::vector<std::wstring> title) = 0;
  virtual void add_row(algo::vector<std::wstring> row) = 0;
  virtual void render() = 0;
  virtual ~UITable() {};
};


class UIForms {
  public:
  virtual ~UIForms() {};
};
