#pragma once

namespace rana {
    
enum class encoding
{
    utf8,
    latin1,
    ascii
};

} // namespace rana

#include "value.hpp"
#include "parser.hpp"
#include "printer.hpp"