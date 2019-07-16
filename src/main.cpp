#include "app/app.h"
#include "misc/typedefs.h"



int main()
{
#ifdef DEBUG
    sfSpace::testSizes();
#endif // DEBUG

    App app(800 ,600 ,"Space Simulator");

    app.run();

    return 0;
}
