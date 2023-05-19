#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include "Commands.hpp"

Commands::Commands() : is_already_opened(false) {}

bool Commands::is_digit(const char el)
{
    return el >= '0' && el <= '9' || el == '-';
}

void Commands::skipFirstPartOfCommand(const std::string& command, std::size_t& i)
{   
    // for (i; command[i] != ' ' && command[i] != '<' && command[i] != '['; i++)
    // {
    // }

    // while (command[i] == ' ' || command[i] == '<')
    // {
    //     i++;
    // }

    for (i; command[i] != ' ' && command[i] != '<' && command[i] != '['; i++)
    {
    }

    while (command[i] == ' ' || command[i] == '<' || command[i] == '[')
    {
        i++;
    }
}

void Commands::extractPathAndString(std::vector<std::string> &path, std::string &str, const std::string &command)
{
    std::size_t i = 0;
    // for (i; command[i] != ' ' && command[i] != '<'; i++)
    // {
    // }

    // while (command[i] == ' ' || command[i] == '<')
    // {
    //     i++;
    // }
    this->skipFirstPartOfCommand(command, i);

    std::string pathString;
    std::string valueString;
    std::size_t j = i;
    for (j; command[j] != '<'; j++)
    {
        pathString += command[j];
    }

    for (std::size_t k = j; command[k] != '\0'; k++)
    {
        valueString += command[k];
    }

    std::string temp;

    for (std::size_t n = 0; pathString[n] != '\0'; n++)
    {
        if (pathString[n] != ' ' && pathString[n] != '>')
        {
            temp += pathString[n];
        }
        else
        {
            if (temp != "")
            {
                path.push_back(temp);
            }

            temp = "";
        }
    }

    for (std::size_t c = 0; valueString[c] != '\0'; c++)
    {
        if (valueString[c] != '<' && valueString[c] != '>')
        {
            str += valueString[c];
        }
    }

    std::reverse(path.begin(), path.end());

    if (str[0] != '{' && str[0] != '[')
    {
        if (str != "true" && str != "false" && str != "null")
        {
            if (!is_digit(str[0]))
            {
                str = "\"" + str + "\"";
            }
        }
    }
}

void Commands::searchByPath(const std::string &command, std::vector<std::string> &path)
{
    if (is_already_opened == false)
    {
        std::cout << "FILE IS NOT OPENED\n";
        return;
    }

    std::size_t i = 0;

    // for (i; command[i] != ' ' && command[i] != '<' && command[i] != '['; i++)
    // {
    // }
    this->skipFirstPartOfCommand(command, i);


    std::string temp;
    for (std::size_t j = i; command[j] != '\0'; j++)
    {
        if (command[j] != ' ' && command[j] != '>' && command[j] != ']' && command[j] != '[' && command[j] != '<')
        {
            temp += command[j];
        }
        else
        {
            if (temp != "")
            {
                path.push_back(temp);
            }

            temp = "";
        }
    }

    if (!path.empty())
    {
        std::reverse(path.begin(), path.end());
    }
}

