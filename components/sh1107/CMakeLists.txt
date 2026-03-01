set(component_srcs "sh1107.c" "sh1107_new_i2c.c" "sh1107_spi.c")

idf_component_register(
	SRCS "${component_srcs}"
	PRIV_REQUIRES driver esp_driver_i2c esp_driver_spi esp_driver_gpio
	INCLUDE_DIRS "."
)
