#pragma once

#include <cstdint>
#include <string>

using namespace std;

enum class Error {
  UserExist,
  UserNotExist,
  SimExist,
  SimNotExist,
};

class User {
  wstring passport_number;
  wstring name;
  uint16_t birth_year;
  wstring address;
  wstring passport_date_of_issue;

public:
  User(wstring name, uint16_t birth_year, wstring address,
         wstring passport_number, wstring passport_date_of_issue)
      : passport_number(passport_number), name(name), birth_year(birth_year),
        address(address), passport_date_of_issue(passport_date_of_issue) {}
  wstring get_name() const { return name; }
  uint16_t get_birth_year() const { return birth_year; }
  wstring get_address() const { return address; }
  wstring get_passport_number() const { return passport_number; }
  wstring get_passport_date_of_issue() const { return passport_date_of_issue; }
};

class Sim {
  wstring number;
  wstring tariff;
  uint16_t issue_year;
  bool is_sim_free;

public:
  Sim(wstring number, wstring tariff, uint16_t issue_year, bool is_free)
      : number(number), tariff(tariff), issue_year(issue_year),
        is_sim_free(is_free) {}
  wstring get_number() const { return number; }
  wstring get_tariff() const { return tariff; }
  uint16_t get_issue_year() const { return issue_year; }
  bool is_free() const { return is_sim_free; }
  void free(bool i) { is_sim_free = i; }
};

class SimRegistation {
  wstring sim_number;
  wstring passport_number;
  wstring registration_date;
  wstring expiration_date;

public:
  SimRegistation(wstring sim_number, wstring passport_number,
                 wstring registration_date, wstring expiration_date)
      : sim_number(sim_number), passport_number(passport_number),
        registration_date(registration_date), expiration_date(expiration_date) {
  }
  wstring get_sim_number() const { return sim_number; }
  wstring get_passport_number() const { return passport_number; }
  wstring get_registration_date() const { return registration_date; }
  wstring get_expiration_date() const { return expiration_date; }
};
