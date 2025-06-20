#include "error.h"

Error::Error()
{
    type = NO_DEFINED;
    pos = -1;
    error_strings = {};
}


Error::Error(ErrorType _type, int _pos, QStringList _error_strings)
{
    type = _type;
    pos = _pos;
    error_strings = _error_strings;
}

