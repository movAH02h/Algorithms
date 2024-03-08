#include <iostream>
#include <string>

int main()
{
    std::string str;
    std::cin >> str;

    char last_symbol = str[0];
    int last_index = 0;
    std::string answer;

    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] != last_symbol)
        {
            if (i - last_index > 1)
            {
                answer += (last_symbol + std::to_string(i - last_index));
            }
            else
            {
                answer += last_symbol;
            }
            last_symbol = str[i];
            last_index = i;
        }
    }

    if (str.size() - last_index > 1)
    {
        answer += (last_symbol + std::to_string(str.size() - last_index));
    }
    else
    {
        answer += last_symbol;
    }
    std::cout << answer;
    return 0;
}