void Commands::interpretator()
{
    std::cout << "please enter command\n";
    std::cout << '>';
    std::string mainCommand;

    getline(std::cin, mainCommand);
    std::string commandFirstPart = "";

    for (std::size_t i = 0; mainCommand[i] != ' ' && mainCommand[i] != '<' && mainCommand[i] != '\0'; i++)
    {
        commandFirstPart += mainCommand[i];
    }

    if (commandFirstPart == "help")
    {
        this->commandHelp();
    }
    else if (commandFirstPart == "open")
    {
        this->commandOpen(mainCommand);
    }
    else if (commandFirstPart == "exit")
    {
        std::cout << "exiting...\n";
        return;
    }
    else if (commandFirstPart == "print")
    {
        if (is_already_opened == false)
        {
            std::cout << "File is not open\n";
            return interpretator();
        }
        this->object->print();
    }
    else if (commandFirstPart == "set")
    {
        this->commandSet(mainCommand);
    }
    else if (commandFirstPart == "create")
    {
        this->commandCreate(mainCommand);
    }
    else if (commandFirstPart == "save")
    {
        this->commandSave(mainCommand);
    }
    else if (commandFirstPart == "saveas")
    {
        this->commandSaveAs(mainCommand);
    }
    else if (commandFirstPart == "close")
    {
        if (is_already_opened == false)
        {
            std::cout << "File is not open\n";
            return interpretator();
        }
        this->is_already_opened = false;
        delete this->object;
        this->object = nullptr;
        std::cout << "file " << this->nameOfOpenedFile << " closed successfully\n";
    }
    else if (commandFirstPart == "delete")
    {
        this->commandDelete(mainCommand);
    }
    else if (commandFirstPart == "move")
    {
        this->commandMove(mainCommand);
    }
    else if(commandFirstPart == "search")
    {
        this->commandSearch(mainCommand);
    }
    else
    {
        std::cout << "invalid command\n";
    }

    return interpretator();
}

void Commands::commandHelp()
{
    std::cout << "The following commands are supported:\n";
    std::cout << "open<file>	opens<file>\n";
    std::cout << "close		closes currently opened file\n";
    std::cout << "save		saves the currently open file\n";
    std::cout << "saveas <file> 	saves the currently open file in <file>\n";
    std::cout << "save[<path>]      writes the path in the opened file\n";
    std::cout << "saveas<file>[<path>]    writes the path to the specified file\n";
    std::cout << "help		prints this information\n";
    std::cout << "print       displays the contents of the object\n";
    std::cout << "search<key>      returns an array of all data stored under that key\n";
    std::cout << "set<path><string>      replaces the value of the specified element with the string value\n";
    std::cout << "create<path><string>     creates a new object and adds it\n";
    std::cout << "delete<path>     deletes the specified element\n";
    std::cout << "move<from><to>     every element on path <from> is moved on path <to>\n";
    std::cout << "exit		exists the program\n";
}

void Commands::commandOpen(const std::string &command)
{
    if (is_already_opened == true)
    {
        std::cout << "ALREADY OPENED\n";
        return;
    }

    JSONFile creater;
    std::size_t i = 0;
    std::string fileName;

    // for (i; command[i] != ' ' && command[i] != '<'; i++)
    // {
    // }
    // while (command[i] == ' ' || command[i] == '<')
    // {
    //     i++;
    // }
    this->skipFirstPartOfCommand(command, i);
    for (std::size_t j = i; command[j] != '\0'; j++)
    {
        if (command[j] != '>')
        {
            fileName += command[j];
        }
    }

    JSONFile validCheck;
    std::ifstream isTest(fileName);

    if(!validCheck.validate(isTest))
    {
        std::cout << "file is not valid\n";
        return;
    }
    isTest.close();

    std::ifstream is(fileName);

    if (is)
    {
        this->is_already_opened = true;
        this->object = creater.create(is);
        std::cout << "successfully opened " << fileName << '\n';
        is.close();
        this->nameOfOpenedFile = fileName;
    }
    else
    {
        std::cout << "file " << fileName << " could not be opened please try again\n";
    }
}

void Commands::commandSet(const std::string &command)
{

    if (is_already_opened == false)
    {
        std::cout << "FILE IS NOT OPENED\n";
        return;
    }
    std::vector<std::string> path;
    std::string str;

    this->extractPathAndString(path, str, command);

    object->set(path, str);
}

void Commands::commandCreate(const std::string &command)
{
    if (is_already_opened == false)
    {
        std::cout << "FILE IS NOT OPENED\n";
        return;
    }
    std::vector<std::string> path;
    std::string str;

    this->extractPathAndString(path, str, command);

    object->create(path, str);
}

void Commands::commandSave(const std::string &command)
{
    std::vector<std::string> path;
    this->searchByPath(command, path);
    std::ofstream os(this->nameOfOpenedFile);
    this->object->saves(path, os);
    os.close();
}

