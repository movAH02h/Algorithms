#include <iostream>
#include <string>
#include <vector>

enum class Month {January = 0, February, March, April, May, June, July, August, September, October, November, December};

int main()
{
    int celebrations; int year;
    std::cin >> celebrations;
    std::cin >> year;
    std::vector<std::pair<int, std::string>> day_month;

    for (int i = 0; i < celebrations; ++i)
    {
        int day; std::string month;
        std::cin >> day >> month;

    }


	return 0;
}
