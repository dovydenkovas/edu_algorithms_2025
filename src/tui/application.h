#pragma once
#include "../operator.h"
#include "../userinterface.h"
#include <type_traits>
#include <vector>
#include <functional>


using label = const std::wstring;
namespace labels {
  label out_of_range_error = L"Укажите номер действия.";
  label pause = L"Для продолжения нажмите Enter.";

  label ask_open_database_or_create_new =
    LR"===(Необходимо открыть существующую базу данных или создать новую?
Введите имя файла базы данных для открытия или <Enter> для создания новой базы.)===";

label main_menu_actions = LR"===(
== Информационная система «Обслуживание клиентов оператора сотовой связи»

Выберите действие.
Клиенты:                                          SIM-карты:
  1) зарегистрировать                                 9) добавить карту
  2) снять с обслуживания                            10) удалить карту
  3) просмотр всех зарегистрированных клиентов       11) просмотр всех имеющихся карт
  4) очистить данные о клиентах                      12) очистить данные о всех SIM-картах
  5) поиск клиента по номеру паспорта                13) поиск карты по номеру
  6) поиск клиента по ФИО или адресу                 14) поиск карты по тарифу
  7) выдать карту клиенту                            15) открыть базу данных
  8) вернуть карту оператору                         16) сохранить базу данных
                                                     17) выход
)===";

  label default_error = L"Проверьте корректность введенных данных.";

  label add_user_header = L"= Регистрация клиента";
  label del_user_header = L"= Удаление клиента из базы данных";
  label show_users = L"= Зарегистрированные клиенты";
  label clear_users = L"= Удаление информации о всех зарегистрированных клиентах";
  label search_user_by_passport = L"= Поиск клиента по номеру паспорта";
  label search_user_by_name = L"= Поиск клиента по ФИО или адресу";
  label add_sim = L"= Добавление новой SIM-карты";
  label del_sim = L"= Удаление SIM-карты";
  label show_sims = L"= SIM-карты";
  label clear_sims = L"= Удалить данные о всех SIM-картах";
  label search_sim_by_number = L"= Поиск SIM-карты по номеру";
  label search_sim_by_tarif = L"= Поиск SIM-карты по тарифу";
  label reg_user_sim = L"= Регистрация выдачи SIM-карты";
  label del_user_sim = L"= Регистрация возврата SIM-карты";
  label open_database = L"= Загрузка базы данных из файла";
  label save_database = L"= Сохранение базы данных в файл";

  label add_user_input_name = L"Введите ФИО клиента.";
  label add_user_input_name_error = L"ФИО клиента может содержать только символы криллического и латинского алфавита, дефис и не должно быть длинее 50 символов.";
  label add_user_input_year = L"Введите год рождения клиента.";
  label add_user_input_year_error = L"Год рождения должен быть целым числом не меньшим 1900 и не превышающим 2011.";
  label add_user_input_address = L"Введите адрес клиента.";
  label add_user_input_address_error = L"Адрес может быть произвольной строкой.";
  label input_passport_number = L"Введите номер паспорта клиента.";
  label input_passport_number_error = L"Номер паспорта – строка формата «NNNN-NNNNNN», где N – цифры.";
  label input_passport_date_of_issue = L"Введите дату и место выдачи паспорта.";
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

  label input_registration_date = L"Введите дату выдачи карты.";
  label input_expiration_date = L"Введите дату окончания действия карты.";

  label date_error = L"Дата должна быть введена в формате dd.mm.yyyy или dd/mm/yyyy и не быть меньше 01/01/2000.";
} // namespace labels

void pause();

void add_user(Operator *op);
void del_user(Operator *op);
void show_users(Operator *op);
void clear_users(Operator *op);
void search_user_by_passport(Operator *op);
void search_user_by_name(Operator *op);
void add_sim(Operator *op);
void del_sim(Operator *op);
void show_sims(Operator *op);
void clear_sims(Operator *op);
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
      search_user_by_passport,
      search_user_by_name,
      reg_user_sim,
      del_user_sim,
      add_sim,
      del_sim,
      show_sims,
      clear_sims,
      search_sim_by_number,
      search_sim_by_tarif,
      open_database,
      save_database,
      exit_op,
  };

public:
  TuiApplication(Operator *op, UIForms *forms);
  void exec();
};
