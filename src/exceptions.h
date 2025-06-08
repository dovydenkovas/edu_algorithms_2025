#include "entities.h"
#include <string>

class InfoException {
public:
  virtual std::wstring what() = 0;
};

class UserNotExist: public InfoException {
  public:
    std::wstring what() override {return L"Пользователь не найден.";}
};

class UserExist: public InfoException {
  public:
    std::wstring what() override {return L"Пользователь с указанным паспортом уже существует.";}
};

class SimNotExist: public InfoException {
  public:
    std::wstring what() override {return L"SIM-карта не найдена.";}
};

class SimExist: public InfoException {
  public:
    std::wstring what() override {return L"SIM-карта уже существует.";}
};

class SimRegistationExist: public InfoException {
  public:
    std::wstring what() override {return L"SIM-карта уже выдана.";}
};

class SimRegistationNotExist: public InfoException {
  public:
    std::wstring what() override {return L"SIM-карта не была выдана.";}
};

class ParseUser: public InfoException {
  public:
    std::wstring what() override {return L"Ошибка при чтении данных пользователя.";}
};

class ParseSim: public InfoException {
  public:
    std::wstring what() override {return L"Ошибка при чтении данных SIM-карты.";}
};

class ParseReg: public InfoException {
  public:
    std::wstring what() override {return L"Ошибка при чтении данных выдачи карты.";}
};

class ParseError: public InfoException {
  public:
    std::wstring what() override {return L"Запись не принадлежит секции";}
};
