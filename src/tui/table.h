#pragma once
#include "../userinterface.h"
#include <string>

class TuiTable: public virtual UITable {
  algo::vector<std::wstring> title;
  algo::vector<algo::vector<std::wstring>> rows;
  algo::vector<size_t> column_width;

  void calculate_table_width();
  void render_title();
  void render_line();
  void render_body();

public:
  void clear() override;
  void set_title(algo::vector<std::wstring> &t) override;
  void add_row(algo::vector<std::wstring> &r) override;
  void render() override;
  ~TuiTable() override;
};
