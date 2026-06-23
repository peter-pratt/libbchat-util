#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../export.h"

enum config_error {
    /// Value returned for no error
    BCHAT_ERR_NONE = 0,
    /// Error indicating that initialization failed because the dumped data being loaded is invalid.
    BCHAT_ERR_INVALID_DUMP = 1,
    /// Error indicated a bad value, e.g. if trying to set something invalid in a config field.
    BCHAT_ERR_BAD_VALUE = 2,
};

/// API: error/config_errstr
///
/// Returns a generic string for a given integer error code as returned by some functions. Depending
/// on the call, a more details error string may be available in the config_object's `last_error`
/// field.
///
/// Declaration:
/// ```cpp
/// CONST CHAR* config_errstr(
///     [in]    int     err
/// );
/// ```
///
/// Inputs:
/// - `err` -- [in] Integer of the error code
///
/// Outputs:
/// - `const char*` -- text of the error string
LIBBCHAT_EXPORT const char* config_errstr(int err);

#ifdef __cplusplus
}  // extern "C"
#endif
