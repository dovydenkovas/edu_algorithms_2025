#include "application.h"
#include "../entities.h"
#include "../input.hpp"
#include "../validators.h"
#include <cstdlib>
#include <exception>
#include <string>

TuiApplication::TuiApplication(Operator *op, UIForms *forms)
    : op{op}, forms{forms} {}

void TuiApplication::exec() {
  while (true) {
    size_t action = input(labels::main_menu_actions, labels::out_of_range_error,
                          in_range<1, 15>) -
                    1;
    main_menu_run[action](op);
  }
}

void add_user(Operator *op) {
  using std::wstring;
  wstring name = input_line(labels::add_user_input_name,
                            labels::add_user_input_name_error, is_valid_name);
  uint16_t birth_year =
      input(labels::add_user_input_year, labels::add_user_input_year_error,
            is_valid_birth_year);
  wstring address = input_line<wstring>(labels::add_user_input_address,
                                        labels::add_user_input_address_error);
  wstring passport_number = input(labels::add_user_input_passport_number,
                                  labels::add_user_input_passport_number_error,
                                  is_valid_passport_number);
  wstring passport_date = input_line<wstring>(
      labels::input_passport_date_of_issue, labels::default_error);

  try {
    op->add_user(
        User(name, birth_year, address, passport_number, passport_date));
  } catch (Error &e) {
    wcout << labels::user_exist << endl;
  }
}

void del_user(Operator *op) {
  wstring passport_number = input(labels::add_user_input_passport_number,
                                  labels::add_user_input_passport_number_error,
                                  is_valid_passport_number);
  try {
    op->remove_user(passport_number);
  } catch (Error &e) {
    wcout << labels::user_not_exist << endl;
  }
}

void show_users(Operator *op) { op->show_all_users(); }

void clear_users(Operator *op) {
  wstring yes_no =
      input(labels::are_you_sure, labels::are_you_sure_error, is_valid_yes_no);
  if (is_yes(yes_no))
    op->remove_all_users();
}

void search_user(Operator *op) {
  std::wstring pattern =
      input_line<std::wstring>(labels::search_user, labels::default_error);
  op->find_users(pattern);
}

void add_sim(Operator *op) {
  wstring number =
      input(labels::add_sim_input_number, labels::add_sim_input_number_error,
            is_valid_sim_number);
  wstring tariff =
      input_line<wstring>(labels::add_sim_input_tariff, labels::default_error);
  uint16_t issue_year =
      input(labels::add_sim_input_year, labels::add_sim_input_year_error,
            is_valid_issue_year);
  bool is_exist = false;

  try {
    op->add_sim(Sim(number, tariff, issue_year, is_exist));
  } catch (Error &e) {
    wcout << labels::sim_exist << endl;
  }
}

void del_sim(Operator *op) {
  wstring number =
      input(labels::add_sim_input_number, labels::add_sim_input_number_error,
            is_valid_sim_number);
  try {
    op->remove_sim(number);
  } catch (Error &e) {
    wcout << labels::sim_not_exist << endl;
  }
}

void show_sims(Operator *op) { op->show_all_sim(); }

void search_sim_by_number(Operator *op) {
  wstring number =
      input(labels::add_sim_input_number, labels::add_sim_input_number_error,
            is_valid_sim_number);
  op->find_sim(number);
}

void search_sim_by_tarif(Operator *op) {
  wstring tariff =
      input_line<wstring>(labels::add_sim_input_tariff, labels::default_error);
  op->find_sims(tariff);
}

void reg_user_sim(Operator *op) {
  wstring sim_number =
      input(labels::add_sim_input_number, labels::add_sim_input_number_error,
            is_valid_sim_number);
  wstring passport_number = input(labels::add_user_input_passport_number,
                                  labels::add_user_input_passport_number_error,
                                  is_valid_passport_number);
  try {
    op->registration_sim(passport_number, sim_number);
  } catch (Error &e) {
    switch (e) {
    case Error::UserNotExist:
      wcout << labels::user_not_exist << endl;
      break;
    case Error::SimNotExist:
      wcout << labels::sim_not_exist << endl;
      break;
    case Error::UserExist:
    case Error::SimExist:
      break;
    }
  }
}

void del_user_sim(Operator *op) {
  wstring sim_number =
      input(labels::add_sim_input_number, labels::add_sim_input_number_error,
            is_valid_sim_number);
  wstring passport_number = input(labels::add_user_input_passport_number,
                                  labels::add_user_input_passport_number_error,
                                  is_valid_passport_number);
  try {
    op->remove_registration_sim(passport_number, sim_number);
  } catch (Error &e) {
    switch (e) {
    case Error::UserNotExist:
      wcout << labels::user_not_exist << endl;
      break;
    case Error::SimNotExist:
      wcout << labels::sim_not_exist << endl;
      break;
    case Error::UserExist:
    case Error::SimExist:
      break;
    }
  }
}


void open_database(Operator *op) {
  wstring filename = input(labels::filename_to_open, labels::open_file_error, is_valid_filename);
  try {
    op->open(filename);
  } catch (exception &e) {
    std::wcout << labels::open_file_error << std::endl;
  }
}

void save_database(Operator *op) {
  wstring filename = input(labels::filename_to_save, labels::open_file_error, is_valid_filename);
  try {
    op->save(filename);
  } catch (exception &e) {
    std::wcout << labels::open_file_error << std::endl;
  }
}

void exit_op(Operator *op) {
  wstring need_save = input(labels::need_save, labels::enter_yes_or_no, is_valid_yes_no);
  if (is_yes(need_save))
    save_database(op);
  exit(0);
}
