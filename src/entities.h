#pragma once

#include <cstdint>
#include <string>

using namespace std;

class Client {
  string passport_number;
  wstring name;
  uint16_t birth_year;
  wstring address;
  wstring passport_date_of_issue;

public:
  Client(wstring name, uint16_t birth_year, wstring address, string passport_number);
  wstring get_name() const { return address; }
  uint16_t get_birth_year() const { return birth_year; }
  wstring get_address() const { return address; }
  string get_passport_number() const { return passport_number; }
  wstring get_passport_date_of_issue() const { return passport_date_of_issue; }
};

class Sim {
  string number;
  wstring tariff;
  uint16_t issue_year;
  bool is_exist;

public:
  Sim(string number, wstring tariff, uint16_t issue_year, bool is_exist);
  string get_number() const { return number; }
  wstring get_tariff() const { return tariff; }
  uint16_t get_issue_year() const { return issue_year; }
  bool exist() const { return is_exist; }
};

class SimRegistation {
  string sim_number; // Первычиный ключ
  string passport_number;
  wstring registration_date;
  wstring expiration_date;

public:
  SimRegistation(string sim_number, string passport_number,
                 wstring registration_date, wstring expiration_date);
  string get_sim_number() const { return sim_number; }
  string get_passport_number() const { return passport_number; }
  wstring get_registration_date() const { return registration_date; }
  wstring get_expiration_date() const { return expiration_date; }
};
