#include "model.hxx"
#include <catch.hxx>
#include <utility>

struct Test_access
{
    Model& m_;

    void shuffle_deck()
    { m_.shuffle_deck_(m_.get_random()); }

    bool is_blackjack(const std::vector<Model::Card>& player)
    { return m_.is_blackjack_(player); }

    bool draw_card()
    { return m_.draw_card_(); }

    bool is_not_bust(std::vector<Model::Card> player)
    { return m_.is_not_bust_(std::move(player)); }

    int score(std::vector<Model::Card> player)
    { return m_.score_(std::move(player)); }

    std::vector<Model::Card> deck()
    { return m_.deck_; }

    std::vector<Model::Card> user_hand()
    { return m_.user_hand_; }

    std::vector<Model::Card> dealer_hand()
    { return m_.dealer_hand_; }
};

TEST_CASE("deal_cards, user_draw_card, reset_game, draw_card_")
{
    Model m;
    Test_access t{m};

    m.deal_cards();
    CHECK(t.user_hand().size() == 2);
    CHECK(t.dealer_hand().size() == 2);
    CHECK(t.deck().size() == 48);

    m.user_draw_card();
    if (m.winner() == Model::Player::neither) {
        CHECK(t.user_hand().size() == 3);
        CHECK(t.deck().size() == 47);
    }

    m.reset_game();

    CHECK(t.user_hand().size() == 2);
    CHECK(t.dealer_hand().size() == 2);
    CHECK(t.deck().size() == 48);

    t.draw_card();
    if (m.user_score() < 21) {
        CHECK(t.user_hand().size() == 3);
        CHECK(t.deck().size() == 47);
    }
}

TEST_CASE("shuffle") {
    Model m;
    Test_access t{m};

    std::string original1 = t.deck()[0].first;
    std::string original2 = t.deck()[1].first;
    std::string original3 = t.deck()[2].first;
    std::string original4 = t.deck()[3].first;
    t.shuffle_deck();
    bool check = original1 != t.deck()[0].first
                 || original2 != t.deck()[1].first
                 || original3 != t.deck()[2].first
                 || original4 != t.deck()[3].first;
    CHECK(check);

    int total = 0;
    for (Model::Card card : t.deck()) {
        total += card.second;
    }
    CHECK(total == 380);
}

TEST_CASE("Add cards and bust")
{
    Model m;
    Test_access t{m};

    std::vector<Model::Card> player = {{"H2", 8}, {"D2", 4}};
    CHECK_FALSE(t.is_blackjack(player));
    CHECK(t.score(player) == 12);
    CHECK(t.is_not_bust(player));

    player.push_back({"SQ", 10});
    CHECK(t.score(player) == 22);
    CHECK_FALSE(t.is_not_bust(player));
}

TEST_CASE("Blackjack!")
{
    Model m;
    Test_access t{m};

    std::vector<Model::Card> player = {{"HJ", 10}, {"DA", 11}};
    CHECK(t.score(player) == 21);
    CHECK(t.is_not_bust(player));
    CHECK(t.is_blackjack(player));
}

TEST_CASE("Aces")
{
    Model m;
    Test_access t{m};

    std::vector<Model::Card> player = {{"HA", 11}, {"DA", 11}};
    CHECK(t.is_not_bust(player));
    CHECK(t.score(player) == 12);
    CHECK(t.is_not_bust(player));
    CHECK(player[0].second == 11);
    CHECK(player[1].second == 11);

    player.push_back({"S9",9});
    CHECK(t.is_not_bust(player));
    CHECK(t.score(player) == 21);

    player.push_back({"S2",2});
    CHECK(t.is_not_bust(player));
    CHECK(t.score(player) == 13);

    player.push_back({"SJ",10});
    CHECK_FALSE(t.is_not_bust(player));
    CHECK(t.score(player) == 23);
}

TEST_CASE("Push/Tie")
{
    Model m;
    Test_access t{m};
    m.add_user_hand({"C10", 10});
    m.add_user_hand({"CJ", 10});
    m.add_dealer_hand({"CQ", 10});
    m.add_dealer_hand({"CK", 10});

    m.dealer_turn();
    CHECK(m.winner() == Model::Player::tie);
    CHECK(t.is_not_bust(t.user_hand()));
    CHECK(t.is_not_bust(t.dealer_hand()));
    CHECK_FALSE(t.is_blackjack(t.user_hand()));
    CHECK_FALSE(t.is_blackjack(t.dealer_hand()));
}