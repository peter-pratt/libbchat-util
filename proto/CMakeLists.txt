
libbchat_static_bundle(protobuf::libprotobuf-lite)


add_library(protos
    SessionProtos.pb.cc
    WebSocketResources.pb.cc)
target_include_directories(protos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(protos PUBLIC protobuf::libprotobuf-lite)
set_target_properties(
    protos PROPERTIES
    OUTPUT_NAME bchat-protos
    SOVERSION ${LIBBCHAT_LIBVERSION})

# -Wunused-parameter triggers in the protobuf dependency
message(STATUS "Disabling -Werror for proto unused-parameter")

if (MSVC)
else()
    target_compile_options(protos PUBLIC -Wno-error=unused-parameter)
endif()

libbchat_static_bundle(protos)

add_library(libbchat::protos ALIAS protos)
export(
    TARGETS protos
    NAMESPACE libbchat::
    FILE libbchatTargets.cmake
)
list(APPEND libbchat_export_targets protos)
set(libbchat_export_targets "${libbchat_export_targets}" PARENT_SCOPE)


add_custom_target(regen-protobuf
    protoc --cpp_out=. SessionProtos.proto WebSocketResources.proto
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
