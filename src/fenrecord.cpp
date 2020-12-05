#include "cmdsuzdal/fenrecord.h"

namespace cSzd
{
    const std::string_view FENRecord::piecePlacement() const
    {
        return std::string_view {fen.c_str(), fen.find_first_of(FENDelim)};
    }

} // namespace cSzd