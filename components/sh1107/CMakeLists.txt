set(component_srcs "sh1107.c" "sh1107_i2c.c" "sh1107_spi.c")

idf_component_register(SRCS "${component_srcs}"
                       PRIV_REQUIRES driver
                       INCLUDE_DIRS ".")
