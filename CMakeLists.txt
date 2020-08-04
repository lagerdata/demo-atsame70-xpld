include(../cmake/utils.cmake)

add_executable(unity-atsame70 "")
target_sources(unity-atsame70 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/main.c
  ${CMAKE_CURRENT_LIST_DIR}/src/test1.c
  ${CMAKE_CURRENT_LIST_DIR}/unity_uart_atsame70/same70_target_uart.c
  ${CMAKE_CURRENT_LIST_DIR}/../Unity/src/unity.c)

target_include_directories(unity-atsame70 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/unity_uart_atsame70
  ${CMAKE_CURRENT_LIST_DIR}/unity_cfg
  ${CMAKE_CURRENT_LIST_DIR}/../Unity/src)

set(MCHP_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/mchp_sdk)
target_sources(unity-atsame70 PRIVATE ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/gcc/system_same70q21b.c
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/gcc/gcc/startup_same70q21b.c)


target_include_directories(unity-atsame70 PRIVATE ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include/pio
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include/component
  ${MCHP_SRC_DIR}/CMSIS/Core/Include)



target_compile_options(unity-atsame70 PRIVATE -mcpu=cortex-m7 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv5-sp-d16)
target_compile_options(unity-atsame70 PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(unity-atsame70 PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(unity-atsame70 PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(unity-atsame70 PRIVATE $<$<COMPILE_LANGUAGE:C>:__SAME70Q21__ DEBUG UNITY_INCLUDE_CONFIG_H>)

target_link_directories(unity-atsame70 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/linker)
target_link_options(unity-atsame70 PRIVATE -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 --entry=Reset_Handler -Wl,--gc-sections -Wl,--start-group -lgcc -lc -lm -Wl,--end-group --specs=nano.specs -Tunity-atsame70q21b_flash.ld)


firmware_size(unity-atsame70)
generate_object(unity-atsame70 .bin binary)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    generate_object(unity-atsame70 .hex ihex)
endif()
