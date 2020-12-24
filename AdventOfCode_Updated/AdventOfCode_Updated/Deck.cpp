#include "Deck.h"

Deck::Deck() : _cards({})
{
}

void Deck::addCard(uint16_t card)
{
	_cards.push_back(card);
}

void Deck::dumb()
{
	_cards.clear();
}

std::string Deck::toString()
{
	std::string deck = "";
	for (auto i : _cards)
	{
		deck += std::to_string(i) + ", ";
	}

	deck.erase(deck.end() - 2, deck.end());

	return deck;
}

uint16_t Deck::dealCard()
{
	if(isEmpty())
	{
		return uint16_t();
	}

	uint16_t card = _cards.front();
	_cards.erase(_cards.begin());
	return card;
}

size_t Deck::cardsInDeck() const
{
	return _cards.size();
}

bool Deck::isEmpty() const
{
	return _cards.empty();
}

bool Deck::operator==(const Deck& b)
{
	if (b.cardsInDeck() == this->cardsInDeck())
	{
		for (size_t i = 0; i < this->cardsInDeck(); i++)
		{
			if (b._cards[i] != this->_cards[i])
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

std::vector<uint16_t> Deck::topCards(size_t nrOfCards) const
{
	std::vector<uint16_t> topCards;

	for (int i = 0; i < nrOfCards; i++)
	{
		topCards.push_back(_cards[i]);
	}

	return topCards;
}
