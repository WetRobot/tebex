#ifndef STORE_HPP
#define STORE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <map>
#include <tuple>
#include <functional>

namespace store{
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    typedef
    std::function<
        void(
            const std::string& key,
            const std::string& line,
            const int& line_no
        )
    >
    store_type;

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Default function to handle storing extraction results.
     * Writes extracted line into e.g. `./tebex_output/x.txt` when `key = "x"`.
     * Note the extensions `.txt` that is always added.
     * @param key
     * Store data for this key.
     * @param line
     * Store this line.
     * @param line_no
     * Line number not stored anywhere by default.
    */
    void store_default(
        const std::string& key,
        const std::string& line,
        const int& line_no
    ) {
        std::string output_file_path = "./tebex_output/" + key + ".txt";
        std::fstream file_connection;
        file_connection.open(
            output_file_path,
            std::ios_base::app | std::ios_base::in
        );
        if (file_connection.is_open()) {
            file_connection << line << std::endl;
        }
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Outputs a function which in turn stores extracted line into
     * `output_dir_path` (e.g. `"./tebex_output/x"` for `key = "x").
     * Note, no file extension added.
     * @param output_dir_path
     * Path to directory into which the tebex_output function will write data.
    */
    store_type store_fs_factory(std::string output_dir_path) {
        return [&](
            const std::string& key,
            const std::string& line,
            const int& line_no
        ) -> void
        {
            if (key == "") {
                throw std::invalid_argument(
                    "Argument key = \""
                    + key
                    + "\""
                );
            }
            std::string output_file_path = output_dir_path + "/" + key;
            std::fstream file_connection;
            file_connection.open(
                output_file_path,
                std::ios_base::app | std::ios_base::in
            );
            if (file_connection.is_open()) {
                file_connection << line << std::endl;
            }
        };
    }



    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    typedef
    std::map<std::string, std::vector<std::string>>
    __store_map_output_line_map_type;
    __store_map_output_line_map_type __store_map_output_line_map;
    
    typedef
    std::map<std::string, std::vector<int>>
    __store_map_output_line_no_map_type;
    __store_map_output_line_no_map_type __store_map_output_line_no_map;

    typedef
    std::tuple<
        __store_map_output_line_map_type,
        __store_map_output_line_no_map_type
    >
    store_map_get_type;

    store_map_get_type
    store_map_get() {
        store_map_get_type t = std::make_tuple(
            __store_map_output_line_map,
            __store_map_output_line_no_map
        );
        __store_map_output_line_map.clear();
        __store_map_output_line_no_map.clear();
        return(t);
    }
    /**
     * @brief
     * Outputs a function which in turn stores the extracted line and line
     * number into two std::map objects.
     * Returns the two std::map object and the store function
     * in a tuple with elements in that order. Keys of the maps are keys
     * extracted from the text files (strings) and contents are vectors of
     * strings / integer.
     * @param output_dir_path
     * Path to directory into which the tebex_output function will write data.
    */
    store_type store_map_factory() {
        store_type store_fun = [&]
        (
            const std::string& key, const std::string& line, int line_no
        ) mutable 
        {
            auto key_pos = __store_map_output_line_map.find(key);
            if (key_pos == __store_map_output_line_map.end()) {
                std::vector<std::string> lines;
                lines.push_back(line);
                __store_map_output_line_map[key] = lines;
            } else {
                key_pos->second.push_back(line);
            }

            auto num_pos = __store_map_output_line_no_map.find(key);
            if (num_pos == __store_map_output_line_no_map.end()) {
                std::vector<int> line_numbers;
                line_numbers.push_back(line_no);
                __store_map_output_line_no_map[key] = line_numbers;
            } else {
                num_pos->second.push_back(line_no);
            }
        };
        return(store_fun);
    }
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
} // namespace store

#endif
