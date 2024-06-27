#include "database.h"

int main()
{
    Database& d1 = Database::get();
    std::cout << d1.getName() << std::endl;  // default "Jef"
    d1.setName("Jan");
    std::cout << d1.getName() << std::endl;  // "Jan"

    Database& d2 = Database::get();
    std::cout << d2.getName() << std::endl;  // still "Jan", not default "Jef"

    d2.setName("Robert");
    std::cout << d2.getName() << std::endl;  // "Robert"
    std::cout << d1.getName() << std::endl;  // also "Robert"

    return 0;
}
