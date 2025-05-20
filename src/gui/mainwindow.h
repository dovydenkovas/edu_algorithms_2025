#pragma once
#include "../operator.h"
#include "../userinterface.h"
#include <type_traits>
#include <vector>
#include <functional>

namespace labels {
const std::wstring prompt_on_error = L"Укажите номер действия";

const std::wstring ask_open_database_or_create_new =
    LR"===(Необходимо открыть существующую базу данных или создать новую?
Введите имя файла базы данных для открытия или <Enter> для создания новой базы.)===";

const std::wstring main_menu_actions = LR"===(Выберите действие:
Клиенты:
  1) зарегистрировать
  2) снять с обслуживания
  3) просмотр всех зарегистрированных клиентов
  4) очистить данные о клиентах
  5) поиск клиента по ФИО или адресу

SIM-карты:
  6) добавить карту
  7) удалить карту
  8) просмотр всех имеющихся карт
  9) поиск карты по номеру
  10) поиск карты по тарифу

  11) выдать карту клиенту
  12) вернуть карту оператору

>>> )===";
} // namespace labels

void add_user();
void del_user();
void show_users();
void clear_users();
void search_user();
void add_sim();
void del_sim();
void show_sims();
void search_sim_by_number();
void search_sim_by_tarif();
void reg_user_sim();
void del_user_sim();

template <size_t first, size_t last> bool in_range(size_t n) {
  return n >= first && n <= last;
}

class GuiMainWindow {
  Operator *op;
  UIForms *forms;

  const algo::vector<std::function<void()>> main_menu_run{
      add_user,
      del_user,
      show_users,
      clear_users,
      search_user,
      add_sim,
      del_sim,
      show_sims,
      search_sim_by_number,
      search_sim_by_tarif,
      reg_user_sim,
      del_user_sim};

public:
  GuiMainWindow(Operator *op, UIForms *forms);
  void exec();
};
