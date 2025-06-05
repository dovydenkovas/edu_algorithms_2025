#include "operator.h"
#include "entities.h"
#include <algo/list.hpp>
#include <algo/search.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include "validators.h"
#include <locale.h>
#include <codecvt>

// Регистрация нового клиента.
void Operator::add_user(User user) {
  if (users.contains(user.get_passport_number()))
    throw Error::UserExist;
  users.insert(user.get_passport_number(), user);
}

// Снятие с обслуживания клиента.
void Operator::remove_user(std::wstring passport) {
  // При удалении сведений о клиенте должны быть учтены и обработаны
  // ситуации, когда эта SIM-карта уже выдана клиенту.

  if (!users.contains(passport))
    throw Error::UserNotExist;

  // Удалить все карты клиента
  for (auto reg = registrations.begin(); reg != registrations.end();)
    if ((*reg).get_passport_number() == passport) {
      sims[(*reg).get_sim_number()].free(true); // Симка не выдана.
      registrations.erase(reg); // Удалить запись о выдаче.
    } else
      ++reg;
}

// Просмотр всех зарегистрированных клиентов.
void Operator::show_all_users() {
  table->clear();
  algo::vector<wstring> title{L"Номер паспорта", L"Имя клиента",
                              L"Год рождения", L"Адрес", L"Дата выдачи паспорта"};
  table->set_title(title);

  for (auto &a : users) {
    User user = a.second;
    wstring passport = user.get_passport_number();
    wstring name = user.get_name();
    wstringstream year;
    year << user.get_birth_year();
    wstring address = user.get_address();
    wstring date = user.get_passport_date_of_issue();

    algo::vector<wstring> row{passport, name, year.str(), address, date};
    table->add_row(row);
    }
  table->render();
}

// Очистка данных о клиентах
void Operator::remove_all_users() {
  users.clear();
}

