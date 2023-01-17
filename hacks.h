#ifndef PROJECT1_HACKS_H
#define PROJECT1_HACKS_H

#include <thread>
#include "memory_controller.h"
#include "offsets.hpp"
#include <chrono>
#include <cmath>
#include "vector.h"
#include "config.h"
#include <iostream>
#include <vector>

namespace v {
    inline std::pair<bool, std::array<float, 4U>> my_team_glow{
            false,
            {0.f, 1.f, 0.f, 1.f}
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_100{
            false,
            {1.f, 0.f, 0.f, 1.f}
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_75{
            false,
            {1.f, 0.f, 1.f, 1.f}
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_50{
            false,
            {0.5f, 0.f, 1.f, 1.f}
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_25{
            false,
            {0.f, 0.f, 1.f, 1.f}
    };
    inline std::pair<bool, std::array<float, 4U>> other_team_glow_scoped{
            false,
            {1.f, 1.f, 1.f, 1.f}
    };
}
template<typename T>
struct color4_t {
    constexpr color4_t(const std::array<T, 4U> &arr) noexcept:
            _r(arr[0]), _g(arr[1]), _b(arr[2]), _a(arr[3]) {}

private:
    T _r = {}, _g = {}, _b = {}, _a = {};
};

class hacks {
public:
    DWORD client;
    DWORD engine;

    const CHAR *name = "Counter-Strike: Global Offensive - Direct3D 9";
    memory_controller m;
    config cfg;

    Vec3 RCS_control{0, 2, 2};
    Vec3 oPunch{0, 0, 0};

    void print_cheat_menu() const;
    void set_chams(DWORD entity, int r, int g, int b);
    void get_and_set_config();
    static std::string get_config_name(std::string str);
    void reset_chams();
    static void delay(int d);
    static void click();
    void set_config(config configuration);
    void set_var(bool &var, int key) const;
    void set();

    void radarhack();
    void chams_func();
    void antiflash();
    void triggerbot();
    void bunnyhop();
    void recoil_control_system();
    void wallhack();
    void antiaim();

    void printEntityList();
    void printmyweapon();

    static void print_string_with_delay(const std::string& str, int d);
    static void welcome();

    hacks();
};


#endif //PROJECT1_HACKS_H
