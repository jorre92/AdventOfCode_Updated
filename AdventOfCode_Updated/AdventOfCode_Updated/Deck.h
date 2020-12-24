#pragma once
#include <vector>
#include <string>

class Deck
{
private:
	std::vector<uint16_t> _cards;
public:
	Deck();
	void addCard(uint16_t);
	void dumb();
	std::string toString();
	uint16_t dealCard();
	size_t cardsInDeck() const;
	bool isEmpty() const;
	bool operator==(const Deck&);
	std::vector<uint16_t> topCards(size_t) const;
};

