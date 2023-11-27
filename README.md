# esp-idf-sh1107
sh1107 Driver for esp-idf

I used [this](https://github.com/dhepper/font8x8) font file.   

# Software requirements
ESP-IDF V4.4/V5.x.   

__Note for ESP32C2.__   
ESP-IDF V5.0 ESP32C2 i2c driver has a bug.   
ESP-IDF V5.1 is required when using i2c of ESP32C2.   

__Note for ESP32C6.__   
ESP-IDF V5.1 is required when using ESP32C6.   

# Installation

```
git clone https://github.com/nopnop2002/esp-idf-sh1107
cd esp-idf-sh1107/TextDemo/
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```


# Configuration   
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

# M5Stick
![config_spi](https://user-images.githubusercontent.com/6020549/103494674-327e1600-4e7b-11eb-9e63-786536862ac0.jpg)
![M5Stick-1](https://user-images.githubusercontent.com/6020549/103348592-d1062200-4add-11eb-8429-7c94f62cd38d.JPG)
![M5Stick-2](https://user-images.githubusercontent.com/6020549/103348595-d2374f00-4add-11eb-919f-f0d64f5a5003.JPG)
![M5Stick-3](https://user-images.githubusercontent.com/6020549/103348596-d2cfe580-4add-11eb-8fe7-2cf9f1d79406.JPG)
![M5Stick-4](https://user-images.githubusercontent.com/6020549/103348598-d4011280-4add-11eb-910b-9c47d61a7db3.JPG)

---

# Generic 64x128 SPI
![config_spi](https://user-images.githubusercontent.com/6020549/103494674-327e1600-4e7b-11eb-9e63-786536862ac0.jpg)
![spi-1](https://user-images.githubusercontent.com/6020549/138789782-6c7904d3-c25e-48f7-aaaa-fec98cf07dce.JPG)
![spi-2](https://user-images.githubusercontent.com/6020549/138789787-dca0f931-8106-4ce8-92bb-b87e01927cc2.JPG)

Wirering

|sh1107||ESP32|ESP32-S2/S3|ESP32-C2/C3/C6|
|:-:|:-:|:-:|:-:|:-:|
|CS|--|GPIO14|GPIO34|GPIO3|
|DC|--|GPIO27|GPIO37|GPIO2|
|RESET|--|GPIO33|GPIO33|GPI10|
|MOSI|--|GPIO23|GPIO35|GPIO0|
|SCLK|--|GPIO18|GPIO36|GPIO1|
|GND|--|GND|GND|GND|
|VCC|--|3.3V|3.3V|3.3V|

__You can change it to any pin using menuconfig.__   

__Note__   
For some reason, there are development boards that cannot use GPIO06, GPIO08, GPIO09, GPIO19 for SPI clock pins.   
According to the ESP32C3 specifications, these pins can also be used as SPI clocks.   
I used a raw ESP-C3-13 to verify that these pins could be used as SPI clocks.   


---

# Generic 64x128 i2c

![config_i2c](https://user-images.githubusercontent.com/6020549/103494667-301bbc00-4e7b-11eb-8314-c4e8944fca0d.jpg)
![i2c-1](https://user-images.githubusercontent.com/6020549/103496654-6577d800-4e82-11eb-9d7f-c0b6af226bee.JPG)
![i2c-2](https://user-images.githubusercontent.com/6020549/103496656-67419b80-4e82-11eb-88e9-640c6cba9769.JPG)
![i2c-3](https://user-images.githubusercontent.com/6020549/103496658-690b5f00-4e82-11eb-96a0-0499a840f9b1.JPG)
![i2c-4](https://user-images.githubusercontent.com/6020549/103496662-6ad52280-4e82-11eb-9177-335eed508e26.JPG)

Wirering

|sh1107||ESP32|ESP32-S2/S3|ESP32-C2/C3/C6|
|:-:|:-:|:-:|:-:|:-:|
|SCL|--|GPIO22|GPIO12|GPIO6|
|SDA|--|GPIO21|GPIO11|GPIO5|
|GND|--|GND|GND|GND|
|VCC|--|3.3V|3.3V|3.3V|

__You can change it to any pin using menuconfig.__   

