#ifndef __CLOCK_MENU_H__
#define __CLOCK_MENU_H__

#include <MenuItemInterface.h>


class ClockMenu : public MenuItemInterface {
public:
    ClockMenu() : MenuItemInterface("Reloj") {}

    void optionsMenu(void);
    void drawIcon(float scale);
};

#endif
