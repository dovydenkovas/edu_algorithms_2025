#pragma once

#include <string>
#include "entities.h"
#include "userinterface.h"

#include <algo/map.hpp>
#include <algo/hashmap.hpp>
#include <algo/hash.h>
#include <algo/list.hpp>

class Operator {
  algo::map<wstring, User> users;
  algo::hashmap<wstring, Sim, algo::wstring_hash> sims;
  algo::list<SimRegistation> registrations;
  UITable *table;
  UIForms *forms;



public:
  Operator(UITable *table, UIForms *forms) : table{table}, forms{forms} {};

  // Регистрация нового клиента.
  void add_user(User user);

  // Снятие с обслуживания клиента.
  void remove_user(wstring passport);

  // Просмотр всех зарегистрированных клиентов.
  void show_all_users();

  // Очистку данных о клиентах;
  void remove_all_users();

  // Поиск клиента по «номер паспорта».
  // Результаты поиска – все сведения о найденном клиенте и номера SIM-карт,
  // которые ему выданы.
  void find_user(wstring passport);

  // Поиск клиента по фрагментам ФИО или адреса.
  // Результаты поиска – список найденных клиентов с указанием номера паспорта,
  // ФИО и адреса
  void find_users(wstring pattern);

  // Добавление новой SIM-карты
  void add_sim(Sim sim);

  // Удаление сведений о SIM-карте
  void remove_sim(wstring number);

  // Просмотр всех имеющихся SIM-карт;
  void show_all_sim();

  // Очистку данных о SIM-картах;
  void remove_all_sim();

  // Поиск SIM-карты по «номеру SIM-карты».
  // Результаты поиска – все сведения о найденной SIM-карте, а также ФИО и номер
  // паспорта клиента, которому выдана эта SIM-карта;
  void find_sim(wstring sim_number);

  // Поиск SIM-карты по тарифу. Результаты поиска – список найденных SIM-карт с
  // указанием «номера SIM-карты», тарифа, года выпуска;
  void find_sims(wstring pattern);

  // Регистрацию выдачи клиенту SIM-карты;
  void registration_sim(SimRegistation simreg);

  // регистрацию возврата SIM-карты от клиента.
  void remove_registration_sim(wstring passport_number, wstring sim_number);

  // Открыть файл базы данных.
  void open(wstring filename);

  // Сохранить базу данных в файл.
  void save(wstring filename);
};
