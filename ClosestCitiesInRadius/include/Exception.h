#pragma once
#include "Utilities.h"

class FileError : public std::exception
{
public:
    FileError(const char* str) : m_str(str) {}

    const char* what() const noexcept { return m_str; }

private:
    const char* m_str;
    string m_string;
};
//------------------------------
class InputError : public std::exception
{
public:
    InputError(const char* str = "Invalid input") : m_str(str) {}

    const char* what() const noexcept { return m_str; }

private:
    const char* m_str;
    string m_string;
};
//--------------------------------------
