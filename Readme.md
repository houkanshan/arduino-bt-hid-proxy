# Arduino Bluetooth HID Proxy

Bridge Bluetooth keyboard to wired USB. (i.e. Bluetooth HID Proxy Mode).
Works like a Logitech Unifying Receiver but for bluetooth devices.

<p>
<img src="https://user-images.githubusercontent.com/657962/130332810-a0201244-cdbd-44db-a61c-58a0c20e44aa.png" width="500" />

<sup>(Image idea from pihidproxy)</sup>
</p>

> [!NOTE]
> If you are looking for a project that turns a wired keyboard into a wireless keyboard. 
This is not the right project. This project does the reverse.

It can be useful in two scenarios:

1. You have a bluetooth keyboard, but it doesn't work in BIOS, Bootloader or TV.
2. You have a bluetooth keyboard and you want turn it into a programmable keyboard (with [TMK USB to USB Converter](https://geekhack.org/index.php?topic=69169.0))

Previously, I used MikerR's [pihidproxy](https://github.com/mikerr/pihidproxy) but it's not transparency enough and I don't like the start-up time of RPi.
So I made this one with Arduino.

# Guide

## Hardware

### Shopping List
  - [SparkFun Micro Pro 3.3V](https://www.sparkfun.com/products/12587) (Other ATmega32U4 based board should also work)
  - [USB Host Shield for Arduino Pro Mini](https://shop.tkjelectronics.dk/product_info.php?products_id=45) 
    (Out of stock due to COVID, 
    I'm using [this](https://www.amazon.com/HiLetgo-Development-Compatible-Interface-Arduino/dp/B01EWW9R1E) cheaper clone)
  - USB Bluetooth dongle 
    (should [supported](https://github.com/felis/USB_Host_Shield_2.0/wiki/Bluetooth-dongles) by USB Host Library 2.0, 
    I've tested [this](https://www.amazon.com/gp/product/B07G9TSDCG/) and [this](https://www.amazon.com/gp/product/B007MKMJGO/))
  - a Micro-USB to USB Cable, Soldering Iron Kit, Electronic Wire, Male Header Pin

### Assembling

Follow [this guide](https://geekhack.org/index.php?topic=80421.0) to connect Micro Pro and USB Host Shield. Or tl;dr:
  1. Cut the line between VBUS and 2k2 to get 5.0V
  2. Two Jump wires on VCC and RST, VBUS and RAW
  3. Put Micro Pro on USB Host shield, align, and connect: (Top) INT, GND, (Bottom) SS, MOSI, MISO, SCK, VCC, GND, RAW

## Programming

> [!NOTE]
> if you are NOT using an Apple Magic Keyboard, make sure to finish step 5

1. Open in Arduino IDE
2. In `Tools -> Manage Libraries`, search and install `USB Host Shield Library 2.0`, `HID-Project`
3. Let's test if USB Host shield is working: `File -> Examples -> USB Host Shield Library 2.0 -> board_qc`
    1. Upload
    2. `Tools -> Serial Monitor`
    3. There'll be a GPIO error, ignore it and send any key in the serial monitor.
    4. Wait until `All tests passed.`
    5. [This article](https://joshcaplin.wordpress.com/tag/board_qc/) could be helpful if you meet any issue.
4. `git clone https://github.com/houkanshan/arduino-bt-hid-proxy.git`
5. In `KeyboardParser.h`, comment `#define APPLE_MAGIC_KBD` (adding `//` to the beginning) if you're not using an Apple Magic Keyboard.

## Uploading for the first pairing

1. Upload the project, open `Tools -> Serial Monitor`
2. Turn on your bluetooth device and start pairing
3. Wait for bluetooth scanning
4. Follow the guide in the Serial Monitor and finish the pairing
5. Now the paired address is remembered by arduino.

## Uploading for paired

The current code will try to re-pair every time after power on. Let's stop it.

1. In `BTHID.ino`, comment `BTHID bthid(&Btd, PAIR, "0000");` and uncomment `BTHID bthid(&Btd);`
2. Upload
3. Press any button on the device, then it should be connected.

## Debug

### USB Host Library

1. In `Documents/Arduino/libraries/USB_Host_Shield_2.0/settings.h`, change `#define ENABLE_UHS_DEBUGGING 0` to `1`.
  It will display detailed log in serial monitor
2. For more detailed log, uncomment `#define EXTRADEBUG` in `*.cpp` file you want to inspect.

# Thanks to

- [mikerr/pihidproxy](https://github.com/mikerr/pihidproxy)
- [felis/USB_Host_Shield_2.0](https://github.com/felis/USB_Host_Shield_2.0)
- [NicoHood/HID](https://github.com/NicoHood/HID)
- [TMK USB to USB Converter](https://geekhack.org/index.php?topic=69169.0)
- [usb_usb converter and Apple Magic keyboard](https://github.com/tmk/tmk_keyboard/issues/606)
