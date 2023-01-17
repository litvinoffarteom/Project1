#include "hacks.h"

void hacks::print_cheat_menu() const {
    system("cls");
    if (cfg.fake) {
        std::cout << "Telegram bot";
    } else {
        std::cout << std::string(52, '=') << "LEGIT CSGO CHEAT" << std::string(52, '=')
                  << "\n \n Functions of cheat:\n -Radarhack \t\t" << cfg.radar_hack << "\n -Bunnyhop \t\t"
                  << cfg.bunny_hop
                  << "\n -Trigger Bot (ALT) \t" << cfg.trigger_bot << "\n" << " -Antiflash \t\t" << cfg.anti_flash
                  << "\n -Chams \t\t"
                  << cfg.chams
                  << "\n -RCS (F7) \t\t" << cfg.RCS << "\n -Glow Wallhack \t" << cfg.wall_hack << std::endl << std::endl
                  << "Settings: " << std::endl
                  << " -MEGA Legit RCS (Only X)" << std::endl
                  << " -Legit RCS(Only Y) - F9" << std::endl << " -RCS(X and Y) - F11" << std::endl
                  << " -Trigger bot and chams teammates \t" << cfg.teammates << std::endl
                  << " -Legit trigger bot \t\t\t"
                  << cfg.legit_trigger_bot << std::endl << " -Legit bunny hop \t\t\t" << cfg.legit_bunny_hop
                  << std::endl << " -Antiflash delay \t\t\t" << cfg.anti_flash_delay << "\n -Teammates chams color \t"
                  << cfg.chams_teammates.r << ' ' << cfg.chams_teammates.g << ' ' << cfg.chams_teammates.b
                  << "\n -Enemy chams color \t\t" << cfg.chams_enemy.r << ' ' << cfg.chams_enemy.g << ' '
                  << cfg.chams_enemy.b << "\n -Health based glow \t\t\t" << cfg.health_based_glow
                  << "\n\n Exit cheat - INSERT" << std::endl << " Hide cheat - F6"
                  << std::endl << std::endl << std::endl << std::endl
                  << std::endl
                  << std::string(120, '=');
    }
}

void hacks::set_chams(DWORD entity, int r, int g, int b) {
    m.WPM<int>(entity + 112, r);
    m.WPM<int>(entity + 113, g);
    m.WPM<int>(entity + 114, b);
}

void hacks::get_and_set_config() {
    system("cls");
    config configuration;
    std::string config_name;
    std::cout << " Fast load: \n 1. Ultra Legit Config \n 2. Mega Legit Config \n 3. Legit Config \n\n";
    std::cout << " Enter Config Name(enter default if you want to use default configuration): ";
    std::cin >> config_name;
    if (config_name != "default") {
        std::ifstream in(get_config_name(config_name));
        if (in.is_open()) {
            in >> configuration.chams_enemy.r >> configuration.chams_enemy.g >> configuration.chams_enemy.b
               >> configuration.chams_teammates.r >> configuration.chams_teammates.g
               >> configuration.chams_teammates.b >> configuration.teammates >> configuration.legit_trigger_bot
               >> configuration.legit_bunny_hop >> configuration.anti_flash_delay >> configuration.health_based_glow
               >> configuration.fake;
        }
        in.close();


    }
    set_config(configuration);
    print_cheat_menu();
}

void hacks::reset_chams() {
    for (int i = 0; i < 64; i++) {
        auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
        set_chams(entity, 255, 255, 255);
    }

}

void hacks::delay(int d) {
    if (d) {
        std::this_thread::sleep_for(std::chrono::milliseconds(d));
    }
}

void hacks::click() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void hacks::set_config(config configuration) {
    cfg = configuration;
}

void hacks::set_var(bool &var, int key) const {
    if (GetAsyncKeyState(key) & 1) {
        var = !var;
        print_cheat_menu();
    }
}

