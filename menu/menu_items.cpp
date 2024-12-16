#include "menu_items.hpp"
#include "menu_functions.hpp"

const mmh::MenuItem mmh::DATA_BASE = {
    "1 - базы данных", mmh::data_base, &mmh::STUDY };
const mmh::MenuItem mmh::MULTISTREAM_PROG = {
    "2 - многопоточное программирование", mmh::multistream_prog, &mmh::STUDY };
const mmh::MenuItem mmh::WEB_TECH = {
    "3 - сетевые технологии", mmh::web_tech, &mmh::STUDY };
const mmh::MenuItem mmh::OTHER_GO_BACK = {
    "0 - выход в предыдущее меню", mmh::other_go_back, &mmh::STUDY };

namespace
{
    const mmh::MenuItem* other_children[] = {
        &mmh::OTHER_GO_BACK,
        &mmh::DATA_BASE,
        &mmh::MULTISTREAM_PROG,
        &mmh::WEB_TECH };
    const int other_size = sizeof(other_children) / sizeof(other_children[0]);
}

const mmh::MenuItem mmh::STUDY_PROG_LANG = {
    "1 - изучать языки программирования", mmh::study_prog_lang, &mmh::STUDY };
const mmh::MenuItem mmh::STUDY_ALGORITHMS = {
    "2 - алгоритмы и структуры", mmh::study_algorithms, &mmh::STUDY };
const mmh::MenuItem mmh::STUDY_OTHER_TECHNOLOGIES = {
    "3 - другие технологии", mmh::study_other_technologies, &mmh::STUDY, other_children, other_size};
const mmh::MenuItem mmh::STUDY_GO_BACK = {
    "0 - выйти в главное меню", mmh::study_go_back, &mmh::STUDY };

namespace
{
    const mmh::MenuItem* study_children[] = {
        &mmh::STUDY_GO_BACK,
        &mmh::STUDY_PROG_LANG,
        &mmh::STUDY_ALGORITHMS,
        &mmh::STUDY_OTHER_TECHNOLOGIES };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const mmh::MenuItem mmh::STUDY = {
    "1 - изучать программирование", mmh::show_menu, &mmh::MAIN, study_children, study_size };
const mmh::MenuItem mmh::EXIT = {
    "0 - пойти играть в футбол", mmh::exit, &mmh::MAIN };

namespace
{
    const mmh::MenuItem* main_children[] = {
        &mmh::EXIT,
        &mmh::STUDY };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const mmh::MenuItem mmh::MAIN = {
    nullptr, mmh::show_menu, nullptr, main_children, main_size };
