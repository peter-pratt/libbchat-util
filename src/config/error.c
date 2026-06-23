#include "bchat/config/error.h"

const char* config_errstr(int err) {
    switch (err) {
        case BCHAT_ERR_INVALID_DUMP: return "Dumped data is invalid";
        case BCHAT_ERR_BAD_VALUE: return "Invalid value";
    }
    return "Unknown error";
}
