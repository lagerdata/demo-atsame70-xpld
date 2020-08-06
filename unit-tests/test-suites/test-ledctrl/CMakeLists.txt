include(../../../cmake/utils.cmake)

add_executable(test-ledctrl "")
target_sources(test-ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main_ledctrl.c
  ${CMAKE_CURRENT_LIST_DIR}/test_ledctrl.c)
target_include_directories(test-ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR})

set(UNITY_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Unity/src)
target_sources(test-ledctrl PRIVATE ${UNITY_SRC_DIR}/unity.c)
target_include_directories(test-ledctrl PRIVATE ${UNITY_SRC_DIR})

set(UART_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../../)
target_sources(test-ledctrl PRIVATE ${UART_SRC_DIR}/same70_target_uart.c)
target_include_directories(test-ledctrl PRIVATE ${UART_SRC_DIR})

set(MCHP_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../mchp_sdk)
target_sources(test-ledctrl PRIVATE ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/gcc/system_same70q21b.c
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/gcc/gcc/startup_same70q21b.c)

target_include_directories(test-ledctrl PRIVATE ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include/pio
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include/component
  ${MCHP_SRC_DIR}/CMSIS/Core/Include)

target_link_libraries(test-ledctrl ledctrl)
target_link_libraries(test-ledctrl ticks)

target_compile_options(test-ledctrl PRIVATE -mcpu=cortex-m7 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv5-sp-d16)
target_compile_options(test-ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(test-ledctrl PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(test-ledctrl PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(test-ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:__SAME70Q21__ DEBUG UNITY_INCLUDE_CONFIG_H>)

target_link_libraries(test-ledctrl ledctrl)


target_link_directories(test-ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../../linker)
target_link_options(test-ledctrl PRIVATE -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 --entry=Reset_Handler -Wl,--gc-sections -Wl,--start-group -lgcc -lc -lm -Wl,--end-group --specs=nano.specs -Tatsame70q21b_flash.ld)


firmware_size(test-ledctrl)
generate_object(test-ledctrl .bin binary)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    generate_object(test-ledctrl .hex ihex)
endif()
