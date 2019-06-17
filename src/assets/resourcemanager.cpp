#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <SFML/Graphics/Font.hpp>

#include "resourcemanager.h"



///////////////////////////////////////////////////////////////////////////////
ResourceManager::ResourceManager()
{
    //ctor
}


///////////////////////////////////////////////////////////////////////////////
ResourceManager::~ResourceManager()
{
    unload();
}


///////////////////////////////////////////////////////////////////////////////
bool ResourceManager::loadFont(sf::String filepath, sf::String resourcename)
{
    if (m_fontmap.find(resourcename) != m_fontmap.end())
        return true;

    sf::Font* newresource = new sf::Font();

    if (newresource && newresource->loadFromFile(filepath))
    {
        if (m_fontmap.emplace(resourcename, newresource).second)
        {
            return true;
        }
    }

    if (newresource)
        delete newresource;

#ifdef DEBUG
    std::cerr << "[Warning] Couldn't load <" << filepath.toAnsiString() << ">" << std::endl;
#endif // DEBUG

    return false;
}


///////////////////////////////////////////////////////////////////////////////
sf::Font* ResourceManager::getFont(sf::String resourcename)
{
    auto find = m_fontmap.find(resourcename);

    if (find != m_fontmap.end())
        return find->second;

    return nullptr;
}


///////////////////////////////////////////////////////////////////////////////
ResourceManager* ResourceManager::getInstance()
{
    static ResourceManager rsmgr;

    return &rsmgr;
}


///////////////////////////////////////////////////////////////////////////////
void ResourceManager::unload()
{
    ResourceManager::FontMap::iterator it;

    for ( auto it = m_fontmap.begin(); it != m_fontmap.end(); ++it )
    {
        delete it->second;
    }

    m_fontmap.clear();
}


