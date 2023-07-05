#ifndef EXTRACT_HPP
#define EXTRACT_HPP

#include <string>
#include <vector>

#include "misc_utils.hpp"
#include "keysets.hpp"
#include "args.hpp"
#include "process.hpp"
#include "store.hpp"

namespace extract {
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // @docstart README.md
    // ## Features
    //
    // The main feature of this library is extraction of documentation
    // contained within comments. This library does not prepare .html or other
    // documents for you --- it simply extracts what you have written into
    // comments into a location of your choice. Normally you would extract
    // documentation from your comments into text files and produce
    // a larger document out of the smaller ones. This README.md has been
    // produced simply by extracting documentation comments from source files
    // directly into the README.md.
    //
    // ## Main functions
    //
    // You may only need `tebex::extract::extract` or one of its signatures,
    // which currently vary wrt. the first argument (`file_path` / `file_paths`)
    // and arg `store`.
    //
    // ### Single file, arbitrary store callback function `store`
    // ```
    /**
     * @brief
     * Extract blocks of text from a file.
     * @param file_path
     * Path to file from which to extract documentation.
     * @param process
     * Storage method, here an arbitrary callback function.
     * Must have arguments
     *     const std::string&  line,
     *     std::string&        out_block_type,
     *     std::string&        out_key,
     *     bool&               out_storeable,
     *     std::string&        out_line
     * @param store
     * Storage method, here an arbitrary callback function.
     * Must have arguments
     *     const std::string& key,
     *     const std::string& line,
     *     const int& line_no
     * @param verbosity
     * For debugging.
     * @details
     * There are three types of blocks of text:
     * - "start-stop":
     *   Those defined by both a starting and stopping line. The starting
     *   and stopping lines look different.
     *    E.g. `{"@start", "text", "@stop"}`.
     * - "boundary":
     *   Those limited by two "boundary" delimiters --- that is, two similar
     *   lines of text. E.g. `{"@boundary", "text", "@boundary"}`.
     * - "start-only":
     *   Those that start after the starting line and stop at the next block's
     *   starting line. E.g. `{"@startonly", "text", "@startonly", "text"}`.
    */
    void extract(
        const std::string&
            file_path,
        const process::process_type&
            process = process::process_markdown,
        const store::store_type&
            store = store::store_default,
        const int&
            verbosity = 0
    )
    // ```
    //
    // @docstop README.md
    {
        // ---------------------------------------------------------------------
        // assertions ----------------------------------------------------------
        args::assert_is_file_path(file_path);
        args::assert_is_verbosity(verbosity);

        // ---------------------------------------------------------------------
        // file connection -----------------------------------------------------
        std::ifstream file_connection;
        file_connection.open(file_path);

        // ---------------------------------------------------------------------
        // prep key search -----------------------------------------------------
        keysets::KeySet key_set_start_only;
        keysets::KeySet key_set_start_stop;

        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        if (verbosity >= 1) {
            std::cout <<
                "tebex::extract::extract: preparations done --- "
                << "starting while loop over lines"
                << std::endl;
            if (verbosity >= 3) {
                utils::print(file_path, "file_path");
                utils::press_enter_to_proceed();
            }
        }
        int line_no = -1;
        std::string line = "";
        while (std::getline(file_connection, line)) {
            // -----------------------------------------------------------------
            // while loop start ------------------------------------------------
            line_no += 1;
            if (line.empty()) {
                line = "";
            }
            if (verbosity >= 2) {
                utils::print(line_no, "line_no");
                utils::print(line, "line");
                if (verbosity >= 3) {
                    std::cout << "process() will be called next\n";
                    utils::press_enter_to_proceed();
                }
            }

            // -----------------------------------------------------------------
            // process ---------------------------------------------------------
            std::string out_line = "";
            std::string out_key = "";
            std::string out_block_type = "";
            bool out_storeable = false;
            process(
                line,
                out_block_type,
                out_key,
                out_storeable,
                out_line
            );
            if (out_key != "") {
                if (out_block_type == "start-only") {
                    key_set_start_only.activate(out_key);
                } else {
                    if (key_set_start_stop.is_active(out_key)) {
                        key_set_start_stop.deactivate(out_key);
                    } else {
                        key_set_start_stop.activate(out_key);
                    }
                }
            }
            if (verbosity >= 2) {
                utils::print(out_block_type, "out_block_type");
                utils::print(out_key, "out_key");
                utils::print(out_storeable, "out_storeable");
                utils::print(out_line, "out_line");
                utils::print(
                    key_set_start_only.get(), "key_set_start_only.get()"
                );
                utils::print(
                    key_set_start_stop.get(), "key_set_start_stop.get()"
                );
                if (verbosity >= 3) {
                    std::cout << "store() will be called next\n";
                    utils::press_enter_to_proceed();
                }
            }

            // -----------------------------------------------------------------
            // store -----------------------------------------------------------
            if (out_storeable) {
                for (auto key : key_set_start_only.get()) {
                    store(
                        key,
                        out_line,
                        line_no
                    );
                }
                for (auto key : key_set_start_stop.get()) {
                    store(
                        key,
                        out_line,
                        line_no
                    );
                }
            }

            // -----------------------------------------------------------------
            // while loop end --------------------------------------------------
        }

        if (verbosity >= 1) {
            std::cout <<
                "tebex::extract::extract: while loop done --- processed "
                << line_no << " lines in total"
                << std::endl;
        }
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // @docstart README.md
    //
    // ### Single file, write results into text files in directory `store`
    // ```
    /**
     * @brief
     * Extract commented documentation from a single text file.
     * Write extracted texts into dir `./tebex_output/` ---
     * one file for each key.
     * @param file_path
     * Path to file from which to extract documentation.
     * @param process
     * Storage method, here an arbitrary callback function.
     * Must have arguments
     *     const std::string&  line,
     *     std::string&        out_block_type,
     *     std::string&        out_key,
     *     bool&               out_storeable,
     *     std::string&        out_line
     * @param store
     * Storage method, here a path to an existing directory.
     * @param verbosity
     * For debugging.
    */
    void extract(
        const std::string&
            file_path,
        const process::process_type&
            process = process::process_markdown,
        const std::string&
            store = "./tebex_output/",
        const int&
            verbosity = 0
    )
    // ```
    //
    // @docstop README.md
    {
        if (!utils::file_is_accessible(store)) {
            std::string msg = "";
            msg += "Cannot access dir path store = ";
            msg += "\"" + store + "\"" + "; ";
            msg += "does it exist?";
            throw std::invalid_argument(msg);
        }
        extract(
            file_path,
            process,
            store::store_fs_factory(store),
            verbosity
        );
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // @docstart README.md
    //
    // ### Multiple files, `store` templated out
    // ```
    /**
     * @brief
     * Process multiple files with one function call. It simply loops over
     * the texts. `store` is templated.
     * @param file_paths
     * One or more file paths to process.
     * @param process
     * See documents for functions that process only a single file.
     * @param store
     * Templated, see documents for functions that process only a single file.
     * @param verbosity
     * For debugging.
    */
    template<typename T>
    void extract(
        const std::vector<std::string>&
            file_paths,
        const process::process_type&
            process = process::process_markdown,
        const T&
            store = "./tebex_output/",
        const int&
            verbosity = 0
    )
    // ```
    //
    // @docstop README.md
    {
        for (std::string file_path : file_paths) {
            extract(
                file_path,
                process,
                store,
                verbosity
            );
        }
    }
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------

} // namespace extract

#endif