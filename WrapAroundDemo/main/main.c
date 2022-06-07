#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "sh1107.h"
//#include "font8x8_basic.h"

#define tag "SH1107"

void app_main(void)
{
	SH1107_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(tag, "INTERFACE is i2c");
	ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_I2C_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_I2C_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(tag, "INTERFACE is SPI");
	ESP_LOGI(tag, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(tag, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(tag, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(tag, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_SPI_RESET_GPIO);
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_SPI_RESET_GPIO);
#endif
	sh1107_init(&dev, 64, 128);
	sh1107_contrast(&dev, 0xff);
	sh1107_direction(&dev, DIRECTION0);
	
	sh1107_clear_screen(&dev, false);
	sh1107_display_text(&dev, 0, 0, "M5 Stick", 8, false);
	sh1107_display_text(&dev, 1, 0, "64x128  ", 8, false);
	sh1107_display_text(&dev, 2, 0, "ABCDEFGH", 8, false);
	sh1107_display_text(&dev, 3, 0, "abcdefgh", 8, false);
	sh1107_display_text(&dev, 4, 0, "01234567", 8, false);
	sh1107_display_text(&dev, 5, 0, "Hello   ", 8, false);
	sh1107_display_text(&dev, 6, 0, "World!! ", 8, false);

	sh1107_display_text(&dev, 8, 0, "M5 Stick", 8, true);
	sh1107_display_text(&dev, 9, 0, "64x128  ", 8, true);
	sh1107_display_text(&dev, 10, 0, "ABCDEFGH", 8, true);
	sh1107_display_text(&dev, 11, 0, "abcdefgh", 8, true);
	sh1107_display_text(&dev, 12, 0, "01234567", 8, true);
	sh1107_display_text(&dev, 13, 0, "Hello   ", 8, true);
	sh1107_display_text(&dev, 14, 0, "World!! ", 8, true);

	vTaskDelay(3000 / portTICK_PERIOD_MS);
	while(1) {
		for(int i=0;i<64;i++) {
			sh1107_wrap_arround(&dev, SCROLL_RIGHT, 1, 2, 0);
			sh1107_wrap_arround(&dev, SCROLL_RIGHT, 5, 6, 0);
			sh1107_wrap_arround(&dev, SCROLL_RIGHT, 9, 10, 0);
			sh1107_wrap_arround(&dev, SCROLL_RIGHT, 13, 14, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		for(int i=0;i<64;i++) {
			sh1107_wrap_arround(&dev, SCROLL_LEFT, 1, 2, 0);
			sh1107_wrap_arround(&dev, SCROLL_LEFT, 5, 6, 0);
			sh1107_wrap_arround(&dev, SCROLL_LEFT, 9, 10, 0);
			sh1107_wrap_arround(&dev, SCROLL_LEFT, 13, 14, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		for(int i=0;i<128;i++) {
			sh1107_wrap_arround(&dev, SCROLL_UP, 0, 15, 0);
			sh1107_wrap_arround(&dev, SCROLL_UP, 48, 63, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		for(int i=0;i<128;i++) {
			sh1107_wrap_arround(&dev, SCROLL_DOWN, 0, 15, 0);
			sh1107_wrap_arround(&dev, SCROLL_DOWN, 48, 63, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		for(int i=0;i<64;i++) {
			sh1107_wrap_arround(&dev, SCROLL_RIGHT, 0, 15, 0);
			sh1107_wrap_arround(&dev, SCROLL_DOWN, 0, 63, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	} // end while
}
