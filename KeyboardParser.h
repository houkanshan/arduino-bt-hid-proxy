#ifndef __kbdrptparser_h_
#define __kbdrptparser_h_

#include <Arduino.h>
#include "KeyboardReporter.h"

// comment if you're not using apple magic keyboard.
#define APPLE_MAGIC_KBD


class KbdRptParser : public HIDReportParser
{
public:
    virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

bool ledOn = false;

void KbdRptParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
#ifdef APPLE_MAGIC_KBD
    // for apple magic keyboard, should also send report id (one byte before current *buf).
    buf -= 1;
    len += 1;
#endif

    for (int i = 0; i < len; i ++) {
      Serial.print(buf[i]);
      Serial.print(" ");
    }
    Serial.print("\r\n");

    ledOn = !ledOn;
    if (ledOn) TXLED1;
    else TXLED0;

    KeyboardReporter.sendReport(buf, len);
};


#endif
