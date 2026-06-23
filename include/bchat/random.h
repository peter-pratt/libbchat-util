#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "export.h"

/// API: crypto/bchat_random
///
/// Wrapper around the randombytes_buf function.
///
/// Inputs:
/// - `size` -- [in] number of bytes to be generated.
///
/// Outputs:
/// - `unsigned char*` -- pointer to random bytes of `size` bytes.  The caller is responsible for
/// freeing the data when done!
LIBBCHAT_EXPORT unsigned char* bchat_random(size_t size);

#ifdef __cplusplus
}
#endif