// Поиск клиента по «номер паспорта».
// Результаты поиска – все сведения о найденном клиенте и номера SIM-карт,
// которые ему выданы.
void Operator::find_user(wstring passport_number) {
  if (users.contains(passport_number)) {
    forms->clear();
    User &user = users[passport_number];
    wstringstream year;
    year << user.get_birth_year();
    forms->add_value(L"Имя клиента", user.get_name());
    forms->add_value(L"Номер паспорта", passport_number);
    forms->add_value(L"Год рождения", year.str());
    forms->add_value(L"Адрес", user.get_address());
    forms->add_value(L"Дата выдачи паспорта", user.get_passport_date_of_issue());
    forms->render();
  }
}

  // Поиск клиента по фрагментам ФИО или адреса.
  // Результаты поиска – список найденных клиентов с указанием номера паспорта,
  // ФИО и адреса
  void Operator::find_users(wstring pattern) {
    // Поиск клиента по фрагментам ФИО или адреса должен осуществляться путем
    // систематического обхода АВЛ-дерева поиска. Метод обхода определяется
    // вариантом задания. При поиске клиента по фрагментам ФИО или адреса могут
    // быть заданы как полное ФИО или адрес, так и их части (например, только
    // фамилия клиента без имени и отчества, только название улицы из адреса).
    // Для обнаружения заданного фрагмента в полном ФИО или адресе должен
    // применяться алгоритм поиска слова в тексте, указанный в варианте задания.

    table->clear();
    algo::vector<wstring> title{L"Номер паспорта", L"Имя клиента",
                                  L"Год рождения", L"Адрес"};
    table->set_title(title);
    for (auto &[id, user]: users) {
    if (algo::search(user.get_name(), pattern) || algo::search(user.get_address(), pattern)) {
        wstring passport = user.get_passport_number();
        wstring name = user.get_name();
        wstringstream year;
        year << user.get_birth_year();
        wstring address = user.get_address();

        algo::vector<wstring> row{passport, name, year.str(), address};
        table->add_row(row);
      }
    }
    table->render();
  }

  // Добавление новой SIM-карты
  void Operator::add_sim(Sim sim) {
    if (sims.contains(sim.get_number()))
      throw Error::SimExist;
    sims.insert(sim.get_number(), sim);
  }

  // Удаление сведений о SIM-карте
  void Operator::remove_sim(wstring number) {
    if (!sims.contains(number))
      return;
    // При удалении сведений о SIM-карте должны быть учтены и обработаны
    // ситуации, когда эта SIM-карта уже выдана клиенту.
    for (auto it = registrations.begin(); it != registrations.end(); ++it) {
       if ((*it).get_sim_number() == number) {
        registrations.erase(it);
        break;
       }
    }

    sims.erase(number);
  }

  // Просмотр всех имеющихся SIM-карт;
  void Operator::show_all_sim() {
    table->clear();
    algo::vector<wstring> title{L"Номер карты", L"Тариф",
                                  L"Год выпуска", L"Выдана ли карта"};
    table->set_title(title);
    for (auto [id, sim]: sims) {
      wstring number = sim.get_number();
      wstring tariff = sim.get_tariff();
      wstring is_sim_issue_user = sim.is_free() ? L"Не выдана" : L"Выдана";
      wstringstream year;
      year << sim.get_issue_year();
      algo::vector<wstring> row{number, tariff, year.str(), is_sim_issue_user};
      table->add_row(row);
    }
    table->render();
  }

  // Очистку данных о SIM-картах;
  void Operator::remove_all_sim() {
    sims.clear();
    registrations.clear();
  }

  // Поиск SIM-карты по «номеру SIM-карты».
  // Результаты поиска – все сведения о найденной SIM-карте, а также ФИО и номер
  // паспорта клиента, которому выдана эта SIM-карта;
  void Operator::find_sim(wstring sim_number) {
    forms->clear();
    if (sims.contains(sim_number)) {
      auto sim = sims[sim_number];
      forms->add_value(L"Номер карты", sim.get_number());
      forms->add_value(L"Тариф", sim.get_tariff());
      wstringstream year;
      year << sim.get_issue_year();
      forms->add_value(L"Год выпуска", year.str());

      if (sim.is_free()) {
        forms->add_value(L"Регистрация карты", L"Карта не выдана");
      } else {
        wstring date_of_reg = L"Карта не выдана";
        wstring date_of_exp = L"";
        wstring username = L"";
        wstring passport = L"";
        for (auto reg: registrations) {
          if (reg.get_sim_number() == sim_number) {
            forms->add_value(L"Дата выдачи", reg.get_registration_date());
            forms->add_value(L"Срок действия истекает", reg.get_expiration_date());
            forms->add_value(L"ФИО клиента", users[reg.get_passport_number()].get_name());
            forms->add_value(L"Номер паспорта", users[reg.get_passport_number()].get_passport_number());
            break;
          }
        }
      }
      forms->render();
    }
  }

  // Поиск SIM-карты по тарифу. Результаты поиска – список найденных SIM-карт с
  // указанием «номера SIM-карты», тарифа, года выпуска;
  void Operator::find_sims(wstring pattern) {
    // Метод поиска SIM-карты по тарифу определяется студентом самостоятельно.
    // Выбранный метод необходимо сравнить с альтернативными методами.
    table->clear();
    algo::vector<wstring> title{L"Номер карты", L"Тариф", L"Год выпуска"};
    table->set_title(title);
    for (auto [id, sim]: sims) {
      wstring tariff = sim.get_tariff();
      if (algo::search(tariff, pattern)) {
        wstring number = sim.get_number();
        wstringstream year;
        year << sim.get_issue_year();
        algo::vector<wstring> row{number, tariff, year.str()};
        table->add_row(row);
      }
    }
    table->render();
  }

  // Регистрацию выдачи клиенту SIM-карты;
  void Operator::registration_sim(SimRegistation simreg) {
    // Регистрация выдачи SIM-карты клиенту должна осуществляться только при
    // наличии SIM-карты у оператора сотовой связи (значение поля «Признак
    // наличия» для соответствующей SIM-карты имеет значение «Истина»). При
    // регистрации выдачи SIM-карты клиенту или возврата SIM-карты клиентом
    // должно корректироваться значение поля «Признак наличия» для
    // соответствующей SIM-карты.
    //
    // 2. Одному клиенту может быть выдано несколько SIM-карт. Таким образом,
    // могут быть данные, имеющие повторяющиеся значения в своих полях.

    if (!users.contains(simreg.get_passport_number()))
      throw Error::UserNotExist;
    if (!sims.contains(simreg.get_sim_number()))
      throw Error::SimNotExist;

    auto &sim = sims[simreg.get_sim_number()];
    sim.free(false);
    registrations.push_back(simreg);
  }

  // регистрацию возврата SIM-карты от клиента.
  void Operator::remove_registration_sim(wstring sim_number) {
    // При регистрации выдачи SIM-карты клиенту или возврата SIM-карты клиентом
    // должно корректироваться значение поля «Признак наличия» для
    // соответствующей SIM-карты.
  }

