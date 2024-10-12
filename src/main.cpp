#include "ecs/camera.h"
#include "math/Mathf.h"
#include "math/Random.h"
#include "sys/SystemInfo.h"
#include "utils/AssetsManager.h"
#include "utils/FileHandler.h"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif


int main() {
    tj::Random::Seed();

#if defined(_WIN32) || defined(__EMSCRIPTEN__)
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TJ - Game", sf::Style::Close);
#else
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "TJ - Game", sf::Style::Close);
#endif

    // window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    auto& assetsManager = tj::AssetsManager::GetInstance();
    auto& debug         = tj::Debug::GetInstance();

    debug.SetSaveToDisk(false);
    // debug.SetEnabled(false); // COMMENT: By default debug is enabled

    auto deviceModel   = tj::SystemInfo::GetDeviceModel();
    auto deviceName    = tj::SystemInfo::GetDeviceName();
    auto deviceUID     = tj::SystemInfo::GetDeviceUniqueIdentifier();
    auto deviceBattery = tj::SystemInfo::GetBatteryLevel();

    TJ_LOG_INFO("Test log info");

    TJ_LOG_INFO("Random number between (0,100) %d", tj::Random::Range(0, 100));
    TJ_LOG_INFO("Random number between (12,22) %d", tj::Random::Range(12, 22));
#ifdef _WIN32
    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.FontGlobalScale = 2.f;
    io.IniFilename     = nullptr;

    ImGuiStyle& style                 = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg].w = 0.5f;
#endif

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    assetsManager.LoadFont("mine_font", "mine_font.ttf");
    assetsManager.LoadFont("mine_font", "mine_font.ttf");
    assetsManager.LoadMusic("time_for_adventure", "time_for_adventure.mp3");
    assetsManager.LoadTexture("player", "player.png");
    assetsManager.LoadTexture("skeleton_spirte", "skeleton_spirte.png"); // ERROR JUST FOR TESTING
    assetsManager.LoadTexture("skeleton_sprite", "skeleton_sprite.png");

    sf::Text randomText;
    randomText.setFont(assetsManager.GetFont("mine_font"));
    randomText.setCharacterSize(16);
    randomText.setString("Hello world!!!");

    sf::Clock clock;
    float fps = 0.0f;

    // Setup docking
    bool show_project = true;
    bool show_console = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
#ifdef _WIN32
            ImGui::SFML::ProcessEvent(window, event);
#endif

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        sf::Time deltaTime     = clock.restart();
        float deltaTimeSeconds = deltaTime.asSeconds();
        deltaTimeSeconds       = std::clamp(deltaTimeSeconds, 0.f, 1.f);
        fps                    = 1.0f / deltaTimeSeconds;

#ifdef _WIN32
        ImGui::SFML::Update(window, deltaTime);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);


        ImGui::SetNextWindowDockID(ImGui::GetID("DockBottom"), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(0, window.getSize().y - 300));
        ImGui::SetNextWindowSize(ImVec2(window.getSize().x, 300));

        ImGui::Begin("Content");

        if (ImGui::BeginTabBar("Tabs")) {
            if (ImGui::BeginTabItem("Assets")) {

                ImGui::SeparatorText("Textures");
                for (auto& texture : assetsManager.GetTextures()) {
                    ImGui::Text("%s", texture.first.c_str());
                }

                ImGui::SeparatorText("Fonts");
                for (auto& font : assetsManager.GetFonts()) {
                    ImGui::Text("%s", font.first.c_str());
                }

                ImGui::SeparatorText("Musics");
                for (auto& music : assetsManager.GetMusics()) {
                    ImGui::Text("%s", music.first.c_str());
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Console")) {
                ImGui::Text("Quantity %d", debug.GetLogBuffer().size());

                for (auto& log : debug.GetLogBuffer()) {
                    ImGui::Text(log.c_str());
                }

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();

        ImGui::Begin("Debug");
        ImGui::SeparatorText("Game");
        ImGui::Text("DeltaTime: %f", deltaTimeSeconds);
        ImGui::Text("FPS: %f", fps);

        ImGui::SeparatorText("Device");
        ImGui::Text("Device Model: %s", deviceModel.c_str());
        ImGui::Text("Device Name: %s", deviceName.c_str());
        ImGui::Text("Device UniqueID: %s", deviceUID.c_str());
        ImGui::Text("Device Battery: %f", deviceBattery);
        ImGui::End();
#endif

        window.clear();
        window.draw(shape);
        window.draw(randomText);

#ifdef _WIN32
        ImGui::SFML::Render(window);
#endif

        window.display();
    }

#ifdef _WIN32
    ImGui::SFML::Shutdown();
#endif

    return 0;
}
