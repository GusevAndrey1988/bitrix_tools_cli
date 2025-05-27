#include "application.h"

int main(int argc, const char *argv[])
{
    using namespace bitrix_tools;

    return Application{argc, argv}.run();
}