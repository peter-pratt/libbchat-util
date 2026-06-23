# BChat utility library

## Build

```
# Configure the build
#
# Options
#   Enable APIs for creating onion-requests with:
#
#     -D ENABLE_ONIONERQ
#
#   Enable testing of a BChat Pro Backend by defining on the configure line:
#
#     -D TEST_PRO_BACKEND_WITH_DEV_SERVER=1
#
#   These tests require the BChat Pro Backend running in development mode (SESH_PRO_BACKEND_DEV=1)
#   to be running and tests the request and response flow of registering, updating and revoking
#   BChat Pro from the development backend. You must also have a libcurl available such that
#   `find_package(CURL)` succeeds (e.g. a system installed libcurl) for this to compile
#   successfully.
#
#   By default, it contacts http://127.0.0.1:5000 but this URL can be changed using the CLI arg
#   --pro-backend-dev-server-url="<url>" when invoking the test suite.
#
cmake -G Ninja -S . -B Build

# Regenerate protobuf files
cmake --build Build --target regen-protobuf --parallel --verbose

# Build
cmake --build Build --parallel --verbose
```

## Docs

C Library: https://api.oxen.io/libbchat-util-c/#/

C++ Library: https://api.oxen.io/libbchat-util-cpp/#/
