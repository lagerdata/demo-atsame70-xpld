include(../cmake/utils.cmake)

add_executable(app "")
target_sources(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main.c)


set(MCHP_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../mchp_sdk)
target_sources(app PRIVATE ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/gcc/system_same70q21b.c
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/gcc/gcc/startup_same70q21b.c)


target_include_directories(app PRIVATE ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include/pio
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include/component
  ${MCHP_SRC_DIR}/CMSIS/Core/Include)


target_link_libraries(app ledctrl)
target_link_libraries(app ticks)

target_compile_options(app PRIVATE -mcpu=cortex-m7 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv5-sp-d16)
target_compile_options(app PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(app PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(app PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(app PRIVATE $<$<COMPILE_LANGUAGE:C>:__SAME70Q21__ DEBUG>)

target_link_directories(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../linker)
target_link_options(app PRIVATE -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 --entry=Reset_Handler -Wl,--gc-sections -Wl,--start-group -lgcc -lc -lm -Wl,--end-group --specs=nano.specs -Tatsame70q21b_flash.ld)


firmware_size(app)
generate_object(app .bin binary)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    generate_object(app .hex ihex)
endif()
