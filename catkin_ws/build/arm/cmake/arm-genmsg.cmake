# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "arm: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iarm:/home/kamerider/catkin_ws/src/arm/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(arm_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/kamerider/catkin_ws/src/arm/msg/pos.msg" NAME_WE)
add_custom_target(_arm_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arm" "/home/kamerider/catkin_ws/src/arm/msg/pos.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(arm
  "/home/kamerider/catkin_ws/src/arm/msg/pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arm
)

### Generating Services

### Generating Module File
_generate_module_cpp(arm
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arm
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(arm_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(arm_generate_messages arm_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kamerider/catkin_ws/src/arm/msg/pos.msg" NAME_WE)
add_dependencies(arm_generate_messages_cpp _arm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arm_gencpp)
add_dependencies(arm_gencpp arm_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arm_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(arm
  "/home/kamerider/catkin_ws/src/arm/msg/pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arm
)

### Generating Services

### Generating Module File
_generate_module_lisp(arm
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arm
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(arm_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(arm_generate_messages arm_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kamerider/catkin_ws/src/arm/msg/pos.msg" NAME_WE)
add_dependencies(arm_generate_messages_lisp _arm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arm_genlisp)
add_dependencies(arm_genlisp arm_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arm_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(arm
  "/home/kamerider/catkin_ws/src/arm/msg/pos.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arm
)

### Generating Services

### Generating Module File
_generate_module_py(arm
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arm
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(arm_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(arm_generate_messages arm_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/kamerider/catkin_ws/src/arm/msg/pos.msg" NAME_WE)
add_dependencies(arm_generate_messages_py _arm_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arm_genpy)
add_dependencies(arm_genpy arm_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arm_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arm
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(arm_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arm)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arm
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(arm_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arm)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arm\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arm
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(arm_generate_messages_py std_msgs_generate_messages_py)
endif()
