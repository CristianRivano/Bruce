#ifndef __BLE_MENU_H__
#define __BLE_MENU_H__

#include <MenuItemInterface.h>


class BleMenu : public MenuItemInterface {
public:
    BleMenu() : MenuItemInterface("Bluetooth") {}

    void optionsMenu(void);
    void drawIcon(float scale);
};

#endif
