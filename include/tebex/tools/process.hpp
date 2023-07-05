#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <vector>
#include <regex>
#include <functional>

#include "misc_utils.hpp"
#include "args.hpp"

namespace process{
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    typedef
    std::function<
        void(
            const std::string&  line,
            std::string&        out_block_type,
            std::string&        out_key,
            bool&               out_storeable,
            std::string&        out_line
        )
    >
    process_type;

    process_type process_markdown =
        []
        (
            const std::string&  line,
            std::string&        out_block_type,
            std::string&        out_key,
            bool&               out_storeable,
            std::string&        out_line
        ) -> void
        {
            // this default function extracts sections from .md files.
            std::regex re("^[ ]*(#+)[ ]*(.+)$");
            std::vector<std::string> e = utils::re_extract_groups(
                line,
                re
            );
            if (e.size() > 0) {
                out_block_type = "start-only";
                out_key = e[1];
                out_storeable = false;
                out_line = "";
            } else {
                out_block_type = "";
                out_key = "";
                out_storeable = true;
                out_line = line;
            }
        };

    process_type process_comment_blocks_factory(
        std::regex
            single_re = std::regex("^[ ]*/{2,}.*$"),
        std::regex
            multi_start_re = std::regex("^[ ]*/[*].*$"),
        std::regex
            multi_stop_re = std::regex("^[ ]*[*]/.*$"),
        std::regex
            tag_key_re = std::regex("^[ /*]*@([a-zA-Z_0-9]+)[ ]*(.+)$"),
        std::regex
            clean_re = std::regex("^[ ]*[/*]+"),

        std::vector<std::string>
            start_only_tags = {"@doc"},
        std::vector<std::string>
            start_tags = {"@docstart"},
        std::vector<std::string>
            stop_tags = {"@docstop"},
        std::vector<std::string>
            boundary_tags = {"@docboundary"}
    ) {
    bool __in_multiline_comment_block = false;

    return
        [&]
        (
            const std::string&
                line,
            std::string&
                out_block_type,
            std::string&
                out_key,
            bool&
                out_storeable,
            std::string&
                out_line
        ) -> void
        {
            // @TODO TODO.md
            // process_comment_blocks_factory: Figure out a way to set
            // out_storeable = true when using @start-@stop tags even for
            // lines that are not comment lines. Maybe a separate call
            // of tebex::extract::extract?
            // 
            // Need to also be able to stop when a start-only block's last
            // comment line has been reached. So, need to keep track of when
            // in_comment_block (globally?) and to deactivate start-only keys
            // when in_comment_block turns from true to false.
            bool in_comment_block = false;
            if (__in_multiline_comment_block) {
                __in_multiline_comment_block = !utils::re_detect(
                    line, multi_stop_re
                );
                in_comment_block = __in_multiline_comment_block;
            } else {
                __in_multiline_comment_block = utils::re_detect(
                    line, multi_start_re
                );
                in_comment_block = __in_multiline_comment_block;
                if (!__in_multiline_comment_block) {
                    
                    bool in_singleline_comment_block = utils::re_detect(
                        line, single_re
                    );
                    in_comment_block = in_singleline_comment_block;
                }
            }
            
            if (in_comment_block) {
                std::vector<std::string> extracted = utils::re_extract_groups(
                    line,
                    tag_key_re
                );
                if (extracted.size() > 0) {
                    std::string tag = extracted[0];
                    std::string key = extracted[1];
                    std::string block_type = "";
                    if (utils::is_in(tag, start_only_tags)) {
                        block_type = "start-only";
                    } else if (utils::is_in(tag, start_tags)) {
                        block_type = "start-stop";
                    } else if (utils::is_in(tag, stop_tags)) {
                        // this is strictly not necessary because the key
                        // is already active and will be deactivated
                        // because it has appeared a second time.
                        block_type = "start-stop";
                    } else if (utils::is_in(tag, boundary_tags)) {
                        block_type = "boundary";
                    }
                    out_block_type = block_type;
                    out_key = key;
                    out_storeable = false;
                    out_line = "";
                } else {
                    out_block_type = "";
                    out_key = "";
                    out_storeable = true;
                    out_line = std::regex_replace(line, clean_re, "");
                }
            }
        };
    }
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
} // namespace process

#endif
