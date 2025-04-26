#include "operator.h"
#include "gui/table.h"
#include "gui/forms.h"
#include "gui/mainwindow.h"


int main() {
  GuiTable *table = new GuiTable;
  GuiForms *forms = new GuiForms;
  Operator op(table, forms);
  GuiMainWindow main_window(&op);
}
