#pragma once

#include <string>
#include <algo/vector.hpp>
#include <algo/map.hpp>

class UITable {
public:
  // Очистить информацию о заголовках и данных в таблице.
  virtual void clear() = 0;
  // Установить названия столбцов.
  virtual void set_title(algo::vector<std::wstring> &title) = 0;
  // Добавить строку таблицы.
  virtual void add_row(algo::vector<std::wstring> &row) = 0;
  // Отобразить таблицу.
  virtual void render() = 0;
  virtual ~UITable() {};
};


class UIForms {
public:
  virtual void clear() = 0;
  virtual void add_value(std::wstring key, std::wstring value) = 0;
  virtual void render() = 0;
  virtual ~UIForms() {};
};
