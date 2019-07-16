#ifndef CERRREDIRECT_H
#define CERRREDIRECT_H

#include <fstream>



// Automatically redirects the std::cerr stream to a file stream
// and reverses this as soon as this object is destroyed.
class CerrRedirect
{
    public:
        CerrRedirect();
        virtual ~CerrRedirect();

        CerrRedirect(const CerrRedirect& rhs) = delete;
        CerrRedirect& operator=(const CerrRedirect& rhs) = delete;

    private:
        // Used to redirect standard output
        std::streambuf* m_cerrbuf;
        std::ofstream   m_out;
};

#endif // CERRREDIRECT_H
