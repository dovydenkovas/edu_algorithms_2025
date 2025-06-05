#pragma once
#include "../userinterface.h"

class TuiForms: public UIForms {
  algo::vector<std::pair<std::wstring, std::wstring>> values;
public:
  virtual void clear() override;
  virtual void add_value(std::wstring key, std::wstring value) override;
  virtual void render() override;
  ~TuiForms() {}
};
