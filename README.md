# React on an ESP32

This sample project demonstrates how to run a React application on an ESP32 micro-controller.
You can view the recording [here](https://youtu.be/R9n32nxrzug)

## Software prerequisites

You will need to install

- [node](https://nodejs.org/) v14 or later
- The ESP-IDF. You can follow [these instructions](https://learnesp32.com/videos/1/0_introduction)

## Hardware to run demo

- an esp32 dev board such as this one [from AliExpress](https://www.aliexpress.com/item/1005001636295529.html?spm=a2g0o.productlist.0.0.58dd798bIY78Qo&algo_pvid=65cfe33f-c51c-4b4d-ba3c-ae136ffd9404&algo_exp_id=65cfe33f-c51c-4b4d-ba3c-ae136ffd9404-1&pdp_ext_f=%7B%22sku_id%22%3A%2212000016916866581%22%7D&pdp_npi=1%40dis%7CAUD%7C%7C5.73%7C%7C%7C5.24%7C%7C%402101e9d416511158324635217eb8f5%7C12000016916866581%7Csea) or this one [form Amazon](https://www.amazon.com/Development-Microcontroller-Integrated-Antenna-Amplifiers/dp/B09GK74F7N/ref=sr_1_6?crid=3K9XNPGUIELBE&keywords=ESP32&qid=1651116139&sprefix=%2Caps%2C1739&sr=8-6)
- A button
- A small servo motor like [this one](https://www.aliexpress.com/item/4001149590522.html?spm=a2g0o.productlist.0.0.f0ce6b49UUGEKu&algo_pvid=18a7e06f-56eb-4a3c-97f7-d6ad54aa8088&algo_exp_id=18a7e06f-56eb-4a3c-97f7-d6ad54aa8088-2&pdp_ext_f=%7B%22sku_id%22%3A%2210000014899518043%22%7D&pdp_npi=1%40dis%7CAUD%7C%7C2.22%7C%7C%7C1.54%7C%7C%400bb0624216511161950402704e8446%7C10000014899518043%7Csea)
- A magnet

## instructions

If you are unfamiliar with running IDF commands please visit the [Learn ESP32](https://learnesp32.com) and follow the first few free modules

1. clone the repo `git clone`
1. open ./main/main.c
   at the top of the file, set your WiFi SSID and passphrase by changing these lines

```c
static const char *SSID = "MY WIFI SSID";
static const char *PASS = "MY WIFI PASS";
```

⚠️warning: Both SSID and passphrase are case sensitive

2. build the React application

```bash
cd site
npm run build
```

3. (optional) run the web dev server

```bash
npm run dev
```

4. Open an IDF shell to ensure your IDF environment is loaded and then in the project root run

```bash
idf.py flash monitor
```

5. make sure your PC is on the same WiFi that you are using
6. in your browser navigate to http://my-esp32.local
7. (optional) If you are running a dev server you can also navigate to http://localhost:3000
