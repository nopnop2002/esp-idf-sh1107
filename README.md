# esp-idf-sh1107
sh1107 Driver for esp-idf

I used [this](https://github.com/dhepper/font8x8) font file.   

# Installation for ESP32(M5Stick)

```
git clone https://github.com/nopnop2002/esp-idf-sh1107
cd esp-idf-sh1107/
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2

```
git clone https://github.com/nopnop2002/esp-idf-sh1107
cd esp-idf-sh1107/
idf.py set-target esp32s2
idf.py menuconfig
idf.py flash
```

You have to set this config value with menuconfig.   
- CONFIG_INTERFACE   
- CONFIG_SDA_GPIO   
- CONFIG_SCL_GPIO   
- CONFIG_RESET_GPIO   
- CONFIG_MOSI_GPIO   
- CONFIG_SCLK_GPIO   
- CONFIG_CS_GPIO   
- CONFIG_DC_GPIO   

![config_menu](https://user-images.githubusercontent.com/6020549/103494664-2d20cb80-4e7b-11eb-8b87-8ed63cb5c60b.jpg)

---

# M5Stick/Generic 64x128 SPI
![config_spi](https://user-images.githubusercontent.com/6020549/103494674-327e1600-4e7b-11eb-9e63-786536862ac0.jpg)
![M5Stick-1](https://user-images.githubusercontent.com/6020549/103348592-d1062200-4add-11eb-8429-7c94f62cd38d.JPG)
![M5Stick-2](https://user-images.githubusercontent.com/6020549/103348595-d2374f00-4add-11eb-919f-f0d64f5a5003.JPG)
![M5Stick-3](https://user-images.githubusercontent.com/6020549/103348596-d2cfe580-4add-11eb-8fe7-2cf9f1d79406.JPG)
![M5Stick-4](https://user-images.githubusercontent.com/6020549/103348598-d4011280-4add-11eb-910b-9c47d61a7db3.JPG)

---

# Generic 64x128 i2c

![config_i2c](https://user-images.githubusercontent.com/6020549/103494667-301bbc00-4e7b-11eb-8314-c4e8944fca0d.jpg)
![i2c-1](https://user-images.githubusercontent.com/6020549/103494864-e97a9180-4e7b-11eb-92e8-369b0d8aaa0b.JPG)
![i2c-2](https://user-images.githubusercontent.com/6020549/103494866-eda6af00-4e7b-11eb-9dc2-93937f50ccf0.JPG)
![i2c-3](https://user-images.githubusercontent.com/6020549/103494869-f0a19f80-4e7b-11eb-9ee3-4de6e0da576d.JPG)
![i2c-4](https://user-images.githubusercontent.com/6020549/103494871-f26b6300-4e7b-11eb-9368-d190ccab340b.JPG)

