#pragma once

#include <cstddef>
#include <string>
#include "./CMenuItem.h"



class CMenu {
    public:
        CMenu(std::string, CMenuItem *, size_t);
        int getSelect() const;
        bool isRun() const;
        std::string getTitle();
        size_t getCount() const;
        CMenuItem *getItems();
        void print();
        int runCommand();

    private:
        int select{-1};
        size_t count{};
        bool running{};
        std::string title{};
        CMenuItem *items{};
};