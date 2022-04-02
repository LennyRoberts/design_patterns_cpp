#include <iostream>

#include "factory_method.h"
#include "abstract_factory.h"
#include "builder.h"
#include "prototype.h"
#include "singleton.h"

using namespace std;

int main(int argc, char *argv[ ])
{

    cout << "------------------------------------------------Factory_Method-------------------------------------------------------" << endl;
    MainFactoryMethod();
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "------------------------------------------------Abstract_Factory-----------------------------------------------------" << endl;
    MainAbstractFactory();
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    return 0;
}