// Прочитать запись о пользователе из строки.
User parse_user(const wstring line) {
  wistringstream buff{line};
  wstring passport_number;
  getline(buff, passport_number, L';');

  wstring name;
  getline(buff, name, L';');

  wstring year;
  getline(buff, year, L';');

  wistringstream year_stream{year};
  uint16_t birth_year;
  year_stream >> birth_year;

  wstring address;
  getline(buff, address, L';');

  wstring passport_date_of_issue;
  getline(buff, passport_date_of_issue);

  if (is_valid_passport_number(passport_number) && is_valid_name(name) && is_valid_birth_year(birth_year))
    return User{name, birth_year, address, passport_number, passport_date_of_issue};
  throw runtime_error("User.");
}

// Прочитать запись о SIM-карте из строки.
Sim parse_sim(const wstring line) {
  wistringstream buff{line};
  wstring number;
  getline(buff, number, L';');

  wstring tariff;
  getline(buff, tariff, L';');

  wstring year;
  getline(buff, year);
  wistringstream year_stream{year};
  uint16_t issue_year;
  year_stream >> issue_year;

  if (is_valid_sim_number(number) && is_valid_issue_year(issue_year))
    return Sim{number, tariff, issue_year, true};
  throw runtime_error("Sim.");
}

// Прочитать запись о регистрации из строки.
SimRegistation parse_registration(const wstring line) {
  wistringstream buff{line};
  wstring sim_number;
  getline(buff, sim_number, L';');

  wstring passport_number;
  getline(buff, passport_number, L';');

  wstring registration_date;
  getline(buff, registration_date, L';');

  wstring expiration_date;
  getline(buff, expiration_date);

  if (is_valid_sim_number(sim_number) && is_valid_passport_number(passport_number))
      return SimRegistation{sim_number, passport_number, registration_date, expiration_date};
    throw runtime_error("Reg.");
}

// Открыть файл базы данных.
void Operator::open(const wstring filename) {
  sims.clear();
  users.clear();
  registrations.clear();

  wifstream ifile{std::filesystem::path{filename}};
  ifile.imbue(std::locale(locale(), new std::codecvt_utf8<wchar_t>));

  enum {NONE, USERS, SIMS, REGISTRATIONS} state;
  state = NONE;
  wstring line;
  getline(ifile, line);
  while (!ifile.eof()) {
    // Если строка задает название секции
    if (line == L"") {}
    else if (line == L"[users]") state = USERS;
    else if (line == L"[sims]") state = SIMS;
    else if (line == L"[regs]") state = REGISTRATIONS;
    else {
      // Если строка содержит запись, принадлежащую секции
      if (state == USERS) add_user(parse_user(line));
      else if (state == SIMS) add_sim(parse_sim(line));
      else if (state == REGISTRATIONS) registration_sim(parse_registration(line));
      else throw std::runtime_error("None section.");
    }
  getline(ifile, line);
  }
}

// Сохранить базу данных в файл.
void Operator::save(wstring filename) {
 wofstream ofile{std::filesystem::path{filename}};
 ofile.imbue(std::locale(locale(), new std::codecvt_utf8<wchar_t>));
 ofile << "[users]" << endl;
 for (auto [id, user]: users) {
   ofile << id << L';' << user.get_name()  << L';'
   << user.get_birth_year() << L';' << user.get_address() << L';'
   << user.get_passport_date_of_issue() << endl;
 }

 ofile << "[sims]" << endl;
 for (auto [id, sim]: sims) {
   ofile << id << L';' << sim.get_tariff()  << L';'
   << sim.get_issue_year() << endl;
 }

 ofile << "[regs]" << endl;
 for (auto reg: registrations) {
   ofile << reg.get_sim_number() << L';' << reg.get_passport_number()  << L';'
   << reg.get_registration_date() << L';' << reg.get_expiration_date() << endl;
 }
}
