#pragma once

#include "menu.hpp"

namespace mmh
{
    const MenuItem* show_menu(const MenuItem* current);
    const MenuItem* exit(const MenuItem* current);

    const MenuItem* study_prog_lang(const MenuItem* current);
    const MenuItem* study_algorithms(const MenuItem* current);
    const MenuItem* study_other_technologies(const MenuItem* current);
    const MenuItem* study_go_back(const MenuItem* current);

    const MenuItem* data_base(const MenuItem* current);
    const MenuItem* multistream_prog(const MenuItem* current);
    const MenuItem* web_tech(const MenuItem* current);
    const MenuItem* other_go_back(const MenuItem* current);

}
