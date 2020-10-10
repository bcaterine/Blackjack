# Proposal:
Blackjack

## Synopsis

### Elements

Our game will have 4 elements:

1. A row near the top of the screen for the dealer’s cards
2. A row near the middle of the screen for the player’s cards
3. Buttons for “Hit”/”Stand” near the bottom of the screen
4. Cards will be represented by image sprites.

### Goal

This is a Blackjack application, and follows the same rules as the physical card
game. The goal is to beat the dealer's hand without going over a point total of
21. 

### Game play

The game starts out with 2 cards from a standard 52-card deck dealt face up to
the player and 2 cards dealt to the dealer, one face down and one face up. The
card point values are as follows:

Ace = 1 or 11 points
2, 3, … 10 = 2, 3, … 10 points
J, Q, K = 10 points

The player then must decide whether to “hit” (take another card) or “stand”
(end their turn). The player may continue to take cards as long as his total
point value is less than 21. Once the player decides not to take any more cards,
it is the dealer’s turn.

The dealer must continue to take cards until his total point value is at least
17; at this point the dealer cannot take any more cards.

If the point value of either the player or dealer exceeds 21, they are
said to have “busted” and cannot take any more cards.

The player wins if he has a higher number of points than the dealer without
exceeding 21, and they tie if they have the same number. Otherwise, the player
loses.

If the player busts, he loses, and the dealer doesn’t take his turn. If the
player or dealer is initially dealt a point value of 21, he has Blackjack, and
automatically wins unless the other player also has Blackjack, in which case
they tie. 


## Functional requirements

1. “Hit” button: The player will be able to press an on screen button to
indicate if he wants to “hit” and thus draw another card. 

2. “Stand” button: The player will be able to press an on screen button to
indicate he wants to “stand.” Hitting this button will then advance the turn to
the dealer. 

3. Hands and card layout: The player and dealer will each have their own
hands of cards that are drawn from the same standard deck. Card sprites will
appear on screen showing the hands, and the cards in each of the hands will
overlap each other like in a real game. The dealer’s hand will be displayed near
the top of the screen, while the player’s hand will be displayed in the middle
of the screen.

4. Random card generation: A standard deck of 52 cards will be generated and
shuffled before each round.

5. Dealer’s hit/stand algorithm: This decides when the dealer will “stand” and
when they will “hit.” Specifically, the dealer will “hit” if his point total is
less than 17; otherwise, he will “stand”.

6. Play again option: After each round the player can press the space bar to
play again.

7. Win/loss/push signal (including busts): The program will write text on the
screen telling the user who has won the game. If it is a tie, the program will
display “Push”, which is the Blackjack term for this occurrence.

8. Blackjack signal: The program will identify when a Blackjack occurs and will
display a message to the player.

9. Score counter dealer and player: There will be a number displayed to the
player, indicating the value his hand represents.

10. Dealer’s hand reveal: After the player stands, the dealer’s hidden card will
be revealed. Then the dealer will draw cards as necessary.

11. After each hand, the player can select between a variety of card colors
(which are mapped to certain keys), and the new hand will be played with a card
theme of the chosen color. For example, pressing "b" instead of space will start
a new game with blue cards. We will clearly show what keys produce what colors.

12. Ace value: An ace can be a value of 1 or a value of 11. The application will
automatically set the ace to the optimal value.


## Open questions

1. How we are going to add a timer for revealing the dealer’s hand and the
winner of the round?

2. How difficult would it be to animate moving/flipping of cards?

3. What is an efficient method for making a deck of cards? 

4. How do we reset the game after pressing the play again function?

5. Can we call functions defined in model in the model constructor?

6. Do we need an explicit constructor if there is nothing to initialize in it?
Would it be better to initialize in a constructor compared to our current setup?

