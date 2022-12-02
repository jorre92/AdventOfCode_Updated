#include "Day22_2020.h"
#include <iostream>
#include <algorithm>

int AOC20::Day22::RecursiveCombat(std::vector<Deck> playerDecks, std::vector<Deck>& results) const
{	
	std::vector<std::pair<std::string, std::string>>  myHistory = {};

	// playing
	while (!playerDecks[0].isEmpty() && !playerDecks[1].isEmpty())
	{
		std::pair<std::string, std::string> state = { playerDecks[0].toString(), playerDecks[1].toString() }; 
		
		auto found = std::find(myHistory.begin(), myHistory.end(), state);

		if (found != myHistory.end())
		{
			results = playerDecks;
			return 0;
		}

		myHistory.push_back(state);

		auto playerOneCard = playerDecks[0].dealCard();
		auto playerTwoCard = playerDecks[1].dealCard();

		if (playerDecks[0].cardsInDeck() >= playerOneCard && playerDecks[1].cardsInDeck() >= playerTwoCard)
		{
			// play a new round of this combat.
			std::vector<Deck> result;
			std::vector<Deck> newDecks = { {}, {} };

			for (auto it : playerDecks[0].topCards(playerOneCard))
			{
				newDecks[0].addCard(it);
			} 
			for (auto it : playerDecks[1].topCards(playerTwoCard))
			{
				newDecks[1].addCard(it);
			}

			auto winner = RecursiveCombat(newDecks, result);

			if (winner == 0)
			{
				playerDecks[0].addCard(playerOneCard);
				playerDecks[0].addCard(playerTwoCard);
			}
			else
			{
				playerDecks[1].addCard(playerTwoCard);
				playerDecks[1].addCard(playerOneCard);
			}
		}
		else
		{
			if (playerOneCard > playerTwoCard)
			{
				playerDecks[0].addCard(playerOneCard);
				playerDecks[0].addCard(playerTwoCard);
			}
			else
			{
				playerDecks[1].addCard(playerTwoCard);
				playerDecks[1].addCard(playerOneCard);			

			}
		}
	}

	results = playerDecks;
	return playerDecks[0].isEmpty() ? 1 : 0;
}

AOC20::Day22::Day22() : Day("2020//Input//day22_data.txt", "2020//Input//day22_data_simple.txt")
{
	_name = __func__;
}

void AOC20::Day22::SolvePartOne(bool simpleData)
{
	auto input = Day::Input(simpleData);

	std::vector<Deck> playerDecks;

	// dealing cards
	for (std::vector<std::string> rows; input.NextBatch(rows);)
	{
		playerDecks.push_back({ });

		for (auto it = rows.begin() + 1; it != rows.end(); it++)
		{
			uint16_t card = std::stoul((*it));
			playerDecks.back().addCard(card);
		}
	}
	std::vector<std::vector<Deck>> previousRounds;

	// playing
	while (!playerDecks[0].isEmpty() && !playerDecks[1].isEmpty())
	{
		previousRounds.push_back(playerDecks);

		auto playerOneCard = playerDecks[0].dealCard();
		auto playerTwoCard = playerDecks[1].dealCard();

		if (playerOneCard > playerTwoCard)
		{
			playerDecks[0].addCard(playerOneCard);
			playerDecks[0].addCard(playerTwoCard);
		}
		else
		{
			playerDecks[1].addCard(playerTwoCard);
			playerDecks[1].addCard(playerOneCard);
		}
	}
	auto winnerDeck = playerDecks[0].cardsInDeck() > playerDecks[1].cardsInDeck() ? playerDecks[0] : playerDecks[1];	// scoring

	uint64_t score = 0;
	while (!winnerDeck.isEmpty())
	{
		score += winnerDeck.cardsInDeck() * winnerDeck.dealCard();
	}

	printf("[%s-%s] : The winner had a score of {%llu}.\n", _name.c_str(), __func__, score);
}

void AOC20::Day22::SolvePartTwo(bool simpleData)
{
	auto input = Day::Input(simpleData);	

	std::vector<Deck> playerDecks;
	std::vector<Deck> result;
	std::vector<std::pair<std::string, std::string>> history;

	// dealing cards
	for (std::vector<std::string> rows; input.NextBatch(rows);)
	{
		playerDecks.push_back({ });

		for (auto it = rows.begin() + 1; it != rows.end(); it++)
		{
			uint16_t card = std::stoul((*it));
			playerDecks.back().addCard(card);
		}
	}

	// playing
	auto winner = RecursiveCombat(playerDecks, result);

	// scoring
	auto winnerDeck = result[winner];

	uint64_t score = 0;
	while (!winnerDeck.isEmpty())
	{
		score += winnerDeck.cardsInDeck() * winnerDeck.dealCard();
	}

	printf("[%s-%s] : The winner had a score of {%llu}.\n", _name.c_str(), __func__, score);
}

AOC20::Day22::~Day22()
{
}