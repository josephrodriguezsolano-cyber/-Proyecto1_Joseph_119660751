#pragma once

#include <exception>
#include <string>

using namespace std;

class ExceptionManager : public exception {
public:
    enum Type { TextureLoad, FontLoad, FileLoad };
    ExceptionManager(Type t, const string& detail = "");
    const char* what() const throw() override;
private:
    string message;
};
