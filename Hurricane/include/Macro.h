#ifndef MACRO_H
#define MACRO_H

#include "PCH.h"

#define BIT(x) (1 << x)

#define SAFE_DELETE(ptr) { if(ptr) { delete ptr;} ptr = nullptr; }

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

#ifdef DEBUG
#define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
#define ASSERT(x, ...) { if(!(x)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CORE_ASSERT(x, ...) { if(!(x)) { CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ASSERT(x, ...)
#define CORE_ASSERT(x, ...)
#endif

#endif MACRO_H