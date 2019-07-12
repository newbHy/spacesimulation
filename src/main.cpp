#include "app.h"
#include "typedefs.h"



int main()
{
#ifdef DEBUG
    sfSpace::testSizes();
#endif // DEBUG

    App app(800,600,"Space Simulator");

    app.run();

    return 0;
}
