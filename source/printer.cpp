#include "printer.hpp"

namespace rana {

printer::printer() : encoding_(rana::encoding::utf8), indent_(true), indent_length_(4), space_before_(true), space_after_(true)
{
}

} // namespace rana
