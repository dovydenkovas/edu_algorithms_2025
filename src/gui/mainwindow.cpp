#include "mainwindow.h"
#include "../input.hpp"

GuiMainWindow::GuiMainWindow(Operator *op, UIForms *forms)
    : op{op}, forms{forms} {}

void GuiMainWindow::exec() {
  while (true) {
    size_t action = input<size_t>(labels::main_menu_actions,
                                  labels::prompt_on_error, in_range<1, 12>) - 1;
    main_menu_run[action]();
  }
}

void add_user() {}
void del_user() {}
void show_users() {}
void clear_users() {}
void search_user() {}
void add_sim() {}
void del_sim() {}
void show_sims() {}
void search_sim_by_number() {}
void search_sim_by_tarif() {}
void reg_user_sim() {}
void del_user_sim() {}
