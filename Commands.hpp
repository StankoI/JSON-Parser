#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "JSONFile.hpp"

class Commands
{
private:
    JSONBase *object;
    bool is_already_opened;
    std::string nameOfOpenedFile;

public:
    Commands();

    void interpretator(); 

    void commandHelp();

    void commandOpen(const std::string& command);

    void commandSet(const std::string& command);

    void commandCreate(const std::string& commad);

    void commandSave(const std::string& command);

    void commandDelete(const std::string& command);

    void commandSaveAs(const std::string& command);

    void commandMove(const std::string& command);

    void commandSearch(const std::string& command);

    void skipFirstPartOfCommand(const std::string& command, std::size_t& i);

    void searchByPath(const std::string& command, std::vector<std::string> &path);

    void extractPathAndString(std::vector<std::string>& path, std::string& str, const std::string& command);

    bool is_digit(const char el);

};

#endif