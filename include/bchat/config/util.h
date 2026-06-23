#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "../export.h"

/// API: util/bchat_id_is_valid
///
/// Returns true if bchat_id has the right form (66 hex digits).  This is a quick check, not a
/// robust one: it does not check the leading byte prefix, nor the cryptographic properties of the
/// pubkey for actual validity.
///
/// Declaration:
/// ```cpp
/// BOOL bchat_id_is_valid(
///     [in]    const char*     bchat_id
/// );
/// ```
///
/// Inputs:
/// - `bchat_id` -- [in] hex string of the bchat id
///
/// Outputs:
/// - `bool` -- Returns true if the bchat id has the right form
LIBBCHAT_EXPORT bool bchat_id_is_valid(const char* bchat_id);

#ifdef __cplusplus
}
#endif
