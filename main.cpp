#include "hacks.h"
#include <thread>

hacks cheat;

void functions() {
    while (true) {
        cheat.radarhack();
        cheat.antiflash();
        cheat.chams_func();
        cheat.set();
        if (cheat.cfg.close) {
            cheat.reset_chams();
            break;
        }
    }
}

void wallhack() {
    while (true) {
        cheat.wallhack();
    }
}

void bunny_hop() {
    while (true) {
        cheat.bunnyhop();
    }
}

void trigger_bot() {
    while (true) {
        cheat.triggerbot();
    }
}

void recoil_control_system() {
    while (true) {
        cheat.recoil_control_system();
    }
}

int main() {
    MessageBox(::GetConsoleWindow(), NULL, NULL, MB_OK);
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    cheat.print_cheat_menu();
    std::thread funcs(functions);
    std::thread wh(wallhack);
    std::thread bh(bunny_hop);
    std::thread tb(trigger_bot);
    std::thread rcs(recoil_control_system);

    wh.detach();
    bh.detach();
    tb.detach();
    rcs.detach();
    funcs.join();
    return 0;
}