#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>

#include <SFML/System/String.hpp>



namespace sf
{
    class Font;
}

class ResourceManager
{
    public:
        typedef std::unordered_map<std::string, sf::Font*> FontMap;

        virtual ~ResourceManager();

        bool loadFont(sf::String filepath, sf::String resourcename);

        sf::Font* getFont(sf::String resourcename);

        static ResourceManager* getInstance();

    protected:

    private:
        ResourceManager();

        void unload();

        FontMap m_fontmap;
};

#endif // RESOURCEMANAGER_H
