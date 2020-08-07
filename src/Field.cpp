#include "Field.hpp"

////------------------------------------------------
std::ostream& operator << ( std::ostream& strm, const Field& field ){
    strm << '[' << (field.flaged() ? 'f' : '_') << (field.covered() ? 'c' : 'u')
         << ';' << (int) field.val() << ']';
    return strm;
}
