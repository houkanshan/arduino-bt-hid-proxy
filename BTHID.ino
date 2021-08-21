#include <BTHID.h>
#include <usbhub.h>
#include "KeyboardParser.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
// USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the class in two ways */
// This will start an inquiry and then pair with your device - you only have to do this once
// If you are using a Bluetooth keyboard, then you should type in the password on the keypad and then press enter

BTHID bthid(&Btd, PAIR, "0000");

// After that you can simply create the instance like so and then press any button on the device
// BTHID bthid(&Btd);

KbdRptParser keyboardPrs;

void setup() {
  Serial.begin(115200);
  TXLED1;

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    TXLED0;
    while (1); // Halt
  }

  bthid.SetReportParser(KEYBOARD_PARSER_ID, &keyboardPrs);

  // If "Boot Protocol Mode" does not work, then try "Report Protocol Mode"
  // If that does not work either, then uncomment PRINTREPORT in BTHID.cpp to see the raw report
  // bthid.setProtocolMode(USB_HID_BOOT_PROTOCOL); // Boot Protocol Mode
  bthid.setProtocolMode(HID_RPT_PROTOCOL); // Report Protocol Mode

  Serial.print(F("\r\nHID Bluetooth Library Started"));
  TXLED1;
}
void loop() {
  Usb.Task();
}
