#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "value.hpp"

namespace rana {

class parse_error : public std::runtime_error
{
public:
    parse_error(std::size_t line, std::size_t column, const char *buffer, std::size_t buffer_length, const std::string &message);
private:
    static std::string create_message(std::size_t line, std::size_t column, const char *buffer, std::size_t buffer_length, const std::string &message);
};
    
class parser
{
public:
    static value parse_string(const std::string &string);
    static value parse_file(const std::string &filename);
    
    parser();
    ~parser();
    
    void parse_next(value &result);
    void set_buffer(const char *buffer, std::size_t buffer_length);
    
private:
    void handle_structural_token(char c);
    value parse_token();
    value parse_number();
    value parse_literal();
    std::string parse_string();
    bool scan(char c);
    parse_error make_error(const std::string &message);
    void push_array();
    void push_object();
    void push_token();
    value &top();
    
    const char *buffer_;
    std::size_t buffer_length_;
    std::size_t buffer_position_;
    std::vector<value *> stack_;
    std::size_t line_;
    std::size_t column_;
    std::string token_string_;
    value *root_;
    std::pair<bool, std::string> key_;
    bool popped_container_;
    std::pair<uint32_t, uint32_t> surrogate_pair_;
    std::size_t unicode_nibble_;
    
    enum class state
    {
        normal,
        string,
        string_escape,
        unicode
    };
    
    state state_;
};

inline value from_file(const std::string &filename)
{
    return parser::parse_file(filename);
}

} // namespace rana
