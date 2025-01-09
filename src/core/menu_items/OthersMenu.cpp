#include "OthersMenu.h"
#include "core/display.h"
#include "core/sd_functions.h"
#include "modules/others/openhaystack.h"
#include "modules/others/tururururu.h"
#include "modules/others/webInterface.h"
#include "modules/others/qrcode_menu.h"
#include "modules/others/mic.h"
#include "modules/bjs_interpreter/interpreter.h"
#include "modules/others/timer.h"
#include "core/utils.h"

#include "modules/others/bad_usb.h"
#ifdef HAS_RGB_LED
#include "modules/others/led_control.h"
#endif

void OthersMenu::optionsMenu() {
    options = {
        {"MicroSD",      [=]() { loopSD(SD); }},
        {"LittleFS",     [=]() { loopSD(LittleFS); }},
        {"WebUI",        [=]() { loopOptionsWebUi(); }},
        {"QR",      [=]() { qrcode_menu(); }},
        {"Megalodon",    [=]() { shark_setup(); }},
    #ifdef MIC_SPM1423
        {"Espectro de micrófono", [=]() { mic_test(); }},
    #endif
        {"BadUSB",       [=]() { usb_setup(); }},
    #ifdef HAS_KEYBOARD_HID
        {"Teclado USB", [=]() { usb_keyboard(); }},
    #endif
    #ifdef HAS_RGB_LED
        {"Control de LED",  [=]()  { ledColorConfig(); }},
        {"Brillo del LED", [=]() { ledBrightnessConfig(); }},
    #endif
    #ifndef LITE_VERSION
        {"Openhaystack", [=]() { openhaystack_setup(); }},
    #endif
    #if !defined(ARDUINO_M5STACK_ARDUINO_M5STACK_CORE) && !defined(ARDUINO_M5STACK_ARDUINO_M5STACK_CORE2)
        {"Interprete", [=]()  { run_bjs_script(); }},
    #endif
        {"Timer",        [=]() { Timer(); }},
        {"Volver",    [=]() { backToMenu(); }},
    };

    delay(200);
    loopOptions(options,false,true,"Otros");
}

void OthersMenu::drawIcon(float scale) {
    clearIconArea();

    int radius = scale * 7;

    tft.fillCircle(iconCenterX, iconCenterY, radius, bruceConfig.priColor);

    tft.drawArc(
        iconCenterX, iconCenterY,
        2.5*radius, 2*radius,
        0, 340,
        bruceConfig.priColor, bruceConfig.bgColor
    );
    tft.drawArc(
        iconCenterX, iconCenterY,
        3.5*radius, 3*radius,
        20, 360,
        bruceConfig.priColor, bruceConfig.bgColor
    );
    tft.drawArc(
        iconCenterX, iconCenterY,
        4.5*radius, 4*radius,
        0, 200,
        bruceConfig.priColor, bruceConfig.bgColor
    );
    tft.drawArc(
        iconCenterX, iconCenterY,
        4.5*radius, 4*radius,
        240, 360,
        bruceConfig.priColor, bruceConfig.bgColor
    );
}