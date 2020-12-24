#include "Day23_2020.h"

int AOC20::Day23::move(std::vector<int>& nextCup, int current)
{

	/*
	

	our current id is 3
	index = cup
	value = next cup
	the vector looks like this:
	nextCup[0] = 0
	nextCup[1] = 2
	nextCup[2] = 5
	nextCup[3] = 8
	nextCup[4] = 6
	nextCup[5] = 4
	nextCup[6] = 7
	nextCup[7] = 3
	nextCup[8] = 9
	nextCup[9] = 1

	this will give us
	the detatched group:
	nextCup[3] = 8
	nextCup[8] = 9
	nextCup[9] = 1

	the current (3) now need to point to the next value after the detatched group; aka nextCup[1] or 2
	nextCup[3] = 2 <--- CHANGE

	cups: (3) 2 5 4 6 7
	detatched 8 9 1

	we also need to change so that: nextCup[2] points to the first element in the detatched group aka 8.
	nextCup[2] = 8 <---- CHANGE	
	we need to attatch the end of the detatched "tail" aka cup nr 1 to the old value of nextCup[2] aka 5
	nextCup[1] = 5 <---- CHANGE

	cups: (3) 2 8 9 1 5 4 6 7

	now we have the following:
	nextCup[0] = 0
	nextCup[1] = 5 <--- CHANGE (end of the tail)
	nextCup[2] = 8 <--- CHANGE 
	nextCup[3] = 2 <--- CHANGE (current value, beginning of the tail)
	nextCup[4] = 6
	nextCup[5] = 4
	nextCup[6] = 7
	nextCup[7] = 3
	nextCup[8] = 9
	nextCup[9] = 1

	So we only need to change the following:
	The current cup needs to point to whatever the end of the tail was connected to (2 in this case)
	We need to connect the start of the tail (8) to the new destination (2)
	and we need to connect the 
	*/

	int detatched[3];

	detatched[0] = nextCup[current];
	detatched[1] = nextCup[detatched[0]];
	detatched[2] = nextCup[detatched[1]];

	nextCup[current] = detatched[2];

	int destination = current - 1;
	if (destination <= 0)
	{
		destination = nextCup.size() - 1;
	}

	// make sure the next destination is not in the detached set.
	while (detatched[0] == destination || detatched[1] == destination || detatched[2] == destination)
	{
		destination--;
		if (destination <= 0)
		{
			destination = nextCup.size() - 1;
		}
	}

	nextCup[detatched[2]] = nextCup[destination];
	nextCup[destination] = detatched[0];

	return nextCup[current];
}

AOC20::Day23::Day23() : Day("2020//Input//day23_data.txt", "2020//Input//day23_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day23::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);

	int index = 0;
	std::vector<int> cupNumbers;
	Node startNode;

	for (char c; input.Next(c);)
	{
		cupNumbers.push_back(c - '0');
	}

	startNode = Node();
	startNode.next = &startNode;
	startNode.previous = &startNode;
	startNode.Value = cupNumbers[0];

	Node* currentNode = &startNode;

	for (int i = 1; i < cupNumbers.size(); i++)
	{
		currentNode->next = new Node();
		currentNode->next->previous = currentNode;
		currentNode->next->Value = cupNumbers[i];
		currentNode->next->next = &startNode;

		startNode.previous = currentNode->next;

		currentNode = currentNode->next;
	}

	currentNode = &startNode;
	for (int i = 0; i < 100; i++)
	{
		Node* pickedUp = currentNode->next;
		currentNode->next = pickedUp->next->next->next;
		pickedUp->next->next->next = pickedUp;
		pickedUp->previous = pickedUp->next->next;


		int nextValue = currentNode->Value - 1;

		if (nextValue == 0)
		{
			nextValue = 9;
		}

		while (true)
		{
			if (pickedUp->Value == nextValue ||
				pickedUp->next->Value == nextValue ||
				pickedUp->next->next->Value == nextValue)
			{
				nextValue -= 1;
				if (nextValue == 0)
				{
					nextValue = 9;
					continue;
				}
			}
			else
			{
				break;
			}
		}

		auto insertAfterNode = currentNode->next;
		while (true)
		{
			if (insertAfterNode->Value == nextValue)
			{
				auto insertBeforeNode = insertAfterNode->next;
				insertAfterNode->next = pickedUp;
				insertBeforeNode->previous = pickedUp->previous;
				pickedUp->previous->next = insertBeforeNode;
				pickedUp->previous = insertAfterNode;
				//insertBefore->previous = pickedUp->previous;


				break;
			}
			else
			{
				insertAfterNode = insertAfterNode->next;
			}
		}

		currentNode = currentNode->next;

		
	}
	//pickedUp->previous = 
	bool seenOne = false;
	std::string answer = "";
	while (true)
	{
		if (seenOne)
		{
			if (currentNode->Value != 1)
			{
				answer += std::to_string(currentNode->Value);
			}
			else
			{
				break;
			}
		}
		else
		{
			if (currentNode->Value == 1)
			{
				seenOne = true;
			}
		}
		currentNode = currentNode->next;
	}

	printf("[%s-%s] : Answer{%s}.\n", _name.c_str(), __func__, answer.c_str());
	
}

void AOC20::Day23::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);
	std::string inputRow;
	input.NextRow(inputRow);

	// we will not be using index 0, because there will never be a cup with the number 0 on it.
	std::vector<int> nextCup(1000001); 

	int previous = inputRow[0] - '0'; 
	int current = previous;
	for (int i = 1; i < inputRow.size(); i++)
	{
		nextCup[previous] = inputRow[i] - '0';
		previous = nextCup[previous];
	}

	for (int i = inputRow.size() + 1; i <= 1000000; ++i) 
	{
		nextCup[previous] = i;
		previous = i;
	}
	nextCup[previous] = current;

	for (int i = 0; i < 10000000; ++i) {
		current = move(nextCup, current);
	}

	uint64_t product = (size_t)nextCup[1] * (size_t)nextCup[nextCup[1]];

	printf("[%s-%s] : The product is {%llu}.\n", _name.c_str(), __func__, product);
}

AOC20::Day23::~Day23()
{
}