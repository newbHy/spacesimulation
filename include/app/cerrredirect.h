#ifndef CERRREDIRECT_H
#define CERRREDIRECT_H

#include <fstream>



// Automatically redirects the std::cerr output stream to
// a file stream and reverses this as soon as this object
// is destroyed.
class CerrRedirect
{
    public:
        CerrRedirect();
        virtual ~CerrRedirect();

    private:
        // used to redirect standard output
        std::streambuf* cerrbuf;
        std::ofstream   out;
};

#endif // CERRREDIRECT_H
