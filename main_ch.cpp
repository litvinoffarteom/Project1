//
// Created by Админ on 29.10.2022.
//

#include "main_ch.h"

void main_ch::set() {
    if (GetKeyState(VK_F1)) {
        if (!radar_hack) {
            radar_hack = true;
            print_cheat_menu();
        }
    } else {
        if (radar_hack) {
            radar_hack = false;
            print_cheat_menu();
        }
    }
    if (GetKeyState(VK_F2)) {
        if (!bunny_hop) {
            bunny_hop = true;
            print_cheat_menu();
        }
    } else {
        if (bunny_hop) {
            bunny_hop = false;
            print_cheat_menu();
        }
    }
    if (GetKeyState(VK_F3)) {
        if (!trigger_bot) {
            trigger_bot = true;
            print_cheat_menu();
        }
    } else {
        if (trigger_bot) {
            trigger_bot = false;
            print_cheat_menu();
        }
    }
    if (GetKeyState(VK_F4)) {
        if (!anti_flash) {
            anti_flash = true;
            print_cheat_menu();
        }
    } else {
        if (anti_flash) {
            anti_flash = false;
            print_cheat_menu();
        }
    }
    /*
    if (GetKeyState(VK_F6)) {
        if (!anti_aim) {
            anti_aim = true;
            print_cheat_menu();
        }
    } else {
        if (anti_aim) {
            anti_aim = false;
            print_cheat_menu();
        }
    }
     */
    if (GetKeyState(VK_F7)) {
        if (!RCS) {
            RCS = true;
            print_cheat_menu();
        }
    } else {
        if (RCS) {
            RCS = false;
            print_cheat_menu();
        }
    }
    if (GetKeyState(VK_F8)) {
        if (!chams) {
            chams = true;
            print_cheat_menu();
        }
    } else {
        if (chams) {
            chams = false;
            for (int i = 1; i < 64; i++) {
                auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
                m.WPM<int>(entity + 112, 255);
                m.WPM<int>(entity + 113, 255);
                m.WPM<int>(entity + 114, 255);
            }
            print_cheat_menu();
        }

    }
    if (GetAsyncKeyState(VK_HOME)) {
        RCS_control.x = 2;
        RCS_control.y = 0;
        Sleep(100);
    }
    if (GetAsyncKeyState(VK_F9)) {
        RCS_control.x = 0;
        RCS_control.y = 2;
        Sleep(100);
    }
    if (GetAsyncKeyState(VK_F11)) {
        RCS_control.x = 2;
        RCS_control.y = 2;
        Sleep(100);
    }
}

void main_ch::print_cheat_menu() {
    system("cls");
    std::cout << std::string(52, '=') << "LEGIT CSGO CHEAT" << std::string(52, '=')
              << "\n \n Functions of cheat:\n -Radarhack " << radar_hack << "\n -Bunnyhop " << bunny_hop
              << "\n -Trigger Bot (ALT) " << trigger_bot << "\n" << " -Antiflash " << anti_flash << "\n -Chams "
              << chams
              << "\n -RCS (F7) " << RCS << std::endl << std::endl << "Settings: " << std::endl
              << " -MEGA Legit RCS (Only X)" << std::endl
              << " -Legit RCS(Only Y) - F9" << std::endl << " -RCS(X and Y) - F11" << "\n \n Exit cheat - INSERT"
              << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
              << std::string(120, '=');
}
main_ch::main_ch() {
    this->name = "Counter-Strike: Global Offensive - Direct3D 9";
    client = m.GetModuleBaseAddress("client.dll");
    engine = m.GetModuleBaseAddress("engine.dll");
}
main_ch::main_ch(const CHAR *name) {

    this->name = name;
    m.setNewWindow(name);
    client = m.GetModuleBaseAddress("client.dll");
    engine = m.GetModuleBaseAddress("engine.dll");


}

main_ch::~main_ch() {
    CloseHandle(m.handle);
}

void main_ch::radarhack() {
    for (int i = 0; i < 64; i++) {
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        m.WPM<bool>(entity + hazedumper::netvars::m_bSpotted, true);
    }
}

