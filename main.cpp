#include "HotelSystem.h"

int main()
{
    try
    {
        HotelSystem hotel;
        hotel.start();
    }
    catch (HotelException& e)
    {
        cout << "System Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error occurred.\n";
    }

    return 0;
}