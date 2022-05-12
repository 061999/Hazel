#pragma once

#ifdef ISDLL
#define HAZEL_API __declspec(export)
#else
#define HAZEL_API __declspec(import)
#endif // ISDLL

