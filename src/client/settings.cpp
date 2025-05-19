#include "settings.hpp"

#include <fstream>
#include <iostream>

Settings::Settings() {
    std::ifstream file(m_settingsPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open settings file at " << m_settingsPath << '\n';
        throw std::runtime_error("Failed to open settings file");
    }
    try {
        m_settingsJson = json::parse(file);
        std::cout << std::setw(4) << m_settingsJson["client"]["settings"] << '\n';
        try {
            m_width = m_settingsJson["client"]["settings"]["width"].get<int>();
            m_height = m_settingsJson["client"]["settings"]["height"].get<int>();
        } catch (const nlohmann::json::exception& e) {
            std::cerr << "unable to read settings.json! using defaults error:" << e.what() << "\n";
            m_width = m_settingsJson["client"]["defaults"]["width"];
            m_height = m_settingsJson["client"]["defaults"]["height"];
        }
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << '\n';
        throw;
    }
}

json Settings::getSettingsJson() const { return m_settingsJson; }

int Settings::getWidth() const { return m_width; }

int Settings::getHeight() const { return m_height; }

std::pair<int, int> Settings::getWidthHeight() const { return {m_width, m_height}; }
