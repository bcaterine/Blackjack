#pragma once
#include "model.hxx"
#include "view.hxx"

class Controller : public ge211::Abstract_game
{
public:

    /// Constructor
    explicit Controller();


protected:

    /// Overridden Abstract_game Functions

    // Takes action when the hit or stand buttons are clicked.
    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

    // Quits if 'q' is pressed and deals a new hand if the space bar is pressed.
    void on_key(ge211::Key) override;

    // Delegates drawing to the view and sets the background color.
    void draw(ge211::Sprite_set&) override;


private:

    Model model_;
    View view_;

};