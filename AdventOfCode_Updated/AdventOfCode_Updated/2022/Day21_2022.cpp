#include "../2022/Day21_2022.h"


AOC22::Day21Node* AOC22::Day21::CreateTree(const std::string& expression)
{
	if (std::isdigit(expression[0]) || std::isdigit(expression[1]))
	{
		AOC22::Day21Node* node;
		node = new AOC22::Day21Node();
		node->value = std::stod(expression);
		return node;
	}
	else if (expression[0] == 'X')
	{
		AOC22::Day21Node* node;
		node = new AOC22::Day21Node();
		node->isUnknown = true;
		return node;
	}
	else
	{
		size_t index = expression.find(' ');
		std::string value1 = expression.substr(0, index);
		char operation = expression[index + 1];
		std::string value2 = expression.substr(index + 3);

		AOC22::Day21Node* node;
		node = new AOC22::Day21Node();
		node->left = CreateTree(this->inputMap[value1]);
		node->operation = operation;
		node->right = CreateTree(this->inputMap[value2]);

		return node;
	}

	return nullptr;
}

AOC22::Day21::Day21() : Day("Input//2022//day21_data.txt", "Input//2022//day21_data_simple.txt")
{
}

void AOC22::Day21::SolvePartOne(bool simple)
{
	auto input = Day::Input(simple);

	for (std::string row; input.NextRow(row);)
	{
		size_t index = row.find(':');
		std::string monkey = row.substr(0, index);
		std::string say = row.substr(index + 2);
		this->inputMap[monkey] = say;
	}

	AOC22::Day21Node* node = CreateTree(this->inputMap["root"]);
	node->SuperSimplify();
	auto result = node->Calculate();

	node->deleteChildren();
	delete(node);
	printf("1) (%lli)\n", static_cast<int64_t>(result));
}

void AOC22::Day21::SolvePartTwo(bool simple)
{
	auto input = Day::Input(simple);

	for (std::string row; input.NextRow(row);)
	{
		size_t index = row.find(':');
		std::string monkey = row.substr(0, index);
		std::string say = row.substr(index + 2);

		if (monkey == "root")
		{
			size_t operatorIndex = say.find(' ') + 1;
			say[operatorIndex] = '=';
		}

		else if (monkey == "humn")
		{
			say = "X";
		}

		this->inputMap[monkey] = say;
	}

	AOC22::Day21Node* node = CreateTree(this->inputMap["root"]);

	node->SuperSimplify();

	double answer;
	AOC22::Day21Node* current;

	if (node->left->CanSimplify())
	{
		answer = node->left->Calculate();
		current = node->right;
	}
	else
	{
		answer = node->right->Calculate();
		current = node->left;
	}

	while (current != nullptr && current->left != nullptr && current->right != nullptr)
	{
		char op = current->operation;
		double value = 0;
		bool onLeft = false;

		if (current->left->CanSimplify())
		{
			value = current->left->Calculate();
			onLeft = true;
		}
		else if (current->right->CanSimplify())
		{
			value = current->right->Calculate();
		}

		switch (op)
		{
		case '+':
			answer = answer - value;
			break;
		case '-':
			if (onLeft)
			{
				answer = answer - value;
				answer *= -1;
			}
			else
			{
				answer = answer + value;
			}
			break;
		case '*':
			answer = answer / value;
			break;
		case '/':
			if (onLeft)
			{
				answer = value / answer;
			}
			else
			{
				answer = answer * value;
			}
			break;
		default:
			break;
		}

		if (onLeft)
		{
			current = current->right;
		}
		else
		{
			current = current->left;
		}
	}

	node->deleteChildren();
	delete(node);

	printf("2) (%lli)\n", static_cast<int64_t>(answer + 0.5));
}

AOC22::Day21::~Day21()
{

}
