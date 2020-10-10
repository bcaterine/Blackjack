#pragma once

#include <ge211.hxx>
#include <string>

class Model : public ge211::Abstract_game
{
public:

    /// Public Class

    // The Player class has values user, dealer, neither, and tie, which can be
    // used to signify the turn and the winner.
    enum class Player {
        user,
        dealer,
        neither,
        tie
    };


    /// Public Functions

    friend struct Test_access;

    // A Card is a pair containing a std::string that names the card (2 of
    // hearts is "H2") and an int signifying its value (2 in this case).
    using Card = std::pair<std::string, int>;

    // Sets up the hand by dealing two cards each to the user and dealer. This
    // is done by first calling shuffle_deck_ and then calling draw_card_ for
    // each draw. The user's hand is then checked for Blackjack by calling
    // is_blackjack_. If the user has Blackjack, the dealer's hand is checked
    // for Blackjack. winner_ is set to user if the dealer does not have
    // Blackjack and set to tie if he does.
    void deal_cards();

    // Draws a card and adds it to the user's hand by calling draw_card_.
    // Sets winner_ to dealer if the user has busted (This ends the game).
    void user_draw_card();

    // Calls draw_card_ on the dealer's hand until his point value exceeds 16
    // (found by calling score_). Then checks whether the dealer has busted and
    // sets winner_ to user if the dealer has. If the dealer has not busted,
    // compares the scores of the user and dealer and sets winner_ to the player
    // with the highest score.
    void dealer_turn();

    // Returns the current turn (either Player::user or Player::dealer).
    Player turn() const
    { return turn_;}

    // Returns the winner. This is Player::neither if there is not yet a winner,
    // Player::user or Player::dealer if there is a winner, and Player::tie if
    // there is no winner but the game is over.
    Player winner() const
    { return winner_; }

    // Defines the Abstract_game draw function to do nothing.
    void draw(ge211::Sprite_set&) override {};

    // For testing: add cards to user_hand_
    void add_user_hand(const Card& card)
    { user_hand_.push_back(card); }

    // For testing: add cards to dealer_hand_
    void add_dealer_hand(const Card& card)
    { dealer_hand_.push_back(card); }

    /// Getter/Setter Functions

    // Returns a Card vector containing the Cards in the user's hand.
    std::vector<Card> get_user_hand_() const
    { return user_hand_; }

    // Returns a Card vector containing the Cards in the dealer's hand.
    std::vector<Card> get_dealer_hand_() const
    { return dealer_hand_; }

    // Returns whether the user has Blackjack.
    bool is_user_blackjack() const
    { return is_blackjack_(user_hand_); }

    // Returns the user's score.
    int user_score() const
    { return score_(user_hand_); }

    // Returns the dealer's score.
    int dealer_score() const
    { return score_(dealer_hand_); }

    // Resets the game for another hand.
    void reset_game()
    { reset_(); }


private:

    /// Private Member Variables

    //deck_ is a vector of Cards containing each card in a standard deck.
    std::vector<Card> deck_ = {{"C2", 2}, {"C3", 3}, {"C4", 4}, {"C5", 5},
                               {"C6", 6}, {"C7", 7}, {"C8", 8}, {"C9", 9},
                               {"C10", 10}, {"CJ", 10}, {"CQ", 10}, {"CK", 10},
                               {"CA", 11},
                               {"D2", 2}, {"D3", 3}, {"D4", 4}, {"D5", 5},
                               {"D6", 6}, {"D7", 7}, {"D8", 8}, {"D9", 9},
                               {"D10", 10}, {"DJ", 10}, {"DQ", 10}, {"DK", 10},
                               {"DA", 11},
                               {"H2", 2}, {"H3", 3}, {"H4", 4}, {"H5", 5},
                               {"H6", 6}, {"H7", 7}, {"H8", 8}, {"H9", 9},
                               {"H10", 10}, {"HJ", 10}, {"HQ", 10}, {"HK", 10},
                               {"HA", 11},
                               {"S2", 2}, {"S3", 3}, {"S4", 4}, {"S5", 5},
                               {"S6", 6}, {"S7", 7}, {"S8", 8}, {"S9", 9},
                               {"S10", 10}, {"SJ", 10}, {"SQ", 10}, {"SK", 10},
                               {"SA", 11}};

    //user_hand_ is a vector of Cards that will contain the user's cards.
    std::vector<Card> user_hand_;

    //dealer_hand_ is a vector of Cards that will contain the dealer's cards.
    std::vector<Card> dealer_hand_;

    //turn_ is a Player that signifies whose turn it is (user or dealer).
    Player turn_ = Player::user;

    //winner_ is a Player that signifies who the winner is (neither if there is
    //not yet a winner, user/dealer if they are the winner, and tie if the game
    //is over but there is no winner).
    Player winner_ = Player::neither;


    /// Private Helper Functions

    // Randomizes the order of the member vector deck_ by calling
    // std::random_shuffle.
    void shuffle_deck_(ge211::Random& rng);

    // Returns a bool indicating whether the given player has Blackjack. This is
    // done by first checking whether there are only 2 cards in their hand and
    // then calling score_ and determining their total point value is 21.
    bool is_blackjack_(const std::vector<Card>&) const;

    // Adds the last element of the deck_ vector to the given player's hand
    // vector using push_back. Then removes the last element from deck_ using
    // pop_back. Then calls is_not_bust_ and returns false if the player has
    // busted.
    bool draw_card_();

    // Returns whether or not the given player has "busted". This is done by
    // calling score_ on the given player and determining whether their point
    // total exceeds 21. If it exceeds 21, checks whether any Aces in the
    // player's hand are set to a value of 11. If so, it sets one them to a
    // value of 1 and returns true. If there are no Aces, returns false to
    // indicate a bust.
    bool is_not_bust_(std::vector<Card>);

    // Returns the score of the given player. This is calculated by adding up
    // the values for each card in the player's hand. For example, the value of
    // first card in the user's hand is user_hand_[0].second.
    int score_(std::vector<Card>) const;

    // Resets all necessary member variables in order to play another hand.
    void reset_();
};

