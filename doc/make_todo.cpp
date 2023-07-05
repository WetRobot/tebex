#include<vector>
#include<string>
#include<regex>

#include <filesystem>
namespace fs = std::filesystem;

#include "./include/tebex/tebex.hpp"
#include "./include/tebex/tools/misc_utils.hpp"

void list_cpp_files(
    const fs::path&
        dir,
    std::vector<std::string>&
        out_file_paths
) {
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        std::string ext = entry.path().extension().string();
        std::regex re_ext = std::regex("^[.][ch]pp$");
        if (fs::is_regular_file(entry) && utils::re_detect(ext, re_ext)) {
            out_file_paths.push_back(entry.path().string());
        }
    }
}

int main() {
    // @doc README.md
    // ## Example .cpp scripts
    // 
    // - `./doc/make_readme.cpp`: A tiny c++ programme to populate `README.md`.
    std::vector<std::string> file_paths;
    list_cpp_files(".", file_paths);
    tebex::extract::extract(
        file_paths,
        tebex::process::process_comment_blocks_factory(
            std::regex("^[ ]*/{2,}.*$"),
            std::regex("^[ ]*/[*].*$"),
            std::regex("^[ ]*[*]/.*$"),
            std::regex("^[ /*]*(@TODO)[ ]*(.+)$"),
            std::regex("^[ ]*[/*]+"),

            {"@TODO"},
            {},
            {},
            {}
        ),
        "./tmp/",
        0
    );
    
    return(0);
}
