#include "menu_functions.hpp"
#include <cstdlib>
#include <iostream>

const mmh::MenuItem* mmh::show_menu(const MenuItem* current)
{
    for (int i = 1; i < current->children_count; i++)
    {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Ввод: > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    return current->children[user_input];
}

const mmh::MenuItem* mmh::exit(const MenuItem* current)
{
    std::exit(0);
}

const mmh::MenuItem* mmh::study_prog_lang(const MenuItem* current)
{
    std::cout << current->title << std::endl
        << std::endl;
    return current->parent;
}

const mmh::MenuItem* mmh::study_algorithms(const MenuItem* current)
{
    std::cout << current->title << std::endl
        << std::endl;
    return current->parent;
}

const mmh::MenuItem* mmh::go_back(const MenuItem* current)
{
    std::cout << current->title << std::endl
        << std::endl;
    return current->parent->parent;
}

const mmh::MenuItem* mmh::multistream_prog(const MenuItem* current)
{
    std::cout << current->title << std::endl
        << std::endl;
    return current->parent->parent;
}
const mmh::MenuItem* mmh::web_tech(const MenuItem* current)
{
    std::cout << current->title << std::endl
        << std::endl;
    return current->parent->parent;
}
const mmh::MenuItem* mmh::data_base(const MenuItem* current)
{
    std::cout << current->title << std::endl
        << std::endl;
    return current->parent->parent;
}