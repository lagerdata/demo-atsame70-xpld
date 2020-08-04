add_library (ledctrl STATIC "")
target_sources(ledctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ledctrl.c)
target_include_directories(ledctrl PUBLIC ${CMAKE_CURRENT_LIST_DIR}/)

set(MCHP_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../mchp_sdk)
target_include_directories(ledctrl PRIVATE ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include
  ${MCHP_SRC_DIR}/microchip/SAME70_DFP/4.3.67/same70b/include/component
  ${MCHP_SRC_DIR}/CMSIS/Core/Include)

target_compile_options(ledctrl PRIVATE -mcpu=cortex-m7 -mthumb -mabi=aapcs -mfloat-abi=hard -mfpu=fpv5-sp-d16)
target_compile_options(ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall -Werror -g -gstrict-dwarf -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin -fshort-enums>)
target_compile_options(ledctrl PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>)
target_compile_options(ledctrl PUBLIC "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=.")
target_compile_definitions(ledctrl PRIVATE $<$<COMPILE_LANGUAGE:C>:__SAME70Q21__ DEBUG>)