void main_ch::set_chams(DWORD entity, int r, int g, int b) {
    m.WPM<int>(entity + 112, r);
    m.WPM<int>(entity + 113, g);
    m.WPM<int>(entity + 114, b);
}

void main_ch::chams_func() {
    for (int i = 0; i < 64; i++) {
        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        auto eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
        auto pTeam = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
        if (eTeam && eTeam != pTeam) {
            auto entity_health = m.RPM<int>(entity + hazedumper::netvars::m_iHealth);
            if (entity_health > 75) {
                set_chams(entity, 255, 0, 0);
            } else if (entity_health > 50) {
                set_chams(entity, 255, 0, 255);
            } else if (entity_health > 25) {
                set_chams(entity, 165, 0, 255);
            } else {
                set_chams(entity, 0, 0, 255);
            }
        } else {
            set_chams(entity, 0, 255, 0);
        }

    }
}

void main_ch::antiflash() {
    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
    auto flash = m.RPM<float>(local_player + hazedumper::netvars::m_flFlashDuration);
    if (flash > 0) {
        m.WPM(local_player + hazedumper::netvars::m_flFlashDuration, 0);
    }
}

void main_ch::triggerbot() {
    if (GetAsyncKeyState(VK_MENU)) {

        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        if (local_player) {
            int pTeam = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
            int crosshair = m.RPM<int>(local_player + hazedumper::netvars::m_iCrosshairId);
            if (crosshair != 0 && crosshair < 64) {
                auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + (crosshair - 1) * 0x10);
                if (entity) {
                    int eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
                    if (eTeam != pTeam && eTeam) {
                        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                        Sleep(100);
                    }
                }
            }
        }
    }
}

void main_ch::bunnyhop() {
    if (GetAsyncKeyState(VK_SPACE)) {
        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        auto player_state = m.RPM<int>(local_player + hazedumper::netvars::m_fFlags);

        if (player_state == 257) {
            mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
            Sleep(100);
        }
    }
}

void main_ch::recoil_control_system() {
    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
    auto clientState = m.RPM<DWORD>(engine + hazedumper::signatures::dwClientState);
    Vec3 viewAngles = m.RPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles);
    int shotsFired = m.RPM<int>(local_player + hazedumper::netvars::m_iShotsFired);
    Vec3 aimPunchAngle = m.RPM<Vec3>(local_player + hazedumper::netvars::m_aimPunchAngle);


    Vec3 punchAngle = aimPunchAngle * RCS_control;
    if (shotsFired > 1) {
        Vec3 newAngle = viewAngles + oPunch - punchAngle;
        newAngle.Normalize();
        m.WPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles, newAngle);

    }
    oPunch = punchAngle;
}

void main_ch::reset_chams() {
    for (int i = 0; i < 64; i++) {
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        set_chams(entity, 255, 255, 255);
    }
}

void main_ch::printEntityList() {
    std::cout << "Entity health list: " << std::endl;
    for (int i = 0; i < 64; i++) {
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        if (entity) {
            auto eHealth = m.RPM<int>(entity + hazedumper::netvars::m_iHealth);
            auto eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
            std::cout << eHealth << std::endl;
            std::cout << eTeam << std::endl << std::endl;
        }
    }

}

void main_ch::antiaim() {
    /*
    auto clientState = m.RPM<DWORD>(engine + hazedumper::signatures::dwClientState);
    Vec3 viewAngles = m.RPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles);
    Vec3 newAngle = viewAngles - Vec3{0, 180, 0};
    newAngle.Normalize();
    m.WPM(clientState + hazedumper::signatures::dwClientState_ViewAngles, newAngle);
    Sleep(10);
    viewAngles = m.RPM<Vec3>(clientState + hazedumper::signatures::dwClientState_ViewAngles);
    newAngle = viewAngles - Vec3{0, 180, 0};
    newAngle.Normalize();
    m.WPM(clientState + hazedumper::signatures::dwClientState_ViewAngles, newAngle);
    Sleep(150);
    */
}

