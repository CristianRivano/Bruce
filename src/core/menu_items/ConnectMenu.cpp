
#include "ConnectMenu.h"
#include "core/display.h"
#include "core/settings.h"
#include "core/connect.h"
#include "core/wifi_common.h"
#include "core/utils.h"


void ConnectMenu::optionsMenu() {
    options = {
        {"Enviar Archivo",    [=]() { DeviceConnection().sendFile(); }},
        {"Recibir archivo", [=]() { DeviceConnection().receiveFile(); }},
        {"Volver",    [=]() { backToMenu(); }},
    };

    delay(200);
    loopOptions(options,false,true,getName());
}

void ConnectMenu::drawIcon(float scale) {
    clearIconArea();

    int iconW = scale * 50;
    int iconH = scale * 40;
    int radius = scale * 7;

    if (iconW % 2 != 0) iconW++;
    if (iconH % 2 != 0) iconH++;

    tft.fillCircle(iconCenterX - iconW/2, iconCenterY, radius, bruceConfig.priColor);

    tft.fillCircle(iconCenterX + 0.3*iconW, iconCenterY - iconH/2, radius, bruceConfig.priColor);
    tft.fillCircle(iconCenterX + 0.5*iconW, iconCenterY, radius, bruceConfig.priColor);
    tft.fillCircle(iconCenterX + 0.3*iconW, iconCenterY + iconH/2, radius, bruceConfig.priColor);

    tft.drawLine(
        iconCenterX - iconW/2, iconCenterY,
        iconCenterX + 0.3*iconW, iconCenterY - iconH/2,
        bruceConfig.priColor
    );
    tft.drawLine(
        iconCenterX - iconW/2, iconCenterY,
        iconCenterX + 0.5*iconW, iconCenterY,
        bruceConfig.priColor
    );
    tft.drawLine(
        iconCenterX - iconW/2, iconCenterY,
        iconCenterX + 0.3*iconW, iconCenterY + iconH/2,
        bruceConfig.priColor
    );
}