# Specify programmer
set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER stk500)
set(AVR_UPLOADTOOL_PORT /dev/ttyACM0)

# Specify CPU
set(AVR_MCU atmega328p)

# Specify fuse magic
set(AVR_H_FUSE 0xD9)
set(AVR_L_FUSE 0xE2)

# Specify CPU frequency
set(MCU_SPEED "8000000ULL")

# Include avg-gcc toolchain
include(generic-gcc-avr)
INCLUDE_DIRECTORIES(${AVR_SYSTEM_INCLUDE_PATH})

# Typical options
add_definitions("-DF_CPU=${MCU_SPEED}")
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
add_definitions("-Werror")
#add_definitions("-pedantic")
#add_definitions("-pedantic-errors")
#add_definitions("-funsigned-char")
#add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-Wl,--relax")
add_definitions("-c")
add_definitions("-std=gnu99")
add_definitions("-O1")

set(AVR_UPLOADTOOL_OPTIONS "")

##########################################################################
# Firmware source
##########################################################################
set(firmware_SOURCES main.c rot.c lcd.c trx.c menu.c display.c
	keyer.c tone.c i2c.c si5351.c band.c meter.c)
set(firmware_HEADERS
	keyer.h tone.h rot.h i2c.h si5351.h band.h meter.h lcd.h trx.h menu.h display.h)

# !!! UGLY HACK TO GET RID OF "-rdynamic" flags. !!!
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# compile & link
add_avr_executable(firmware ${firmware_SOURCES})
avr_target_link_libraries(firmware ${AVR_C_LIB})


