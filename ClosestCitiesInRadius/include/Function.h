#pragma once
#include "Location.h"
#include "Exception.h"
#include <functional>

using FunctionPtr = std::function < double (const Location&, const Location&) >;
using FuncMap = std::map< int, FunctionPtr>;

FunctionPtr getFunction(const char c);