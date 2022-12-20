#include "../2022/Day20_2022.h"



void AOC22::Day20::Decode(const std::vector<Day20Item>& order, std::vector<Day20Item>& message)
{
	long long int modulus = message.size();
	for (int i = 0; i < modulus; i++)
	{
		long long int move = order[i].Value;
		if (move == 0)
		{
			continue;
		}

		long long int identifier = order[i].Id;
		long long int currentIndex = std::find_if(message.begin(), message.end(), [&id = identifier](const Day20Item& other) -> bool {return id == other.Id; }) - message.begin();
		auto item = message[currentIndex];
		
		long int newIndex = (currentIndex + move) % (modulus - 1);

		if (0 < newIndex and newIndex < (modulus - 1))
		{
		}
		else if (newIndex <= 0)
		{
			newIndex += (modulus - 1);
		}
		else if (newIndex >= (modulus - 1))
		{
			newIndex -= (modulus - 1);
		}

		message.erase(message.begin() + currentIndex);
		message.insert(message.begin() + newIndex, { item });
	}
}

AOC22::Day20::Day20() : Day("Input//2022//day20_data.txt", "Input//2022//day20_data_simple.txt")
{
}

void AOC22::Day20::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	std::vector<Day20Item> order;
	int i = 0;
	for (std::string row; input.NextRow(row); i++)
	{
		Day20Item item;
		item.Id = i;
		item.Value = std::stoll(row);
		order.push_back(item);
	}
	
	std::vector<Day20Item> message = order;

	Decode(order, message);

	auto itterator = std::find_if(message.begin(), message.end(), [](const Day20Item& o) ->  bool { return 0 == o.Value; }) - message.begin();

	Day20Item a = message[(itterator + 1000) % message.size()];
	Day20Item b = message[(itterator + 2000) % message.size()];
	Day20Item c = message[(itterator + 3000) % message.size()];

	printf("1) (%lli)\n", a.Value + b.Value + c.Value);
}

void AOC22::Day20::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);
	const long long int decryptionKey = 811589153;

	std::vector<Day20Item> order;
	int i = 0;
	for (std::string row; input.NextRow(row); i++)
	{
		Day20Item item;
		item.Id = i;
		item.Value = std::stoll(row) * decryptionKey;
		order.push_back(item);
	}

	std::vector<Day20Item> message = order;

	for (int i = 0; i < 10; i++)
	{
		Decode(order, message);
	}

	auto itterator = std::find_if(message.begin(), message.end(), [](const Day20Item& o) ->  bool { return 0 == o.Value; }) - message.begin();

	Day20Item a = message[(itterator + 1000) % message.size()];
	Day20Item b = message[(itterator + 2000) % message.size()];
	Day20Item c = message[(itterator + 3000) % message.size()];

	printf("2) (%lli)\n", a.Value + b.Value + c.Value);
}

AOC22::Day20::~Day20()
{

}
