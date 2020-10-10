#pragma once
#include "model.hxx"
#include <algorithm>

class View
{
public:

    /// Constructor

    explicit View(Model const&);


    /// Public Functions

    // Draws the scene using the sprites defined below.
    void draw(ge211::Sprite_set&) const;

    // A Card is a pair containing a std::string that names the card (2 of
    // hearts is "H2") and an Image_sprite that draws the corresponding card.
    using View_Card = std::pair<std::string, ge211::Image_sprite>;

    // A Score_pair is a pair containing an int that represents the a number
    // value (0-30) and a Text_sprite that draws the corresponding number.
    using Score_Pair = std::pair<int, ge211::Text_sprite>;

    // Returns the position of the hit button.
    ge211::Position get_hit_pos()
    { return hit_pos_; }

    // Returns the position of the stand button.
    ge211::Position get_stand_pos()
    { return stand_pos_; }

    // Returns the dimensions of the hit button.
    ge211::Dimensions get_hit_dims()
    { return hit_button_.dimensions(); }

    // Returns the dimensions of the stand button.
    ge211::Dimensions get_stand_dims()
    { return stand_button_.dimensions(); }

    // Sets the color choice given an int that corresponds to a color.
    void set_back_color(const std::string&);

    // Returns the card back color.
    std::string get_back_color()
    { return back_color_; }

private:

    /// Private Member Variables

    Model const& model_;

    // Font variables
    ge211::Font sans_{"sans.ttf", 50};
    ge211::Font sans_small_{"sans.ttf", 25};

    // Hit/stand position variables
    ge211::Position hit_pos_ = {160,475};
    ge211::Position stand_pos_ = {480,475};

    // Sprites for hit/stand buttons and their text
    ge211::Rectangle_sprite hit_button_{{160,100},
                                        ge211::Color {0,255,0}.darken(.4)};
    ge211::Rectangle_sprite stand_button_{{160,100},
                                        ge211::Color {255,0,0}.darken(.5)};
    ge211::Text_sprite hit_text_{"Hit", sans_};
    ge211::Text_sprite stand_text_{"Stand", sans_};

    // Sprites for the end screen
    ge211::Rectangle_sprite screen_dimmer_{{800,600},
                                           ge211::Color {0, 0, 0, 200}};
    ge211::Text_sprite user_win_text_{"You win!", sans_};
    ge211::Text_sprite dealer_win_text_{"Dealer wins.", sans_};
    ge211::Text_sprite push_text_{"Push.", sans_};
    ge211::Text_sprite blackjack_text_{"Blackjack!", sans_};
    ge211::Text_sprite space_text_{"Press SPACE to deal a new hand.",
                                   sans_small_};
    ge211::Text_sprite bottom_text_{
        "Press r, y, g, b, p, or 0 to change theme.",
        sans_small_};

    // Sprite variable for card back color
    std::string back_color_ = "red";

    //Standard 52-card deck of Image_sprites + an Image_sprite for the card back
    ge211::Image_sprite C2_{"2C.png"}, C3_{"3C.png"}, C4_{"4C.png"},
                        C5_{"5C.png"}, C6_{"6C.png"}, C7_{"7C.png"},
                        C8_{"8C.png"}, C9_{"9C.png"}, C10_{"10C.png"},
                        CJ_{"JC.png"}, CQ_{"QC.png"}, CK_{"KC.png"},
                        CA_{"AC.png"},
                        D2_{"2D.png"}, D3_{"3D.png"}, D4_{"4D.png"},
                        D5_{"5D.png"}, D6_{"6D.png"}, D7_{"7D.png"},
                        D8_{"8D.png"}, D9_{"9D.png"}, D10_{"10D.png"},
                        DJ_{"JD.png"}, DQ_{"QD.png"}, DK_{"KD.png"},
                        DA_{"AD.png"},
                        H2_{"2H.png"}, H3_{"3H.png"}, H4_{"4H.png"},
                        H5_{"5H.png"}, H6_{"6H.png"}, H7_{"7H.png"},
                        H8_{"8H.png"}, H9_{"9H.png"}, H10_{"10H.png"},
                        HJ_{"JH.png"}, HQ_{"QH.png"}, HK_{"KH.png"},
                        HA_{"AH.png"},
                        S2_{"2S.png"}, S3_{"3S.png"}, S4_{"4S.png"},
                        S5_{"5S.png"}, S6_{"6S.png"}, S7_{"7S.png"},
                        S8_{"8S.png"}, S9_{"9S.png"}, S10_{"10S.png"},
                        SJ_{"JS.png"}, SQ_{"QS.png"}, SK_{"KS.png"},
                        SA_{"AS.png"},
                        red_back_{"red_back.png"},yellow_back_{"yellow_back.png"},
                        green_back_{"green_back.png"},blue_back_{"blue_back.png"},
                        purple_back_{"purple_back.png"},gray_back_{"gray_back.png"},
                        cats_{"cats.png"};

