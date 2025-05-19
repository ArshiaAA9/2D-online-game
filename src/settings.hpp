#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <utility>

using json = nlohmann::json;

class Settings {
public:
    Settings();

    int getWidth() const;
    int getHeight() const;
    std::pair<int, int> getWidthHeight() const;

private:
    json getSettingsJson() const;

    std::string m_settingsPath = "/home/arshia/coding/trash-fight/src/settings.json";
    json m_settingsJson;
    int m_width, m_height;
};
