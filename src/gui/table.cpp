#include "table.h"
#include <cstddef>
#include <stdexcept>

// GuiTable::GuiTable() {}

void GuiTable::clear() {
  title.clear();
  rows.clear();
  column_width.clear();
}

void GuiTable::set_title(algo::vector<std::wstring> t) {
  clear();
  title = t;
}

void GuiTable::add_row(algo::vector<std::wstring> row) {
  if (row.size() != title.size())
    throw std::runtime_error(
        "Ошибка формата таблицы. В строке неправильное количество столбцов.");
  rows.push_back(row);
}

void GuiTable::render() {
  calculate_table_width();
  render_line();
  render_title();
  render_line();
  render_body();
  render_line();
}

void GuiTable::calculate_table_width() {
  // Определяет максимальную ширину элементов каждого столбца
  for (size_t i = 0; i < title.size(); ++i)
    column_width.push_back(title[i].size());
  for (size_t i = 0; i < rows.size(); ++i)
    for (size_t j = 0; j < title.size(); ++j)
      if (column_width[j] < rows[i][j].size())
        column_width[j] = rows[i][j].size();
}

void GuiTable::render_line() {
  // Горизонтальная черта
  std::wcout << "*";
  for (size_t i = 0; i < title.size(); ++i) {
    std::wcout.width(column_width[i] + 3);
    std::wcout.fill(L'-');
    std::wcout << "*";
  }
  std::wcout << std::endl;
  std::wcout.fill(L' ');
}

void GuiTable::render_title() {
  // Заголовок таблицы
  std::wcout << "| ";
  for (size_t i = 0; i < title.size(); ++i) {
    std::wcout.width(column_width[i]);
    std::wcout << title[i];
    std::wcout << " | ";
  }
  std::wcout << std::endl;
}

void GuiTable::render_body() {
  // Тело таблицы
  std::wcout.fill(L' ');
  for (size_t i = 0; i < rows.size(); ++i) {
    std::wcout << "| ";
    for (size_t j = 0; j < title.size(); ++j) {
      std::wcout.width(column_width[j]);
      std::wcout << rows[i][j];
      std::wcout << " | ";
    }
    std::wcout << std::endl;
  }
}

GuiTable::~GuiTable() {}
