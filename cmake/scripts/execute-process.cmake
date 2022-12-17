if(SEQUENTIAL)
  string(
    REPLACE "\\ "
            ":::"
            COMMANDS
            ${COMMANDS})
  string(
    REPLACE " "
            ";"
            COMMANDS
            ${COMMANDS})
  foreach(command IN LISTS COMMANDS)
    if(command STREQUAL "")
      continue()
    endif()
    string(
      REPLACE ":::"
              ";"
              command
              ${command})
    execute_process(
      COMMAND ${command}
      WORKING_DIRECTORY ${WORKING_DIRECTORY}
      RESULT_VARIABLE
        result
        COMMAND_ECHO
        STDOUT
        ECHO_OUTPUT_VARIABLE
        ECHO_ERROR_VARIABLE
        COMMAND_ERROR_IS_FATAL
        ANY)
  endforeach()
else()
  string(
    REPLACE "\\ "
            ":::"
            COMMANDS
            ${COMMANDS})
  string(
    REPLACE " "
            " COMMAND "
            COMMANDS
            ${COMMANDS})
  string(PREPEND COMMANDS "COMMAND ")
  string(
    REGEX
    REPLACE "( |:::)"
            ";"
            COMMANDS
            ${COMMANDS})
  execute_process(
    ${COMMANDS}
    WORKING_DIRECTORY ${WORKING_DIRECTORY}
    RESULT_VARIABLE
      result
      COMMAND_ECHO
      STDOUT
      ECHO_OUTPUT_VARIABLE
      ECHO_ERROR_VARIABLE
      COMMAND_ERROR_IS_FATAL
      ANY)
endif()
