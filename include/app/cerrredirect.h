#ifndef CERRREDIRECT_H
#define CERRREDIRECT_H

#include <fstream>



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
