#ifndef MULTIPLEMARKERS_MAIN_HPP
#define MULTIPLEMARKERS_MAIN_HPP

#include "CVector.h"
#include "CMenuManager.h"

class multiplemarkers {
public:
    multiplemarkers();
    ~multiplemarkers();

    int  add(CMenuManager *manager, CVector pos);
    void remove(CMenuManager *manager, int blip);
    void on_mark(CMenuManager *manager);

private:
    std::vector<int> blips;
};

inline multiplemarkers main_plugin;

#endif // MULTIPLEMARKERS_MAIN_HPP