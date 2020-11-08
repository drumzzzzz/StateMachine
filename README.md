CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Usage
 * Maintainers


INTRODUCTION
------------

A simple text based game that demonstrates a state machine design pattern project for UWGB Computer Science Fall semester, 2020.
Reads a game level consisting of integer values from a file and plays a game according to the states 


USAGE
------------
    The game level file contains a vertical list of integers with values from 1 to 10 that represents 
    the following objects the player encounters and the resultant state that is set:

    Value   Description         State
    1       Path                Walking
    2       Monster chasing     Running
    3       Monster Sleeping    Sneaking
    4       Log                 Jumping
    5       Boulder             Climbing
    6       Apple               Eating
    7       Snake               Jumping
    8       Tree                Climbing
    9       Game Start          Game Start
    10      Game End            Game End

    Game Example:
    9
    1
    2
    8
    10

MAINTAINERS
-----------

 * Nathaniel Kennis - https://github.com/drumzzzzz