void hacks::set() {
    set_var(cfg.trigger_bot, VK_F3);
    set_var(cfg.radar_hack, VK_F1);
    set_var(cfg.anti_flash, VK_F4);
    set_var(cfg.bunny_hop, VK_F2);
    set_var(cfg.RCS, VK_F7);
    set_var(cfg.wall_hack, VK_NEXT);

    if (GetAsyncKeyState(VK_PRIOR)) {
        m.reconnect(name);
        client = m.GetModuleBaseAddress("client.dll");
        engine = m.GetModuleBaseAddress("engine.dll");
        Sleep(100);
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
    if (GetKeyState(VK_F8)) {
        if (!cfg.chams) {
            cfg.chams = true;
            print_cheat_menu();
        }
    } else {
        if (cfg.chams) {
            cfg.chams = false;
            reset_chams();
            print_cheat_menu();
        }

    }
    if (GetAsyncKeyState(VK_DELETE)) {
        if(cfg.console){
            get_and_set_config();
        }
    }
    if (GetKeyState(VK_F6)){
        if (!cfg.console) {
            cfg.console = true;
            ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
            ::SetForegroundWindow(::GetConsoleWindow());
            print_cheat_menu();
        }
    } else {
        if (cfg.console) {
            cfg.console = false;
            ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
            ::SetForegroundWindow(m.hwnd);
            print_cheat_menu();


        }
    }
    if (GetAsyncKeyState(VK_INSERT)) {
        cfg.close = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

}

void hacks::radarhack() {
    if (cfg.radar_hack) {
        for (int i = 0; i < 64; i++) {
            auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
            if (entity) {
                m.WPM(entity + hazedumper::netvars::m_bSpotted, true);
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

}

void hacks::chams_func() {
    if (cfg.chams && !cfg.close) {
        for (int i = 0; i < 64; i++) {
            auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
            auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
            if (cfg.teammates) {
                set_chams(entity, cfg.chams_enemy.r, cfg.chams_enemy.g, cfg.chams_enemy.b);
            } else {
                auto eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
                auto pTeam = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
                if (eTeam && eTeam != pTeam) {
                    set_chams(entity, cfg.chams_enemy.r, cfg.chams_enemy.g, cfg.chams_enemy.b);
                } else {
                    set_chams(entity, cfg.chams_teammates.r, cfg.chams_teammates.g, cfg.chams_teammates.b);
                }
            }
        }
    } else if (cfg.close) {
        reset_chams();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void hacks::antiflash() {
    if (cfg.anti_flash) {
        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        auto flash = m.RPM<float>(local_player + hazedumper::netvars::m_flFlashDuration);
        if (flash > 0) {
            if (cfg.anti_flash_delay) Sleep(200);
            m.WPM(local_player + hazedumper::netvars::m_flFlashDuration, 0);
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void hacks::triggerbot() {

    if (!cfg.trigger_bot) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        return;
    }

    if (!GetAsyncKeyState(VK_MENU)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        return;
    }

    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
    if (!local_player) {
        return;
    }

    int crosshair = m.RPM<int>(local_player + hazedumper::netvars::m_iCrosshairId);

    if (crosshair == 0 || crosshair >= 64) {
        return;
    }
    auto entity = m.RPM<DWORD>(
            client + hazedumper::signatures::dwEntityList + (crosshair - 1) * 0x10);

    if (!entity) {
        return;
    }
    if (cfg.teammates) {
        if (cfg.legit_trigger_bot) delay(50);
        click();
        std::cout << "click";        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
        int eTeam = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
        int pTeam = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
        if (eTeam != pTeam && eTeam) {
            if (cfg.legit_trigger_bot) delay(50);
            click();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void hacks::bunnyhop() {
    if (cfg.bunny_hop) {
        if (GetAsyncKeyState(VK_SPACE)) {
            auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
            auto player_state = m.RPM<int>(local_player + hazedumper::netvars::m_fFlags);
            if (player_state == 257 || player_state == 263) {
                if (cfg.legit_bunny_hop) {
                    int random = rand() % 5;
                    if (!random) Sleep(50);
                }

                mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void hacks::recoil_control_system() {
    if (cfg.RCS) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void hacks::printEntityList() {
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

void hacks::antiaim() {
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

void hacks::wallhack() {
    if (cfg.wall_hack) {
        auto glow_object_manager = m.RPM<DWORD>(client + hazedumper::signatures::dwGlowObjectManager);
        auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);
        auto p_team = m.RPM<int>(local_player + hazedumper::netvars::m_iTeamNum);
        for (int i = 0; i < 64; i++) {
            auto entity = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + i * 0x10);
            if (entity) {
                auto glow_index = m.RPM<int>(entity + hazedumper::netvars::m_iGlowIndex);
                auto e_team = m.RPM<int>(entity + hazedumper::netvars::m_iTeamNum);
                if (e_team != p_team || cfg.teammates) {
                    auto is_scoped = m.RPM<bool>(entity + hazedumper::netvars::m_bIsScoped);
                    auto e_health = m.RPM<int>(entity + hazedumper::netvars::m_iHealth);
                    if (is_scoped) {
                        m.WPM(
                                glow_object_manager + (0x38 * glow_index) + 0x8,
                                color4_t{v::other_team_glow_scoped.second}
                        );
                    } else if (cfg.health_based_glow) {
                        if (e_health > 75) {
                            m.WPM(
                                    glow_object_manager + (0x38 * glow_index) + 0x8,
                                    color4_t{v::other_team_glow_100.second}
                            );
                        } else if (e_health > 50) {
                            m.WPM(
                                    glow_object_manager + (0x38 * glow_index) + 0x8,
                                    color4_t{v::other_team_glow_75.second}
                            );
                        } else if (e_health > 25) {
                            m.WPM(
                                    glow_object_manager + (0x38 * glow_index) + 0x8,
                                    color4_t{v::other_team_glow_50.second}
                            );
                        } else {
                            m.WPM(
                                    glow_object_manager + (0x38 * glow_index) + 0x8,
                                    color4_t{v::other_team_glow_25.second}
                            );
                        }
                    } else {
                        m.WPM(
                                glow_object_manager + (0x38 * glow_index) + 0x8,
                                color4_t{v::other_team_glow_100.second}
                        );
                    }
                } else {
                    m.WPM(
                            glow_object_manager + (0x38 * glow_index) + 0x8,
                            color4_t{v::my_team_glow.second}
                    );
                }
                constexpr struct visible_t {
                    bool a{true}, b{false};
                } vis;
                m.WPM(glow_object_manager + (0x38 * glow_index) + 0x28, vis);
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void hacks::printmyweapon() {
    auto local_player = m.RPM<DWORD>(client + hazedumper::signatures::dwLocalPlayer);

    auto weapon = m.RPM<DWORD>(local_player + hazedumper::netvars::m_hActiveWeapon);
    auto weapon_pointer = m.RPM<DWORD>(client + hazedumper::signatures::dwEntityList + (weapon - 1) * 0x10);
    auto weapon_type = m.RPM<int>(weapon_pointer + hazedumper::netvars::m_iItemDefinitionIndex);
    std::cout << weapon_type << std::endl;


}

void hacks::print_string_with_delay(const std::string &str, int d) {
    for (char c: str) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(d));
    }
}

void hacks::welcome() {
    system("cls");
    int d = 100;
    print_string_with_delay("Welcome to my CS:GO cheat", d);
}

hacks::hacks() {
    srand(time(NULL));
    client = m.GetModuleBaseAddress("client.dll");
    engine = m.GetModuleBaseAddress("engine.dll");
}

std::string hacks::get_config_name(std::string str) {
    if (str == "1") {
        return "config_fast_load_1.cfg";
    }
    if (str == "2") {
        return "config_fast_load_2.cfg";
    }
    if (str == "3") {
        return "config_fast_load_3.cfg";
    }
    return str;
}
