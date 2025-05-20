#pragma once

#include <string>
#include "entities.h"
#include "userinterface.h"

#include <algo/map.hpp>
#include <algo/hashmap.hpp>
#include <algo/hash.h>
#include <algo/list.hpp>

class Operator {
  algo::map<wstring, Client> clients;
  algo::hashmap<wstring, Sim, algo::wstring_hash> sims;
  algo::list<SimRegistation> registrations;
  UITable *table;
  UIForms *forms;

  bool is_match_pattern(wstring str, wstring pattern);


public:
  Operator(UITable *table, UIForms *forms) : table{table}, forms{forms} {};

  // Регистрация нового клиента.
  void add_client(Client client);

  // Снятие с обслуживания клиента.
  void remove_client(Client client);

  // Просмотр всех зарегистрированных клиентов.
  void show_all_clients();

  // Очистку данных о клиентах;
  void remove_all_clients();

  // Поиск клиента по «номер паспорта».
  // Результаты поиска – все сведения о найденном клиенте и номера SIM-карт,
  // которые ему выданы.
  void find_client(wstring passport_number);

  // Поиск клиента по фрагментам ФИО или адреса.
  // Результаты поиска – список найденных клиентов с указанием номера паспорта,
  // ФИО и адреса
  void find_clients(wstring pattern);

  // Добавление новой SIM-карты
  void add_sim(Sim sim);

  // Удаление сведений о SIM-карте
  void remove_sim(Sim sim);

  // Просмотр всех имеющихся SIM-карт;
  void show_all_sim();

  // Очистку данных о SIM-картах;
  void remove_all_sim();

  // Поиск SIM-карты по «номеру SIM-карты».
  // Результаты поиска – все сведения о найденной SIM-карте, а также ФИО и номер
  // паспорта клиента, которому выдана эта SIM-карта;
  void find_sim(string sim_number);

  // Поиск SIM-карты по тарифу. Результаты поиска – список найденных SIM-карт с
  // указанием «номера SIM-карты», тарифа, года выпуска;
  void find_sims(wstring pattern);

  // Регистрацию выдачи клиенту SIM-карты;
  void registration_sim(string passport_number, string sim_number);

  // регистрацию возврата SIM-карты от клиента.
  void remove_registration_sim(string passport_number, string sim_number);
};
