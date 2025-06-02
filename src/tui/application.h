#pragma once
#include "../operator.h"
#include "../userinterface.h"
#include <type_traits>
#include <vector>
#include <functional>


using label = const std::wstring;
namespace labels {
  label out_of_range_error = L"Укажите номер действия";

  label ask_open_database_or_create_new =
    LR"===(Необходимо открыть существующую базу данных или создать новую?
Введите имя файла базы данных для открытия или <Enter> для создания новой базы.)===";

label main_menu_actions = LR"===(Выберите действие:
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

  13) открыть базу данных
  14) сохранить базу данных
  15) выход)===";


  label default_error = L"Проверьте корректность введенной строки.";

  label add_user_input_name = L"Введите имя клиента.";
  label add_user_input_name_error = L"Имя клиента может содержать только символы криллического и латинского алфавита, дефис и не должно быть длинее 50 символов.";
  label add_user_input_year = L"Введите год рождения клиента.";
  label add_user_input_year_error = L"Год рождения должен быть целым числом не меньшим 1900 и не превышающим 2011.";
  label add_user_input_address = L"Введите адрес клиента.";
  label add_user_input_address_error = L"Адрес может быть произвольной строкой.";
  label add_user_input_passport_number = L"Введите номер паспорта клиента.";
  label add_user_input_passport_number_error = L"Номер паспорта – строка формата «NNNN-NNNNNN», где N – цифры.";
  label input_passport_date_of_issue = L"Введите дату выдачи паспорта.";
  label user_exist = L"Пользователь с указанным паспортом уже существует.";
  label user_not_exist = L"Пользователя с указанным паспортом не существует.";
  label are_you_sure = L"Вы уверены? (да/нет)";
  label are_you_sure_error = L"Необходимо ввести да или нет.)";
  label search_user = L"Введите имя или адрес клиента.";
  label add_sim_input_number = L"Введите номер SIM-карты.";
  label add_sim_input_number_error = L"Номер SIM-карты – строка формата «NNN-NNNNNNN», где N – цифра.";
  label add_sim_input_tariff = L"Введите наименование тарифа.";

  label add_sim_input_year = L"Введите год выпуска карты.";
  label add_sim_input_year_error = L"Год выпуска карты должен быть целым числом, не меньшим 2000 и не превышающим 2025.";
  label sim_exist = L"SIM-карта уже существует.";
  label sim_not_exist = L"SIM-карта с указанным номером не существует.";

  label filename_to_open = L"Укажите имя файла для открытия базы данных.";
  label filename_to_save = L"Укажите имя файла для сохранения базы данных.";
  label open_file_error = L"Не могу открыть файл. Ошибка в имени файла или недостаточно прав.";

  label need_save = L"Все несохраненные изменения будут утеряны. Желаете сохранить базу?";
  label enter_yes_or_no = L"Необходимо ввести да или нет.";

} // namespace labels

void add_user(Operator *op);
void del_user(Operator *op);
void show_users(Operator *op);
void clear_users(Operator *op);
void search_user(Operator *op);
void add_sim(Operator *op);
void del_sim(Operator *op);
void show_sims(Operator *op);
void search_sim_by_number(Operator *op);
void search_sim_by_tarif(Operator *op);
void reg_user_sim(Operator *op);
void del_user_sim(Operator *op);
void open_database(Operator *op);
void save_database(Operator *op);
void exit_op(Operator *op);

template <size_t first, size_t last> bool in_range(size_t n) {
  return n >= first && n <= last;
}

class TuiApplication {
  Operator *op;
  UIForms *forms;

  const algo::vector<std::function<void(Operator *op)>> main_menu_run{
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
      del_user_sim,
      open_database,
      save_database,
      exit_op,
  };

public:
  TuiApplication(Operator *op, UIForms *forms);
  void exec();
};
