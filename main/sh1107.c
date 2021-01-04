#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "sh1107.h"
#include "font8x8_basic.h"

#define TAG "SH1107"

void sh1107_init(SH1107_t * dev, int width, int height)
{
	if (dev->_address == SPIAddress) {
		spi_init(dev, width, height);
	} else {
		i2c_init(dev, width, height);
	}
}

void sh1107_display_text(SH1107_t * dev, int row, int col, char * text, int text_len, bool invert)
{
	int _length = text_len;
	int _width = 0;
	int _height = 0;
	int _row = 0;
	int _col = 0;
	int _rowadd = 0;
	int _coladd = 0;
	if (dev->_direction == DIRECTION0) {
		_width = dev->_width / 8;
		_height = dev->_height / 8;
		_row = row;
		_col = col*8;
		_rowadd = 0;
		_coladd = 8;
	} else if (dev->_direction == DIRECTION90) {
		_width = dev->_height / 8;
		_height = dev->_width / 8;
		_row = col;
		_col = (dev->_width-8) - (row*8);
		_rowadd = 1;
		_coladd = 0;
	} else if (dev->_direction == DIRECTION180) {
		_width = dev->_width / 8;
		_height = dev->_height / 8;
		_row = _height - row - 1;
		_col = (dev->_width-8) - (col*8);
		_rowadd = 0;
		_coladd = -8;
	} else if (dev->_direction == DIRECTION270) {
		_width = dev->_height / 8;
		_height = dev->_width / 8;
		_row = (dev->_pages-1) - col;
		_col = row*8;
		_rowadd = -1;
		_coladd = 0;
	}
	if (row >= _height) return;
	if (col >= _width) return;
	if (col + text_len > _width) _length = _width - col;
	ESP_LOGD(TAG, "_direction=%d _width=%d _height=%d _length=%d _row=%d _col=%d", 
		dev->_direction, _width, _height, _length, _row, _col);

	void (*func)(SH1107_t * dev, int page, int seg, uint8_t * images, int width);
	if (dev->_address == SPIAddress) {
		func = spi_display_image;
	} else {
		func = i2c_display_image;
	}

	uint8_t image[8];
	for (int i=0; i<_length; i++) {
		memcpy(image, font8x8_basic_tr[(uint8_t)text[i]], 8);
		if (invert) sh1107_invert(image, 8);
		sh1107_rotate(image, dev->_direction);
		//spi_display_image(dev, _row, _col, image, 8);
		(*func)(dev, _row, _col, image, 8);
		_row = _row + _rowadd;
		_col = _col + _coladd;
	}
}

void sh1107_display_image(SH1107_t * dev, int page, int col, uint8_t * images, int width)
{
	if (dev->_address == SPIAddress) {
		spi_display_image(dev, page, col, images, width);
	} else {
		i2c_display_image(dev, page, col, images, width);
	}
}

void sh1107_clear_screen(SH1107_t * dev, bool invert)
{
	uint8_t zero[64];
	if (invert) {
		memset(zero, 0xff, sizeof(zero));
	} else {
		memset(zero, 0x00, sizeof(zero));
	}
	for (int page = 0; page < dev->_pages; page++) {
		if (dev->_address == SPIAddress) {
			spi_display_image(dev, page, 0, zero, dev->_width);
		} else {
			i2c_display_image(dev, page, 0, zero, dev->_width);
		}
	}
}

void sh1107_clear_line(SH1107_t * dev, int row, bool invert)
{
	char space[1];
	space[0] = 0x20;
	if (dev->_direction == DIRECTION0 || dev->_direction == DIRECTION90) {
		int _width = dev->_width / 8;
		for (int col=0;col<_width;col++) {
			sh1107_display_text(dev, row, col, space, 1, invert);
		}
	} else {
		int _width = dev->_height / 8;
		for (int col=0;col<_width;col++) {
			sh1107_display_text(dev, row, col, space, 1, invert);
		}
	}
}

void sh1107_contrast(SH1107_t * dev, int contrast)
{
	if (dev->_address == SPIAddress) {
		spi_contrast(dev, contrast);
	} else {
		i2c_contrast(dev, contrast);
	}
#if 0
	int _contrast = contrast;
	if (contrast < 0x0) _contrast = 0;
	if (contrast > 0xFF) _contrast = 0xFF;

	spi_master_write_command(dev, 0x81);
	spi_master_write_command(dev, _contrast);
#endif
}

void sh1107_invert(uint8_t *buf, size_t blen)
{
	uint8_t wk;
	for(int i=0; i<blen; i++){
		wk = buf[i];
		buf[i] = ~wk;
	}
}


void sh1107_fadeout(SH1107_t * dev)
{
	void (*func)(SH1107_t * dev, int page, int seg, uint8_t * images, int width);
	if (dev->_address == SPIAddress) {
		func = spi_display_image;
	} else {
		func = i2c_display_image;
	}

	uint8_t image[1];
	for(int page=0; page<dev->_pages; page++) {
		image[0] = 0xFF;
		for(int line=0; line<8; line++) {
			image[0] = image[0] << 1;
			for(int seg=0; seg<dev->_width; seg++) {
				//sh1107_display_image(dev, page, seg, image, 1);
				(*func)(dev, page, seg, image, 1);
			}
		}
	}
}

void sh1107_direction(SH1107_t * dev, int dir)
{
	dev->_direction = dir;
}

uint8_t rotate_byte(uint8_t ch1) {
	uint8_t ch2 = 0;
	for (int j=0;j<8;j++) {
		ch2 = (ch2 << 1) + (ch1 & 0x01);
		ch1 = ch1 >> 1;
	}
	return ch2;
}

void sh1107_rotate(uint8_t * buf, int dir)
{
	uint8_t wk[8];
	if (dir == DIRECTION0) return;
	for(int i=0; i<8; i++){
		wk[i] = buf[i];
		buf[i] = 0;
	}
	if (dir == DIRECTION90 || dir == DIRECTION270) {
		uint8_t wk2[8];
		uint8_t mask1 = 0x80;
		for(int i=0;i<8;i++) {
			wk2[i] = 0;
			ESP_LOGD(TAG, "wk[%d]=%x", i, wk[i]);
			uint8_t mask2 = 0x01;
			for(int j=0;j<8;j++) {
				if( (wk[j] & mask1) == mask1) wk2[i] = wk2[i] + mask2;
				mask2 = mask2 << 1;
			}
			mask1 = mask1 >> 1;
		}
		for(int i=0; i<8; i++){
			ESP_LOGD(TAG, "wk2[%d]=%x", i, wk2[i]);
		}

		for(int i=0;i<8;i++) {
			if (dir == DIRECTION90) {
				buf[i] = wk2[i];
			} else {
				buf[i] = rotate_byte(wk2[7-i]);
			}
		}
	} else if (dir == DIRECTION180) {
		for(int i=0;i<8;i++) {
			buf[i] = rotate_byte(wk[7-i]);
		}

	}
	return;

}

