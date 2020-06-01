# Introduction

This project demonstrates how to use the Arduino Over The Air update system on an ESP32.
Click the image to watch the demo video.

[![Demo Video](https://img.youtube.com/vi/_bMsrxiyuHs/0.jpg)](https://www.youtube.com/watch?v=_bMsrxiyuHs)

# Setup

Update the file `wifi_credentials.h` with your SSID and PASSWORD.

```c
#define SSID "YOUR_SSID"
#define PASSWORD "YOUR_PASSWORD"
```

Now just compile and run the sketch.

The first install will need to over USB.

Once the sketch is running you can go to "Tools" -> "Ports" and you should find your ESP32 listed as "esp_test".

You can change the name of your device by changing this line of code:

```c
ArduinoOTA.setHostname("esp_test");
```
