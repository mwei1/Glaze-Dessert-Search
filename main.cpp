//
// Created by lawre on 3/2/2026.
//
#include <iostream>
#include <optional>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "CSVReader.h"
#include <vector>
#include "Trie.h"

using namespace std;

void musicSwitch(sf::Music& music, sf::Sprite& spr, sf::Texture& mute, sf::Texture& unmute)
{
    if (music.getStatus() == sf::Sound::Status::Playing)
    {
        music.pause();
        spr.setTexture(mute);
    }
    else
    {
        music.play();
        spr.setTexture(unmute);
    }
}

int main() {
    sf::Color backgroundColor(245, 228, 218);
    sf::Color titleColor(254, 136, 150);
    sf::Color subtitleColor(254, 147, 152);
    sf::Color accent(211, 101, 130);

    sf::FloatRect sizeRect; //for text resizing/centering

    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Dessert Search");
    window.clear(backgroundColor);

    //load window icon
    sf::Image icon;
    icon.loadFromFile("resources/images/taskbar_icon.png");
    window.setIcon(icon.getSize(), icon.getPixelsPtr());

    //load music!!!  French Accordion Waltz Paris Atmosphere by Denis Pavlov Music
    //https://pixabay.com/music/france-french-accordion-waltz-paris-atmosphere-477503/
    sf::Music music("resources/audio/Music.mp3");
    music.setLooping(true);
    //music.play();

    //music mute button
    sf::Texture unmuted;
    unmuted.loadFromFile("resources/images/unmute.png");

    sf::Texture muted;
    muted.loadFromFile("resources/images/mute.png");

    sf::Sprite toggleMusic(unmuted);
    toggleMusic.setScale(sf::Vector2f(0.2, 0.2));
    toggleMusic.setPosition({0.f, 750.f});

    //beautiful donut
    sf::Texture donut;
    donut.loadFromFile("resources/images/quirky_donut.png");
    sf::Sprite quirkyDonut(donut);
    quirkyDonut.setScale(sf::Vector2f(0.09, 0.09));
    sizeRect = quirkyDonut.getLocalBounds();
    quirkyDonut.setOrigin(sizeRect.getCenter());
    quirkyDonut.setPosition({0.f + quirkyDonut.getGlobalBounds().size.x / 2.0f, 130.f + quirkyDonut.getGlobalBounds().size.y / 2.0f});

    //load fonts
    const sf::Font title("resources/fonts/ButterGarlic.ttf");
    const sf::Font subtitle("resources/fonts/Million Dreams.otf");
    const sf::Font text("resources/fonts/Martel-Light.ttf");

    //title
    sf::Text text1(title,"Welcome to Dessert Searcher!", 60);
    text1.setFillColor(titleColor);
    text1.setOutlineThickness(2);
    text1.setOutlineColor(accent);
    sizeRect = text1.getLocalBounds();
    text1.setOrigin({sizeRect.getCenter()});
    text1.setPosition({600, 75});

    //subtitle
    sf::Text text2(subtitle, "Search for a Dessert Below", 40);
    text2.setFillColor(subtitleColor);
    sizeRect = text2.getLocalBounds();
    text2.setOrigin({sizeRect.getCenter()});
    text2.setPosition({600, 140});

    //search box
    string query = "";
    sf::Text searchBar(text, "WELCOME HELP ME", 30);
    searchBar.setFillColor(sf::Color::Black);
    sizeRect = searchBar.getLocalBounds();
    searchBar.setOrigin({sizeRect.getCenter()});
    searchBar.setPosition({600, 200});

    sf::RectangleShape bar({600.f, 40.f});
    bar.setOrigin({300.f, 20.f});
    bar.setPosition({600, 200});
    bar.setOutlineThickness(2.f);


    vector<Recipe> recipes = CSVReader::loadRecipesFromFile("resources/recipes.csv");
    cout << recipes.size() << "\n\n";

    Trie t;
    for (int i=0;i<recipes.size();i++) {
        t.insert(recipes[i].name, i);
    }




    while (window.isOpen())
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (toggleMusic.getGlobalBounds().contains(mousePos))
            toggleMusic.setScale(sf::Vector2f(0.18, 0.18));
        else
            toggleMusic.setScale(sf::Vector2f(0.2, 0.2));

        if (quirkyDonut.getGlobalBounds().contains(mousePos))
        {
            quirkyDonut.setScale(sf::Vector2f(0.085, 0.085));
            quirkyDonut.rotate(sf::degrees(0.1));
        }
        else
            quirkyDonut.setScale(sf::Vector2f(0.089, 0.089));


        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonReleased>())
            {
                if (toggleMusic.getGlobalBounds().contains(mousePos))
                    musicSwitch(music, toggleMusic, muted, unmuted);
            }
        }

        window.clear(backgroundColor);

        window.draw(toggleMusic);
        window.draw(quirkyDonut);

        window.draw(text1);
        window.draw(text2);

        window.draw(bar);
        window.draw(searchBar);

        window.display();
    }

    return 0;
}

