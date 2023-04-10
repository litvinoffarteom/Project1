//
// Created by Админ on 17.11.2022.
//

#ifndef MY_SDK_CONFIG_H
#define MY_SDK_CONFIG_H
#include "colors.h"
#include <iostream>
#include <fstream>

struct config {
    bool bunny_hop = false;
    bool trigger_bot = false;
    bool radar_hack = false;
    bool anti_flash = false;
    bool chams = false;
    bool RCS = false;
    bool wall_hack = false;
    bool auto_pistol = false;
    bool console = false;
    bool close = false;
    bool fake = false;

    bool health_based_glow = true;
    bool teammates = false;
    bool legit_trigger_bot = false;
    bool legit_bunny_hop = false;
    bool anti_flash_delay = false;
    color3_t chams_enemy = color3_t{255, 0 , 0};
    color3_t chams_teammates = color3_t{0, 255 , 0};
};

#endif //MY_SDK_CONFIG_H
