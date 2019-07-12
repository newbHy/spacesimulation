#include <iostream>
#include "cerrredirect.h"



///////////////////////////////////////////////////////////////////////////////
CerrRedirect::CerrRedirect() : cerrbuf(nullptr)
{
    out.open("messages.txt", std::ofstream::out | std::ofstream::app);
    if (out.is_open())
    {
        cerrbuf = std::cerr.rdbuf(); //save old buf
        std::cerr.rdbuf(out.rdbuf()); //redirect std::cerr to out.txt!
    }
    else
    {
        std::cerr << "[Warning] Couldn't open <message.txt>" << std::endl;
    }
}


///////////////////////////////////////////////////////////////////////////////
CerrRedirect::~CerrRedirect()
{
    if (cerrbuf)
        std::cerr.rdbuf(cerrbuf); //reset to standard output again
}
