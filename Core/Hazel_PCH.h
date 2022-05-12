#pragma once

#ifdef ISDLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif // ISDLL

#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;