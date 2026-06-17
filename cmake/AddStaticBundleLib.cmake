
set(LIBBCHAT_STATIC_BUNDLE_LIBS "" CACHE INTERNAL "list of libs to go into the static bundle lib")

function(_libbchat_static_bundle_append tgt)
    list(APPEND LIBBCHAT_STATIC_BUNDLE_LIBS "${tgt}")
    set(LIBBCHAT_STATIC_BUNDLE_LIBS "${LIBBCHAT_STATIC_BUNDLE_LIBS}" CACHE INTERNAL "")
endfunction()

# Call as:
#
#     libbchat_static_bundle(target [target2 ...])
#
# to append the given target(s) to the list of libraries that will be combined to make the static
# bundled libbchat-util.a.
function(libbchat_static_bundle)
    foreach(tgt IN LISTS ARGN)
        if(TARGET "${tgt}" AND NOT "${tgt}" IN_LIST LIBBCHAT_STATIC_BUNDLE_LIBS)
            get_target_property(tgt_type ${tgt} TYPE)

            if(tgt_type STREQUAL STATIC_LIBRARY)
                message(STATUS "Adding ${tgt} to libbchat-util bundled library list")
                _libbchat_static_bundle_append("${tgt}")
            endif()

            if(tgt_type STREQUAL INTERFACE_LIBRARY)
                get_target_property(tgt_link_deps ${tgt} INTERFACE_LINK_LIBRARIES)
            else()
                get_target_property(tgt_link_deps ${tgt} LINK_LIBRARIES)
            endif()

            if(tgt_link_deps)
                libbchat_static_bundle(${tgt_link_deps})
            endif()
        endif()
    endforeach()
endfunction()