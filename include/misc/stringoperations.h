#ifndef STRINGOPERATIONS_H_INCLUDED
#define STRINGOPERATIONS_H_INCLUDED

#include <sstream>

#include <SFML/Graphics/Text.hpp>


////////////////////////////////////////////////////////////////////////////////
// note: https://stackoverflow.com/questions/16605967/set-precision-of-stdto-string-when-converting-floating-point-values
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}


////////////////////////////////////////////////////////////////////////////////
inline void setOriginTopLeft(sf::Text& text)
{
    text.setOrigin( text.getLocalBounds().left, text.getLocalBounds().top);
}

#endif // STRINGOPERATIONS_H_INCLUDED
