#include "operator.h"
#include "entities.h"
#include <algo/list.hpp>
#include <sstream>

// Регистрация нового клиента.
void Operator::add_client(Client client) {
  if (clients.contains(client.get_passport_number()))
    throw Error::UserExist;
  clients.insert(client.get_passport_number(), client);
}

// Снятие с обслуживания клиента.
void Operator::remove_client(Client client) {
  // При удалении сведений о клиенте должны быть учтены и обработаны
  // ситуации, когда эта SIM-карта уже выдана клиенту.

  if (!clients.contains(client.get_passport_number()))
    throw Error::UserNotExist;

  // Удалить все карты клиента
  for (auto reg = registrations.begin(); reg != registrations.end();)
    if ((*reg).get_passport_number() == client.get_passport_number()) {
      sims[(*reg).get_sim_number()].issue(false); // Симка не выдана.
      registrations.erase(reg); // Удалить запись о выдаче.
    } else
      ++reg;
}

// Просмотр всех зарегистрированных клиентов.
void Operator::show_all_clients() {
  table->clear();
  algo::vector<wstring> title{L"Номер паспорта", L"Имя клиента",
                              L"Год рождения", L"Адрес"};
  table->set_title(title);

  for (auto &a : clients) {
    Client client = a.second;
    wstring passport = client.get_passport_number();
    wstring name = client.get_name();
    wstringstream year;
    year << client.get_birth_year();
    wstring address = client.get_address();

    algo::vector<wstring> row{passport, name, year.str(), address};
    table->add_row(row);
  }
  table->render();
}

// Очистка данных о клиентах
void Operator::remove_all_clients() {
  while (clients.size())
    remove_client((*clients.begin()).second);
}

// Поиск клиента по «номер паспорта».
// Результаты поиска – все сведения о найденном клиенте и номера SIM-карт,
// которые ему выданы.
void Operator::find_client(wstring passport_number) {
  table->clear();
  algo::vector<wstring> title{L"Номер паспорта", L"Имя клиента",
                              L"Год рождения", L"Адрес",
                              L"Дата выдачи паспорта"};
  table->set_title(title);

  if (clients.contains(passport_number)) {
    Client &client = clients[passport_number];
    wstringstream year;
    year << client.get_birth_year();

    algo::vector<wstring> row{client.get_passport_number(), client.get_name(),
                              year.str(), client.get_address(), client.get_passport_date_of_issue()};
    table->add_row(row);
    table->render();
  }
}

  // Поиск клиента по фрагментам ФИО или адреса.
  // Результаты поиска – список найденных клиентов с указанием номера паспорта,
  // ФИО и адреса
  void Operator::find_clients(wstring pattern) {
    // Поиск клиента по фрагментам ФИО или адреса должен осуществляться путем
    // систематического обхода АВЛ-дерева поиска. Метод обхода определяется
    // вариантом задания. При поиске клиента по фрагментам ФИО или адреса могут
    // быть заданы как полное ФИО или адрес, так и их части (например, только
    // фамилия клиента без имени и отчества, только название улицы из адреса).
    // Для обнаружения заданного фрагмента в полном ФИО или адресе должен
    // применяться алгоритм поиска слова в тексте, указанный в варианте задания.

    algo::vector<wstring> title{L"Номер паспорта", L"Имя клиента",
                                  L"Год рождения", L"Адрес"};
    for (auto &[id, client]: clients) {
    if (is_match_pattern(client.get_name(), pattern) || is_match_pattern(client.get_address(), pattern)) {
        wstring passport = client.get_passport_number();
        wstring name = client.get_name();
        wstringstream year;
        year << client.get_birth_year();
        wstring address = client.get_address();

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
  void Operator::remove_sim(Sim sim) {
    // При удалении сведений о SIM-карте должны быть учтены и обработаны
    // ситуации, когда эта SIM-карта уже выдана клиенту. Аналогичным образом
    // следует поступать и с удалением данных о клиентах.


  }

  // Просмотр всех имеющихся SIM-карт;
  void Operator::show_all_sim() {
    //  Состав данных о клиенте или SIM-карте, выдаваемых при просмотре всех
    //  зарегистрированных клиентов или просмотре всех SIM-карт, определяется
    //  студентом самостоятельно, но должен содержать не менее двух полей.
  }

  // Очистку данных о SIM-картах;
  void Operator::remove_all_sim() {}

  // Поиск SIM-карты по «номеру SIM-карты».
  // Результаты поиска – все сведения о найденной SIM-карте, а также ФИО и номер
  // паспорта клиента, которому выдана эта SIM-карта;
  void Operator::find_sim(string sim_number) {}

  // Поиск SIM-карты по тарифу. Результаты поиска – список найденных SIM-карт с
  // указанием «номера SIM-карты», тарифа, года выпуска;
  void Operator::find_sims(wstring pattern) {
    // Метод поиска SIM-карты по тарифу определяется студентом самостоятельно.
    // Выбранный метод необходимо сравнить с альтернативными методами.
  }

  // Регистрацию выдачи клиенту SIM-карты;
  void Operator::registration_sim(string passport_number, string sim_number) {
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
  void Operator::remove_registration_sim(string passport_number,
                                         string sim_number) {
    // При регистрации выдачи SIM-карты клиенту или возврата SIM-карты клиентом
    // должно корректироваться значение поля «Признак наличия» для
    // соответствующей SIM-карты.
  }
