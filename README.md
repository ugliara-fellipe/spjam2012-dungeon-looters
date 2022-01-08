# Dungeon Looters - SPJAM 2012

## Introduction

The first version of this game was created during the SPjam 2012, a 48hs game 
development marathon that took place in Sao Paulo, Brazil, from August 31th to 
September 2nd. This is the improved post-marathon version of the game where we 
used some 48 additional hours to remove bugs, improve the gameplay, add new
graphics, sounds and music. We hope you like the final version as much as we
liked working on it (and playing it too!).


## The Game

This game is meant to be played by two players that need to cooperate in order
to reach the highest score possible. They must explore a random dungeon killing
monsters, collecting gold and using powerful items.

At the start of the game, both players receive a random character to control
from a pool of 3 possible classes: Warrior, Mage and Rogue. 

The Warrior has lots of health and has the strongest attack power but he lacks
attack range. The Mage has average health, a ranged attack with average power
but he lacks the speed to keep up with the other two classes. The Rogue is the
fastest class, he can also carry two items but he has a short ranged attack 
that lacks the attack power of the other two classes.

The dungeon is populated by dangerous monsters that will try to hinder the
player's progress. Some of them can be killed by all the three classes but there
are special monsters that can only be killed by specific classes. This is 
indicated by the symbols displayed above each monster and above each player. If
the monster has the same symbol as you, you can kill it with your attack. If 
the symbols are different, then your attack can't hurt the monster and you'll
need the help of the other player.

Hidden in the dungeons there are also lots of chests containing items that can
be used by the players. Items cannot be identified until they are collected by a 
player. When a player collects a chest, the item contained on it is displayed
at a free item slot owned by that player. 

Players can use theirs items at any time but the effect of the item will always
be provided to the other player. That means you cannot heal yourself with a 
health potion if you are one who collected it.

The game goal is to collect as much gold as possible in 90 seconds. When a
player dies or the time runs out, the game is over. Players can get gold by 
collecting gold bags, using items and killing monsters. 


## Items

Red Potion    - Gives 20 points of health to the other player
Purple Potion - Removes 15 points of health from the other player
Yellow Potion - Gives 20 points of speed to the other player
Green Potion  - Removes 15 points of speed from the other player
Blue Potion   - Swaps the characters of both players
Amulet        - Gives 5 attack power and changes the attack type of the
		other player to Mage
Boots         - Gives 5 attack power and changes the attack type of the
		other player to Rogue
Sword         - Gives 5 attack power and changes the attack type of the
	 	other player to Warrior


## Controls

***** Player 1 (Left player)

Start button  - 1
Movement      - W A S D
Attack button - R
Item 1 button - T
Item 2 button - Y

***** Player 2 (Right player)

Start button  - 2
Movement      - Arrow keys
Attack button - I
Item 1 button - O
Item 2 button - P

To start the game both players must press start together (1 + 2)


# Dev Guide

## Install in Linux

sudo apt install allegro5-dev ...

# Credits

* Game design and programming by

  Fellipe Augusto Ugliara - <ugliara.fellipe@gmail.com>  
  Jeferson Rodrigues da Silva - <jefrsilva@gmail.com>

* Graphics by

  Ronaldo Rodrigues da Silva - <polynaoh@gmail.com>

* Music by

  Alex Campos - A3 Studios - <alexmesilva@gmail.com>

