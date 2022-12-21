#pragma once
#include <map>
#include <sstream>

#include "../Day.h"

namespace AOC22
{
	struct Day21Node
	{
		bool isUnknown = false;
		double value = 0;
		Day21Node* left = nullptr;
		char operation;
		Day21Node* right = nullptr;

		std::string ToString()
		{
			std::stringstream ss;
			if (isUnknown)
			{
				return "X";
			}
			else if (left == nullptr && right == nullptr)
			{
				ss << static_cast<int64_t>(value);
				return ss.str();
			}
			else if (operation == '=')
			{
				return left->ToString() + operation + right->ToString();
			}
			else
			{
				return "("+left->ToString()+operation+right->ToString()+")";
			}
		}

		void deleteChildren()
		{
			if (left != nullptr)
			{
				left->deleteChildren();
				delete(left);
				left = nullptr;
			}
			if (right != nullptr)
			{
				right->deleteChildren();
				delete(right);
				right = nullptr;
			}
			
		}

		bool Simplify()
		{
			if (operation == '=')
			{
				if (left->CanSimplify())
				{
					double tempValue = left->Calculate();
					left->deleteChildren();
					left->value = tempValue;
					left->isUnknown = false;


					auto oldRight = this->right;
					if (right->left != nullptr && right->left->CanSimplify())
					{
						auto old = this->right;
						double modifier = right->left->Calculate();

						switch (right->operation)
						{
						case '+':
							left->value = left->value - modifier;
							break;
						case '-':
							left->value = left->value - modifier;
							break;
						case '*':
							left->value = left->value / modifier;
							break;
						case '/':
							left->value = left->value / modifier;
							break;
						default:
							break;
						}
						this->right = right->right;
						delete(oldRight);
						return true;
					}
					if (right->right != nullptr && right->right->CanSimplify())
					{
						double modifier = right->right->Calculate();

						switch (right->operation)
						{
						case '+':
							left->value = left->value - modifier;
							break;
						case '-':
							left->value = left->value + modifier;
							break;
						case '*':
							left->value = left->value / modifier;
							break;
						case '/':
							left->value = left->value * modifier;
							break;
						default:
							break;
						}
						this->right = right->left;
						delete(oldRight);
						return true;
					}
				}
				if (right->CanSimplify())
				{
					double tempValue = right->Calculate();
					right->deleteChildren();
					right->value = tempValue;
					right->isUnknown = false;

					auto oldLeft = this->left;
					if (left->left != nullptr && left->left->CanSimplify())
					{
						double modifier = left->left->Calculate();

						switch (left->operation)
						{
						case '+':
							right->value = right->value - modifier;
							break;
						case '-':
							right->value = right->value - modifier;
							break;
						case '*':
							right->value = right->value / modifier;
							break;
						case '/':
							right->value = right->value / modifier;
							break;
						default:
							break;
						}
						this->left = left->right;
						delete(oldLeft);
						return true;
					}
					if (left->right != nullptr && left->right->CanSimplify())
					{
						double modifier = left->right->Calculate();

						switch (left->operation)
						{
						case '+':
							right->value = right->value - modifier;
							break;
						case '-':
							right->value = right->value + modifier;
							break;
						case '*':
							right->value = right->value / modifier;
							break;
						case '/':
							right->value = right->value * modifier;
							break;
						default:
							break;
						}
						this->left = this->left->left;
						delete(oldLeft);
						return true;
					}
				}
			}
			return false;
		}

		void SuperSimplify()
		{
			if (this->left != nullptr)
			{
				this->left->SuperSimplify();

				if ( this->left->CanSimplify())
				{
					this->left->value = this->left->Calculate();
					this->left->deleteChildren();
				}
			}

			if (this->right != nullptr)
			{
				this->right->SuperSimplify();

				if (this->right->CanSimplify())
				{
					this->right->value = this->right->Calculate();
					this->right->deleteChildren();
				}
			}
			
		}

		bool CanSimplify()
		{
			if (left != nullptr && right != nullptr)
			{
				return left->CanSimplify() && right->CanSimplify();
			}

			return !isUnknown;
		}

		double Calculate()
		{
			if (left == nullptr && right == nullptr)
			{
				return value;
			}
			else
			{
				switch (operation)
				{
				case '+':
					return left->Calculate() + right->Calculate();
				case '-':
					return left->Calculate() - right->Calculate();
				case '*':
					return left->Calculate() * right->Calculate();
				case '/':
					return left->Calculate() / right->Calculate();
				default:
					break;
				}
			}
		}
	};

	class Day21 : public Day
	{
	private:
		Day21Node* CreateTree(const std::string&);
		std::map<std::string, std::string> inputMap;
	public:
		Day21();

		void SolvePartOne(bool = false) override;
		void SolvePartTwo(bool = false) override;

		~Day21();
	};
}
