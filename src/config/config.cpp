#include "config.hpp"
#include "koalabox/util/util.hpp"

#include <fstream>

namespace config {
    Config instance = {};

    void init(const Path path) { // NOLINT(performance-unnecessary-value-param)
        if (not std::filesystem::exists(path)) {
            return;
        }

        try {
            std::ifstream ifs(path);
            nlohmann::json json = nlohmann::json::parse(ifs, nullptr, true, true);

            instance = json.get<Config>();
        } catch (const std::exception& ex) {
            const auto message = fmt::format("Failed to parse config file: {}", ex.what());
            util::error_box("config::read", message);
            exit(::GetLastError()); // NOLINT(cppcoreguidelines-narrowing-conversions)
        }
    }

}
