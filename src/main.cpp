#include "operator.h"
#include "gui/table.h"
#include "gui/forms.h"
#include "gui/mainwindow.h"
#include "userinterface.h"


int main() {
  std::setlocale(LC_ALL, "");
  UITable *table = new GuiTable;
  UIForms *forms = new GuiForms;

  Operator op(table, forms);
  GuiMainWindow main_window(&op, forms);
  main_window.exec();

  delete forms;
  delete table;
}
