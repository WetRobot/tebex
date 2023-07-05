#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <functional>
#include <map>
#include <sys/stat.h>

namespace utils{
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Get position of first match of `x` in `y`. If there is no match,
     * return `-1`.
     * @param x
     * Object to match in `y`.
     * @param y
     * Vector of objects.
    */
    template<typename T>
    int match_first(const T& x, const std::vector<T>& y) {
        int m = -1;
        int i = -1;
        for (T y_elem : y) {
            i += 1;
            if (x == y_elem) {
                m = i;
                break;
            }
        }
        return(m);
    } 

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Return `true` if string `x` matches regex `r`, else `false`.
     * Uses `std::regex_search`.
     * @param x
     * A string.
     * @param r
     * A regex.
     * @param args
     * Additional arbitrary arguments passed to `std::regex_search`.
    */
    template <typename... Args>
    bool re_detect(
        const std::string& x, 
        const std::regex& r,
        Args... args
    ) {
        std::smatch m;
        bool out = false;
        if (std::regex_search(x, m, r, args...)) {
            out = true;
        }
        return(out);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Return extracted part of `x` that matches `r`. If there is no match,
     * return `""`.
     * @param x
     * A string.
     * @param r
     * A regex.
     * @param args
     * Additional arbitrary arguments passed to `std::regex_search`.
    */
    template <typename... Args>
    std::string re_extract(
        const std::string& x,
        const std::regex& r,
        Args... args
    ) {
        std::smatch m;
        std::string out = "";
        if (std::regex_search(x, m, r, args...)) {
            out = m.str();
        }
        return(out);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Return extracted parts of `x` that match separate capture groups of `r`.
     * If there are no matched capture groups, return a vector of length zero.
     * @param x
     * A string.
     * @param r
     * A regex with capture groups.
     * @param args
     * Additional arbitrary arguments passed to `std::regex_search`.
    */
    template <typename... Args>
    std::vector<std::string> re_extract_groups(
        const std::string& x,
        const std::regex& r,
        Args... args
    ) {
        std::smatch m;
        std::vector<std::string> out;
        if (std::regex_search(x, m, r, args...)) {
            int n = m.size();
            if (n > 1) {
                for (int i = 1; i < n; i++) {
                    out.push_back(m[i]);
                }
            }
        }
        return(out);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Return last capture group of match in string `x` against regex `r`.
     * @param x
     * A string.
     * @param r
     * A regex.
     * @param args
     * Additional arbitrary arguments passed to `std::regex_search`.
    */
    template <typename... Args>
    std::string re_extract_last_group(
        const std::string& x,
        const std::regex& r,
        Args... args
    ) {
        std::smatch m;
        std::string out = "";
        if (std::regex_search(x, m, r, args...)) {
            int n = m.size();
            out = m[n - 1].str();
        }
        return(out);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Defines what a key is allowed to look like. Currently allowed to contain
     * any characters on the same line (after the tag and any whitespace).
    */
    std::string key_regex_string() {
        return(".+");
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Returns a regex which matches any tag supplied via `tag_set`
     * plus any interim whitespaces, the key, and any trailing whitespaces.
     * The key is in the last capture group of the regex.
    */
    std::regex tag_set_to_regex(const std::vector<std::string>& tag_set) {
        std::string s = "(";
        for (std::string tag : tag_set) {
            s += "(" + tag + ")|";
        }
        s.pop_back(); // remove trailing |
        s += ")[ ]*(" + key_regex_string() + ")[ ]*$";
        std::regex r = std::regex(s);
        return(r);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Printing for debugging.
     * @param x
     * Any object.
     * @param x_nm
     * Name of object in debug message.
    */
    template<typename T>
    void print(const T& x, const std::string& x_nm) {
        std::cout << x_nm << " = " << std::to_string(x) << std::endl;
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Printing for debugging.
     * @param x
     * Any object.
     * @param x_nm
     * Name of object in debug message.
    */
    void print(const std::string& x, const std::string& x_nm) {
        std::cout << x_nm << " = \"" << x << "\"" << std::endl;
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Printing for debugging.
     * @param x
     * Any vector object.
     * @param x_nm
     * Name of object in debug message.
    */
    template<typename T>
    void print(const std::vector<T>& x, const std::string& x_nm) {
        std::cout << x_nm << " is a vector of size ";
        std::cout << std::to_string(x.size()) << std::endl;
        if (x.size() == 0) {
            std::cout << x_nm << "[]" << std::endl;
        } else {
            for (int i = 0; i < x.size(); i++) {
                std::string x_nm_i = "  [" + std::to_string(i) + "]";
                utils::print(x[i], x_nm_i);
            }
        }
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Printing for debugging.
     * @param x
     * Any vector object.
     * @param x_nm
     * Name of object in debug message.
    */
    template<typename T>
    void print(
        const std::map<std::string, T>&
            x,
        const std::string&
            x_nm
    ) {
        std::cout << x_nm << " is a map of size ";
        std::cout << std::to_string(x.size()) << std::endl;
        if (x.size() == 0) {
            std::cout << x_nm << "[]" << std::endl;
        } else {
            for (const auto& pair : x) {
                std::string key = pair.first;
                std::string x_nm_i = "  [\"" + key + "\"]";
                T x_i = x.at(key);
                print(x_i, x_nm_i);
            }
        }
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Requests user to press enter to proceed. Used in debugging.
    */
    void press_enter_to_proceed() {
        std::cout << "press enter to proceed" << std::endl;
        std::cin.ignore();
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    /**
     * @brief
     * Returns `true` if file is accessible (exists + you have permission to
     * read), else `false`.
     * @param file_path
     * Path to a file.
    */
    bool file_is_accessible(const std::string& file_path) {
        struct stat buffer;   
        return (stat (file_path.c_str(), &buffer) == 0); 
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    template<typename MapType, typename MapElemType, typename FunOutType>
    std::map<std::string, FunOutType> apply_string_map(
        const MapType& x,
        const std::function<FunOutType(const MapElemType&)>& f
    ) {
        std::map<std::string, FunOutType> y;
        for (const auto& kv : x) {
            y[kv.first] = f(kv.second);
        }
        return(y);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    template<typename T>
    void is_in(const T& x, const std::vector<T>& y, bool& out) {
        int yn = y.size();
        for (int i = 0; i < yn; i++) {
            if (y[i] == x) {
                out = true;
                break;
            }
        }
    }
    template<typename T>
    bool is_in(const T& x, const std::vector<T>& y) {
        bool out = false;
        int yn = y.size();
        for (int i = 0; i < yn; i++) {
            if (y[i] == x) {
                out = true;
                break;
            }
        }
        return(out);
    }
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
} // namespace utils

#endif // UTILS_HPP