    // Standard 52-card deck of View_Cards_
    std::vector<View_Card> view_deck_ = {{"C2", C2_}, {"C3", C3_}, {"C4", C4_},
                                         {"C5", C5_}, {"C6", C6_}, {"C7", C7_},
                                         {"C8", C8_}, {"C9", C9_},{"C10", C10_},
                                         {"CJ", CJ_}, {"CQ", CQ_}, {"CK", CK_},
                                         {"CA", CA_},
                                         {"D2", D2_}, {"D3", D3_}, {"D4", D4_},
                                         {"D5", D5_}, {"D6", D6_}, {"D7", D7_},
                                         {"D8", D8_}, {"D9", D9_},{"D10", D10_},
                                         {"DJ", DJ_}, {"DQ", DQ_}, {"DK", DK_},
                                         {"DA", DA_},
                                         {"H2", H2_}, {"H3", H3_}, {"H4", H4_},
                                         {"H5", H5_}, {"H6", H6_}, {"H7", H7_},
                                         {"H8", H8_}, {"H9", H9_},{"H10", H10_},
                                         {"HJ", HJ_}, {"HQ", HQ_}, {"HK", HK_},
                                         {"HA", HA_},
                                         {"S2", S2_}, {"S3", S3_}, {"S4", S4_},
                                         {"S5", S5_}, {"S6", S6_}, {"S7", S7_},
                                         {"S8", S8_}, {"S9", S9_},{"S10", S10_},
                                         {"SJ", SJ_}, {"SQ", SQ_}, {"SK", SK_},
                                         {"SA", SA_}};

    // Text_sprites for numbers 0-30
    ge211::Text_sprite n0_{"0", sans_}, n1_{"1", sans_}, n2_{"2", sans_},
                       n3_{"3", sans_}, n4_{"4", sans_}, n5_{"5", sans_},
                       n6_{"6", sans_}, n7_{"7", sans_}, n8_{"8", sans_},
                       n9_{"9", sans_}, n10_{"10", sans_}, n11_{"11", sans_},
                       n12_{"12", sans_}, n13_{"13", sans_}, n14_{"14", sans_},
                       n15_{"15", sans_}, n16_{"16", sans_}, n17_{"17", sans_},
                       n18_{"18", sans_}, n19_{"19", sans_}, n20_{"20", sans_},
                       n21_{"21", sans_}, n22_{"22", sans_}, n23_{"23", sans_},
                       n24_{"24", sans_}, n25_{"25", sans_}, n26_{"26", sans_},
                       n27_{"27", sans_}, n28_{"28", sans_}, n29_{"29", sans_},
                       n30_{"30", sans_};

    // A vector that maps each score sprite to its corresponding number value
    std::vector<Score_Pair> scores_ = {{0, n0_}, {1, n1_}, {2, n2_}, {3, n3_},
                                       {4, n4_}, {5, n5_}, {6, n6_}, {7, n7_},
                                       {8, n8_}, {9, n9_}, {10, n10_},
                                       {11, n11_}, {12, n12_}, {13, n13_},
                                       {14, n14_}, {15, n15_}, {16, n16_},
                                       {17, n17_}, {18, n18_}, {19, n19_},
                                       {20, n20_}, {21, n21_}, {22, n22_},
                                       {23, n23_}, {24, n24_}, {25, n25_},
                                       {26, n26_}, {27, n27_}, {28, n28_},
                                       {29, n29_}, {30, n30_}};
};