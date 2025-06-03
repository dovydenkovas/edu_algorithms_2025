#include "operator.h"
#include "entities.h"
#include <algo/list.hpp>
#include <algo/search.h>
#include <sstream>

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
      sims[(*reg).get_sim_number()].issue(false); // Симка не выдана.
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
  table->clear();
  algo::vector<wstring> title{L"Номер паспорта", L"Имя клиента",
                              L"Год рождения", L"Адрес",
                              L"Дата выдачи паспорта"};
  table->set_title(title);

  if (users.contains(passport_number)) {
    User &user = users[passport_number];
    wstringstream year;
    year << user.get_birth_year();

    algo::vector<wstring> row{user.get_passport_number(), user.get_name(),
                              year.str(), user.get_address(), user.get_passport_date_of_issue()};
    table->add_row(row);
    table->render();
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

    algo::vector<wstring> title{L"Номер паспорта", L"Имя клиента",
                                  L"Год рождения", L"Адрес"};
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
      table->render();
    }
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
                                  L"Год выпуска карты", L"Выдана ли карта"};
    table->set_title(title);
    for (auto [id, sim]: sims) {
      wstring number = sim.get_number();
      wstring tariff = sim.get_tariff();
      wstring is_sim_issue_user = sim.is_issue() ? L"Выдана" : L"Не выдана";
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
    table->clear();
    algo::vector<wstring> title{L"Номер карты", L"Тариф",
                                  L"Год выпуска", L"Дата выдачи", L"Срок действия истекает", L"ФИО клиента", L"Номер паспорта"};
    table->set_title(title);
    if (sims.contains(sim_number)) {
      auto sim = sims[sim_number];
      wstring number = sim.get_number();
      wstring tariff = sim.get_tariff();
      wstring date_of_reg = L"Карта не выдана";
      wstring date_of_exp = L"";
      wstring username = L"";
      wstring passport = L"";
      if (sim.is_issue()) {
        for (auto reg: registrations) {
          if (reg.get_sim_number() == sim_number) {
            date_of_reg = reg.get_registration_date();
            date_of_exp = reg.get_expiration_date();
            username = users[reg.get_passport_number()].get_name();
            passport = users[reg.get_passport_number()].get_passport_number();
            break;
          }
        }
      }
      wstringstream year;
      year << sim.get_issue_year();
      algo::vector<wstring> row{number, tariff, year.str(), date_of_reg, date_of_exp, username, passport};
      table->add_row(row);
    }
    table->render();
  }

  // Поиск SIM-карты по тарифу. Результаты поиска – список найденных SIM-карт с
  // указанием «номера SIM-карты», тарифа, года выпуска;
  void Operator::find_sims(wstring pattern) {
    // Метод поиска SIM-карты по тарифу определяется студентом самостоятельно.
    // Выбранный метод необходимо сравнить с альтернативными методами.
  }

  // Регистрацию выдачи клиенту SIM-карты;
  void Operator::registration_sim(wstring passport_number, wstring sim_number) {
    // Регистрация выдачи SIM-карты клиенту должна осуществляться только при
    // наличии SIM-карты у оператора сотовой связи (значение поля «Признак
    // наличия» для соответствующей SIM-карты имеет значение «Истина»). При
    // регистрации выдачи SIM-карты клиенту или возврата SIM-карты клиентом
    // должно корректироваться значение поля «Признак наличия» для
    // соответствующей SIM-карты.
    //
    // 2. Одному клиенту может быть выдано несколько SIM-карт. Таким образом,
    // могут быть данные, имеющие повторяющиеся значения в своих полях.
  }

  // регистрацию возврата SIM-карты от клиента.
  void Operator::remove_registration_sim(wstring passport_number,
                                         wstring sim_number) {
    // При регистрации выдачи SIM-карты клиенту или возврата SIM-карты клиентом
    // должно корректироваться значение поля «Признак наличия» для
    // соответствующей SIM-карты.
  }


  // Открыть файл базы данных.
  void Operator::open(wstring filename) {

  }

  // Сохранить базу данных в файл.
  void Operator::save(wstring filename) {

  }