void Commands::commandSaveAs(const std::string &command)
{
    if (is_already_opened == false)
    {
        std::cout << "FILE IS NOT OPENED\n";
        return;
    }

    std::vector<std::string> path;
    std::string fileName;

    std::size_t i = 0;

    // for (i; command[i] != ' ' && command[i] != '<' && command[i] != '['; i++)
    // {
    // }

    // while (command[i] == ' ' || command[i] == '<' || command[i] == '[')
    // {
    //     i++;
    // }

    this->skipFirstPartOfCommand(command, i);
    size_t j = i;
    for (j; command[j] != '>'; j++)
    {
        fileName += command[j];
    }

    // std::cout << fileName << '\n';
    std::string temp;

    for (std::size_t k = j; command[k] != '\0'; k++)
    {
        if (command[k] != ' ' && command[k] != '>' && command[k] != '<' && command[k] != '[' && command[k] != ']')
        {
            temp += command[k];
        }
        else
        {
            if (temp != "")
            {
                path.push_back(temp);
            }
            temp = "";
        }
    }

    if (!path.empty())
    {
        std::reverse(path.begin(), path.end());
    }

    std::ofstream os(fileName);
    if(os)
    {
        this->object->saves(path, os);
        os.close();
    }
    else
    {
        std::cout << fileName << " not found\n";
    }
    // this->object->saves(path, os);
    // os.close();
}

void Commands::commandMove(const std::string &command)
{
    if (is_already_opened == false)
    {
        std::cout << "you didn't open a file\n";
        return;
    }
    std::vector<std::string> from;
    std::vector<std::string> to;

    std::size_t i = 0;
    // for (i; command[i] != ' ' && command[i] != '<'; i++)
    // {
    // }

    // while (command[i] == ' ' || command[i] == '<')
    // {
    //     i++;
    // }
    this->skipFirstPartOfCommand(command, i);
    std::string temp;

    std::size_t j = i;
    for (j; command[j] != '<'; j++)
    {
        if (command[j] != ' ' && command[j] != '>')
        {
            temp += command[j];
        }
        else
        {
            if (temp != "")
            {
                from.push_back(temp);
            }
            temp = "";
        }
    }

    temp = "";

    for (std::size_t k = j; command[k] != '\0'; k++)
    {
        if (command[k] != ' ' && command[k] != '>' && command[k] != '<')
        {
            temp += command[k];
        }
        else
        {
            if (temp != "")
            {
                to.push_back(temp);
            }
            temp = "";
        }
    }

    if(from.empty())
    {
        std::cout << "path <from> is empty\n";
    }
    else
    {
        std::reverse(from.begin(), from.end());
    }

    if(to.empty())
    {
        std::cout << "path <to> is empty\n";
    }
    else
    {
        std::reverse(to.begin(), to.end());
    }

    this->object->move(from,to);


}

void Commands::commandSearch(const std::string& command)
{
    if (is_already_opened == false)
    {
        std::cout << "you didn't open a file\n";
        return;
    }
    
    std::size_t i = 0;
    std::string key;
    
    // for (i; command[i] != ' ' && command[i] != '<' && command[i] != '['; i++)
    // {
    // }

    // while (command[i] == ' ' || command[i] == '<' || command[i] == '[')
    // {
    //     i++;
    // }

    this->skipFirstPartOfCommand(command, i);

    
    for(std::size_t j = i; command[j] != '\0'; j++)
    {
        if(command[j] != ' ' && command[j] != '>')
        {
            key += command[j]; 
        }
    }

    std::cout << key << ":[\n";
    object->search(key);
    std::cout << "]\n"; 
    
}

void Commands::commandDelete(const std::string &command)
{
    std::vector<std::string> path;
    this->searchByPath(command, path);
    this->object->delete_element(path);
}

int main()
{
    Commands a;
    a.interpretator();


    return 0;
}