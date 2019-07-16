#include "app/cerrredirect.h"

#include <iostream>



////////////////////////////////////////////////////////////////////////////////
CerrRedirect::CerrRedirect()
  : m_cerrbuf(nullptr),
    m_out("messages.txt", std::ofstream::out | std::ofstream::app)
{
    if (m_out.is_open())
    {
        m_cerrbuf = std::cerr.rdbuf(); //save old buf
        std::cerr.rdbuf(m_out.rdbuf()); //redirect std::cerr to out.txt!
    }
    else
    {
        std::cerr << "[Warning] Couldn't open <message.txt>" << std::endl;
    }
}


////////////////////////////////////////////////////////////////////////////////
CerrRedirect::~CerrRedirect()
{
    if (m_cerrbuf)
        std::cerr.rdbuf(m_cerrbuf); //reset to standard output again

    if (m_out.is_open())
        m_out.close();
}
