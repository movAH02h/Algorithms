#include "functions.h"

std::vector<const char*>::iterator mystd::find(std::vector<const char*>& strings, const char* target)
{
    auto beg = strings.begin();
    auto en = strings.end();
    while (beg != en)
    {
        if (!strcmp(target, *beg)) return beg;
        beg++;
    }
    return en;
}

int write_to_file(const char* file_read, const char* file_write)
{
    std::fstream read(file_read, std::ios::in);
    if (!read.is_open())
    {
        std::cout << "Error of opening file!" << std::endl;
        return 0;
    }
    std::fstream write(file_write, std::ios::out | std::ios::app);

    std::string temp_str;
    while (getline(read, temp_str))
    {
        write << temp_str << "\n";
    }

    read.close();
    write.close();

    return 1;
}
int print_file(const char* file_name)
{
    std::fstream file_read(file_name, std::ios::in);

    if (file_read.is_open())
    {
        std::string temp_str;
        while (getline(file_read, temp_str))
        {
            file_read >> temp_str;
            std::cout << temp_str << std::endl;
        }
    }

    file_read.close();
    std::cerr << "Error with opening file!";
    return 0;
}

int do_option_to_file(const char* name_file, const char* name_option)
{
    std::fstream file_read(name_file, std::ios::in);
    if (!strcmp(name_option, "-b"))
    {
        if (file_read.is_open())
        {
            int count_row = 1; std::string temp_str;

            while (getline(file_read, temp_str))
            {
                if (temp_str != "")
                {
                    std::cout << count_row << " " << temp_str << "\n";
                    count_row++;
                }
                else
                {
                    std::cout << temp_str << "\n";
                }
            }
            file_read.close();
            return 1;
        }
        else
        {
            std::cerr << "Can't open the file!" << std::endl;
            return 0;
        }

    }
    else if (!strcmp(name_option, "-n"))
    {
        if (file_read.is_open())
        {
            int count_row = 1; std::string temp_str;

            while (getline(file_read, temp_str))
            {
                std::cout << count_row << " " << temp_str << "\n";
                count_row++;

            }
            file_read.close();
            return 1;
        }
        else
        {
            std::cerr << "Can't open the file!" << std::endl;
            return 0;
        }
    }
    else if (!strcmp(name_option, "-e"))
    {
        if (file_read.is_open())
        {
            std::string temp_str;

            while (getline(file_read, temp_str))
        {
                std::cout << temp_str << "$" << "\n";
            }
            file_read.close();
            return 1;
        }
        else
        {
            std::cerr << "Can't open the file!" << std::endl;
            return 0;
        }
    }
    else if(!strcmp(name_option, "-s"))
    {
        if (file_read.is_open())
        {
            std::string temp_str; int space_flag = false;

            while (getline(file_read, temp_str))
            {
                if (temp_str == "")
                {
                    if (space_flag == false)
                    {
                        std::cout << temp_str << "\n";
                        space_flag = true;
                    }
                }
                else
                {
                    std::cout << temp_str << "\n";
                    space_flag = false;
                }
            }
            file_read.close();
            return 1;
        }
        else
        {
            std::cerr << "Can't open the file!" << std::endl;
            return 0;
        }
    }

    file_read.close();
    std::cerr << "Undefined option!" << "\n";
    return 0;
}

