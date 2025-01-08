#include "ConfigMenu.h"
#include "core/utils.h"
#include "core/display.h"
#include "core/settings.h"
#include "core/i2c_finder.h"
#include "core/wifi_common.h"

void ConfigMenu::optionsMenu() {
    options = {
        {"Brillo",    [=]() { setBrightnessMenu(); }},
        {"Tiempo apagado",      [=]() { setDimmerTimeMenu(); }},
        {"Orientación",   [=]() { gsetRotation(true); }},
        {"Color",      [=]() { setUIColor(); }},
        {"Sonido",  [=]() { setSoundConfig(); }},
        {"Iniciar WiFi",  [=]() { setWifiStartupConfig(); }},
        {"Iniciar App",   [=]() { setStartupApp(); }},
        {"Reloj",         [=]() { setClock(); }},
        {"Dormir",         [=]() { setSleepMode(); }},
        {"Reiniciar",       [=]() { ESP.restart(); }},
    };

  #if defined(T_EMBED_1101)
    options.push_back({"Turn-off",  [=]() { digitalWrite(PIN_POWER_ON,LOW); esp_sleep_enable_ext0_wakeup(GPIO_NUM_6,LOW); esp_deep_sleep_start(); }});
  #endif
    if (bruceConfig.devMode) options.push_back({"Dev Mode", [=]() { devMenu(); }});

    options.push_back({"Volver", [=]() { backToMenu(); }});

    delay(200);
    loopOptions(options,false,true,"Configurar");
}

void ConfigMenu::devMenu(){
    options = {
        {"Device Info",   [=]() { showDeviceInfo(); }},
        {"MAC Address",   [=]() { checkMAC(); }},
        {"I2C Finder",    [=]() { find_i2c_addresses(); }},
        {"Atrás",          [=]() { optionsMenu(); }},
    };

    delay(200);
    loopOptions(options,false,true,"Dev Mode");
}

void ConfigMenu::drawIcon(float scale) {
    clearIconArea();

    int radius = scale * 9;

    int i=0;
    for(i=0; i<6; i++) {
        tft.drawArc(
            iconCenterX,
            iconCenterY,
            3.5*radius, 2*radius,
            15+60*i, 45+60*i,
            bruceConfig.priColor,
            bruceConfig.bgColor,
            true
        );
    }

    tft.drawArc(
        iconCenterX,
        iconCenterY,
        2.5*radius, radius,
        0, 360,
        bruceConfig.priColor,
        bruceConfig.bgColor,
        false
    );
}