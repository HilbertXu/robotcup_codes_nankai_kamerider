# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "rbx2_msgs: 0 messages, 1 services")

set(MSG_I_FLAGS "")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(rbx2_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv" NAME_WE)
add_custom_target(_rbx2_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "rbx2_msgs" "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(rbx2_msgs
  "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rbx2_msgs
)

### Generating Module File
_generate_module_cpp(rbx2_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rbx2_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(rbx2_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(rbx2_msgs_generate_messages rbx2_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv" NAME_WE)
add_dependencies(rbx2_msgs_generate_messages_cpp _rbx2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rbx2_msgs_gencpp)
add_dependencies(rbx2_msgs_gencpp rbx2_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rbx2_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(rbx2_msgs
  "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rbx2_msgs
)

### Generating Module File
_generate_module_lisp(rbx2_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rbx2_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(rbx2_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(rbx2_msgs_generate_messages rbx2_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv" NAME_WE)
add_dependencies(rbx2_msgs_generate_messages_lisp _rbx2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rbx2_msgs_genlisp)
add_dependencies(rbx2_msgs_genlisp rbx2_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rbx2_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(rbx2_msgs
  "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rbx2_msgs
)

### Generating Module File
_generate_module_py(rbx2_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rbx2_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(rbx2_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(rbx2_msgs_generate_messages rbx2_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kamerider/catkin_ws/src/rbx2/rbx2_msgs/srv/SetBatteryLevel.srv" NAME_WE)
add_dependencies(rbx2_msgs_generate_messages_py _rbx2_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rbx2_msgs_genpy)
add_dependencies(rbx2_msgs_genpy rbx2_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rbx2_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rbx2_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rbx2_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rbx2_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rbx2_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rbx2_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rbx2_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rbx2_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
