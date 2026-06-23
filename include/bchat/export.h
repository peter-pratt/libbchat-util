#pragma once

#if defined(_WIN32) || defined(WIN32)
#define LIBBCHAT_EXPORT __declspec(dllexport)
#else
#define LIBBCHAT_EXPORT __attribute__((visibility("default")))
#endif
#define LIBBCHAT_C_API extern "C" LIBBCHAT_EXPORT

#ifdef __GNUC__
#define LIBBCHAT_WARN_UNUSED __attribute__((warn_unused_result))
#else
#define LIBBCHAT_WARN_UNUSED
#endif