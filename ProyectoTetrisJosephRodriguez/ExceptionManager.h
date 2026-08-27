#pragma once

#include <exception>
#include <string>

class ExceptionManager : public std::exception {
public:
    enum Type { TextureLoad, FontLoad, FileLoad };
    ExceptionManager(Type t, const std::string& detail = "");
    const char* what() const throw() override;
private:
    std::string message;
};
