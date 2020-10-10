#include <utility>

#include "model.hxx"

using namespace ge211;

void Model::deal_cards()
{
    shuffle_deck_(get_random());
    draw_card_();
    draw_card_();
    turn_ = Player::dealer;
    draw_card_();
    draw_card_();
    turn_ = Player::user;

    if(is_blackjack_(user_hand_)){
        turn_ = Player::dealer;
        if(is_blackjack_(dealer_hand_)){
            winner_ = Player::tie;
        } else {
            winner_ = Player::user;
        }
    }
}


void Model::user_draw_card()
{
    if(!draw_card_()) {
        winner_ = Player::dealer;
        turn_ = Player::dealer;
    }
}


void Model::dealer_turn()
{
    turn_ = Player::dealer;
    for(;;) {
        if (score_(dealer_hand_) < 17) {
            if(!draw_card_()) {
                winner_ = Player::user;
                return;
            }
        } else break;
    }
    if (score_(user_hand_) > score_(dealer_hand_))
        winner_ = Player::user;
    else if (score_(user_hand_) < score_(dealer_hand_))
        winner_ = Player::dealer;
    else
        winner_ = Player::tie;
}


///
///Helper functions definitions below
///

void Model::shuffle_deck_(Random& rng)
{
    unsigned long int j = deck_.size() - 1;
    for (unsigned long int i = 0; i < deck_.size() - 2; i++) {
        std::swap(deck_[i], deck_[rng.between(i, j)]);
    }
}

int Model::score_(std::vector<Card> hand) const {
    int score = 0;
    for(const Card& card : hand){
        score += card.second;
    }
    if(score > 21) {
        int i = 0;
        for(const Card& card : hand) {
            if (score > 21)
                if (card.first == "CA" || card.first == "DA"
                    || card.first == "SA" || card.first == "HA") {
                    if (card.second == 11) {
                        hand[i].second = 1;
                        score = 0;
                        for (const Card& card2 : hand) {
                            score += card2.second;
                        }
                    }
                }
            i++;
        }
        }
    return score;
}

bool Model::is_blackjack_(const std::vector<Card>& hand) const {
    return hand.size() == 2 && score_(hand) == 21;
}

bool Model::draw_card_()
{
    if(turn_ == Player::user){
        user_hand_.push_back(deck_[deck_.size() - 1]);
        if(!is_not_bust_(user_hand_))
            return false;
    }
    if(turn_ == Player::dealer){
        dealer_hand_.push_back(deck_[deck_.size() - 1]);
        if(!is_not_bust_(dealer_hand_))
            return false;
    }
    deck_.pop_back();
    return true;
}

bool Model::is_not_bust_(std::vector<Card> hand)
{
    return score_(std::move(hand)) <= 21;
}

void Model::reset_() {
    user_hand_.clear();
    dealer_hand_.clear();
    winner_ = Player::neither;
    turn_ = Player::user;
    deck_ = {{"C2", 2}, {"C3", 3}, {"C4", 4}, {"C5", 5},
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
    deal_cards();
}