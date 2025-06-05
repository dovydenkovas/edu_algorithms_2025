#include "operator.h"
#include "tui/table.h"
#include "tui/forms.h"
#include "tui/application.h"
#include "userinterface.h"


int main() {
  std::setlocale(LC_ALL, "");
  UITable *table = new TuiTable;
  UIForms *forms = new TuiForms;

  Operator op(table, forms);
  TuiApplication app(&op, forms);
  app.exec();

  delete forms;
  delete table;
}
