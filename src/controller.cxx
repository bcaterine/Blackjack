#include "controller.hxx"

using namespace ge211;

Controller::Controller()
        : view_(model_)
{
    model_.deal_cards();
}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position pos) {
    if (model_.winner() == Model::Player::neither) {
        if (pos.x >= view_.get_hit_pos().x && pos.y >= view_.get_hit_pos().y
            && pos.x <= view_.get_hit_pos().x + view_.get_hit_dims().width
            && pos.y <= view_.get_hit_pos().y + view_.get_stand_dims().height) {
            model_.user_draw_card();
        }

        if (pos.x >= view_.get_stand_pos().x && pos.y >= view_.get_stand_pos().y
            && pos.x <= view_.get_stand_pos().x + view_.get_stand_dims().width
            && pos.y <= view_.get_stand_pos().y +view_.get_stand_dims().height){
            model_.dealer_turn();
        }
    }
}

void Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();
    if (model_.winner() != Model::Player::neither) {
        if (key == ge211::Key::code(' '))
            model_.reset_game();
        if (key == ge211::Key::code('r')) {
            model_.reset_game();
            view_.set_back_color("red");
        }
        if (key == ge211::Key::code('y')) {
            model_.reset_game();
            view_.set_back_color("yellow");
        }
        if (key == ge211::Key::code('g')) {
            model_.reset_game();
            view_.set_back_color("green");
        }
        if (key == ge211::Key::code('b')) {
            model_.reset_game();
            view_.set_back_color("blue");
        }
        if (key == ge211::Key::code('p')) {
            model_.reset_game();
            view_.set_back_color("purple");
        }
        if (key == ge211::Key::code('0')) {
            model_.reset_game();
            view_.set_back_color("gray");
        }
    }
}

void Controller::draw(Sprite_set& sprites)
{
    if (view_.get_back_color() == "red")
        background_color = ge211::Color {0,255,0}.darken(.8);
    if (view_.get_back_color() == "yellow")
        background_color = ge211::Color::medium_yellow().darken(.8);
    if (view_.get_back_color() == "green")
        background_color = ge211::Color {0,255,0}.darken(.8);
    if (view_.get_back_color() == "blue")
        background_color = ge211::Color {0,0,255}.darken(.8);
    if (view_.get_back_color() == "purple")
        background_color = ge211::Color {75,0,130};
    if (view_.get_back_color() == "gray")
        background_color = ge211::Color {50,50,50};
    view_.draw(sprites);
}