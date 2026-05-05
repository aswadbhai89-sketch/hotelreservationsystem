#include "HotelException.h"

HotelException::HotelException(string msg)
{
    message = msg;
}

string HotelException::what()
{
    return message;
}

HotelException::~HotelException()
{
}