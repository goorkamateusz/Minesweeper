#include "Field.hpp"

////------------------------------------------------
std::ostream& operator << ( std::ostream& strm, const Field& field ){
    strm << '[' << (field.flagged() ? 'f' : '_') << (field.covered() ? 'c' : 'u')
         << ((field.uncoverAble()) ? 'a' : '_') << (int) field.val() << ']';
    return strm;
}