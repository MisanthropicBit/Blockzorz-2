Version log
===========

1.0 beta
--------
- Entered beta phase.

1.1 beta
--------
- When swapping, adjacent blocks are now checked for death.


1.2 beta
---------
- Fixed some music and sound issues
- When disabling music or sound from gameplay, the settings now carry over to the menu when the game is finished or intentionally exited.
- The music/sound buttons in gameplay now display the correct animation frame depending on the current settings.

1.0
---
- Any key press now returns you to the main menu from the How to play menu and the Options menu
- Highscore messages now display the proper postfix fater the number, e.g. "1st", "2nd" etc.
- Fixed a bug where blocks would not get cleared and not count as a combo.
- Combos now award you 20 points instead of 7. Also fixed combo score counting that was a bit broken
- Fixed a bug where 4 block combos would award the same amount of combo points as any other combo
- Added biocomv2b.ttf to the Fonts folder, since it was missing and used to display "name", "score", "combos" and "time" text under the Highscores menu.
- Made a few minor fixes to the methods for checking blocks and swapping them
- Made major code revisions for the Block::Update(...) method
- The Easter Egg can now be turned off by doing the exact same thing that initially turned it on
- Added internal flags to the AudioManager class because SDL_Mixer's flags for pausing/playing were not working correctly
- Improved the speed of the particle effect engine
- Rewrote and added new parts to the Credits.txt and Readme.txt files
- The .zip file now extracts to a folder instead of all individual files (Google code)
