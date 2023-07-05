#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>
#include <vector>
#include <regex>
#include <map>

#include "misc_utils.hpp"

namespace args{
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    void assert_is_file_path(
        std::string x,
        std::string arg_nm = "file_path"
    ) {
        if (!utils::file_is_accessible(x)) {
            throw std::invalid_argument(
                "Argument \"" + arg_nm + "\" = \""
                + x
                + "\" is not accessible --- does it exist?"
            );
        }
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    void assert_is_verbosity(
        int x,
        std::string arg_nm = "verbosity"
    ) {
        if (x < 0 || x > 3) {
            throw std::invalid_argument(
                "Argument \"" + arg_nm + "\" must be 0, 1, 2, or 3"
            );
        }
    }
        
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
}

#endif