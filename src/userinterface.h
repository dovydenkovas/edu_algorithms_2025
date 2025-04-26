#pragma once

class Operator;

class UserInterface {
  Operator *op;
public:
  UserInterface(Operator *op);
};


class Table {
  Operator *op;
public:
  Table();
};


class Forms {
  Operator *op;
public:
  Forms();
};
