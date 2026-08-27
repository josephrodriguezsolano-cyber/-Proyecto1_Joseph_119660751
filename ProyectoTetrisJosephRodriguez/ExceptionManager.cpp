#include "ExceptionManager.h"

ExceptionManager::ExceptionManager(Type t, const std::string& detail) {
    if (t == TextureLoad) {
        message = "Failed to load texture: " + detail;
    }
    else if (t == FontLoad) {
        message = "Failed to load font: " + detail;
    }
    else if (t == FileLoad) {
        message = "Failed to open file: " + detail;
    }
    else {
        message = "Unknown error";
    }
}

const char* ExceptionManager::what() const throw() {
    return message.c_str();
}
