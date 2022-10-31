//
// Created by Админ on 29.10.2022.
//

#ifndef PROJECT1_MAIN_CH_H
#define PROJECT1_MAIN_CH_H
#include "Windows.h"
#include "memory_controller.h"
#include <string>
#include <iostream>
#include "offsets.hpp"

struct Vec3 {
    float x, y, z;

    Vec3 operator+(Vec3 d) {
        return {x + d.x, y + d.y, z + d.z};
    }

    Vec3 operator-(Vec3 d) {
        return {x - d.x, y - d.y, z - d.z};
    }

    Vec3 operator*(Vec3 d) {
        return {x * d.x, y * d.y, z * d.z};
    }
    void Normalize() {
        while (y < -180) {
            y += 360;
        }
        while (y > 180) {
            y -= 360;
        }
        if (x > 89) {
            x = 89;
        }
        if (x < -89) {
            x = -89;
        }
    }
};

class main_ch {
public:


    bool bunny_hop = false;
    bool trigger_bot = false;
    bool radar_hack = false;
    bool anti_flash = false;
    bool chams = false;
    bool RCS = false;
    //bool anti_aim = false;

    memory_controller m;
    const CHAR *name;


    DWORD client;
    DWORD engine;
    Vec3 RCS_control{0, 2, 2};
    Vec3 oPunch{0, 0, 0};
    main_ch();
    main_ch(const CHAR* name);
    ~main_ch();
    void print_cheat_menu();
    void set();
    void radarhack();
    void set_chams(DWORD entity, int r, int g, int b);
    void chams_func();
    void antiflash();
    void triggerbot();
    void bunnyhop();
    void recoil_control_system();
    void reset_chams();
    void printEntityList();
    void antiaim();
};


#endif //PROJECT1_MAIN_CH_H
