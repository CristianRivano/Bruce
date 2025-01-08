#include "RFMenu.h"
#include "core/display.h"
#include "core/settings.h"
#include "modules/rf/rf.h"
#include "core/utils.h"

void RFMenu::optionsMenu() {
    options = {
        {"Escanear/Copiar",       [=]() { rf_scan_copy(); }},
        {"Custom SubGhz",   [=]() { otherRFcodes(); }},
        {"Espectro",        [=]() { rf_spectrum(); }}, //@IncursioHack
        {"Onda Cuadrada", [=]() { rf_SquareWave(); }}, //@Pirata
        {"Jammer Intermitente",     [=]() { rf_jammerIntermittent(); }}, //@IncursioHack
        {"Jammer Full",     [=]() { rf_jammerFull(); }}, //@IncursioHack
        {"Configurar",          [=]() { configMenu(); }},
        {"Volver",       [=]() { backToMenu(); }},
    };

    delay(200);
    String txt = "Radio Frequencia";
    if(bruceConfig.rfModule==CC1101_SPI_MODULE) txt+=" (CC1101)"; // Indicates if CC1101 is connected
    else txt+=" Tx: " + String(bruceConfig.rfTx) + " Rx: " + String(bruceConfig.rfRx);

    loopOptions(options,false,true,txt);
}

void RFMenu::configMenu() {
    options = {
        {"RF TX Pin",     [=]() { gsetRfTxPin(true); }},
        {"RF RX Pin",     [=]() { gsetRfRxPin(true); }},
        {"Módulo RF",     [=]() { setRFModuleMenu(); }},
        {"Frequencia RF",  [=]() { setRFFreqMenu();   }},
        {"Volver",          [=]() { optionsMenu(); }},
    };

    delay(200);
    loopOptions(options,false,true,"RF Config");
}

void RFMenu::drawIcon(float scale) {
    clearIconArea();

    int radius = scale * 7;
    int deltaRadius = scale * 10;
    int triangleSize = scale * 30;

    if (triangleSize % 2 != 0) triangleSize++;

    // Body
    tft.fillCircle(iconCenterX, iconCenterY - radius, radius, bruceConfig.priColor);
    tft.fillTriangle(
        iconCenterX, iconCenterY,
        iconCenterX - triangleSize/2, iconCenterY + triangleSize,
        iconCenterX + triangleSize/2, iconCenterY + triangleSize,
        bruceConfig.priColor
    );

    // Left Arcs
    tft.drawArc(
        iconCenterX, iconCenterY - radius,
        2.5*radius, 2*radius,
        40, 140,
        bruceConfig.priColor, bruceConfig.bgColor
    );
    tft.drawArc(
        iconCenterX, iconCenterY - radius,
        2.5*radius + deltaRadius, 2*radius + deltaRadius,
        40, 140,
        bruceConfig.priColor, bruceConfig.bgColor
    );
    tft.drawArc(
        iconCenterX, iconCenterY - radius,
        2.5*radius + 2*deltaRadius, 2*radius + 2*deltaRadius,
        40, 140,
        bruceConfig.priColor, bruceConfig.bgColor
    );

    // Right Arcs
    tft.drawArc(
        iconCenterX, iconCenterY - radius,
        2.5*radius, 2*radius,
        220, 320,
        bruceConfig.priColor, bruceConfig.bgColor
    );
    tft.drawArc(
        iconCenterX, iconCenterY - radius,
        2.5*radius + deltaRadius, 2*radius + deltaRadius,
        220, 320,
        bruceConfig.priColor, bruceConfig.bgColor
    );
    tft.drawArc(
        iconCenterX, iconCenterY - radius,
        2.5*radius + 2*deltaRadius, 2*radius + 2*deltaRadius,
        220, 320,
        bruceConfig.priColor, bruceConfig.bgColor
    );
}
