#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionY / boxPixelsX; //20: Total rows on grid
const int gameColumns = resolutionX / boxPixelsY; //30: Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {}; // gameGrid is a 2d array with the exact same shape as the grid of the game

void drawMenu(RenderWindow& window, int& selectedOption, int currentState);
int handleMenuInput(RenderWindow& window, int& selectedOption, int& currentState);
void drawLevelSelect(RenderWindow& window, int& selectedLevel, int& currentState);
int handleLevelSelectInput(RenderWindow& window, int& selectedLevel, int& currentState);
void initializeGameResources();
void runGame(int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[][20], float& player_x, float& player_y, int honeyCombArray[][gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound);
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, Sound fireSound);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite beeSprite);
void moveBee(float beePositions[4][20], Clock&, int);
void drawBee(RenderWindow&, float beePositions[4][20], Sprite beeSprites[20], int);
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[][20], int i, int honeyCombArray[gameRows][gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound);
void drawHoneyCombs(int honeyCombArray[gameRows][gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]);

int main()
{
	srand(time(0));

	// Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX+20, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(180, 0));

	// Initializing Background Music.
	Music bgMusic;
	if (!bgMusic.openFromFile("Music/Music3.ogg")) {
	    cout << "Error: Could not load music file!" << endl;
	}
	bgMusic.setVolume(5000.0f);
	bgMusic.setLoop(true);
	bgMusic.play();

  // Bee Bullet collision music
  SoundBuffer beeBulletCollisionBuffer;
  beeBulletCollisionBuffer.loadFromFile("./Sound Effects/hit.wav");
  Sound beeBulletCollisionSound;
  beeBulletCollisionSound.setBuffer(beeBulletCollisionBuffer);
  beeBulletCollisionSound.setVolume(25.0f);

  // Fire music
  SoundBuffer fireBuffer;
  fireBuffer.loadFromFile("./Sound Effects/fire.wav");
  Sound fireSound;
  fireSound.setBuffer(fireBuffer);

  // Obstacle Bullet collision music
  SoundBuffer obstacleBulletCollisionBuffer;
  obstacleBulletCollisionBuffer.loadFromFile("./Sound Effects/Obstacle.wav");
  Sound obstacleBulletCollisionSound;
  obstacleBulletCollisionSound.setBuffer(obstacleBulletCollisionBuffer);

	// Initializing Player and Player Sprites.
	float player_x = (gameColumns / 2) * boxPixelsX;
	float player_y = (gameRows - 4) * boxPixelsY;

	Texture playerTexture;
	Sprite playerSprite;
	playerTexture.loadFromFile("Textures/spray.png");
  playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	//playerSprite.setTextureRect(IntRect(0, 0, boxPixelsX, boxPixelsY));

	// Initializing Bullet and Bullet Sprites
	// Data for bullet / Spray pellet

	float bullet_x = player_x;
	float bullet_y = player_y-32; // so that bullet is one box above the player
	bool bullet_exists = false;

	Clock bulletClock;
	Texture bulletTexture;
	Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(2, 2);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// The bee sprite

	Clock beeClock;
  Clock gameClock;
  Time elapsed = gameClock.getElapsedTime();
	Texture beeTexture;
	beeTexture.loadFromFile("Textures/Regular_bee.png");
  beeTexture.setSmooth(true);

  Sprite beeSprites[20];
  for (int i = 0; i < 20; i++) {
    Sprite beeSprite;
  	beeSprite.setTexture(beeTexture);
	  beeSprite.setScale(1.15, 1.15);
    beeSprites[i] = beeSprite;
  }
  float beePositions[4][20];
  for (int i = 0; i < 20; i++) {
    beePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    beePositions[1][i] = 0; // bee_y
    beePositions[2][i] = 0; // moveDown flag
    beePositions[3][i] = static_cast<int>(beePositions[0][i])==0 ? 1 : 0; // bee_moving_right
  }

  // Honeycomb
  int honeyCombArray[gameRows][gameColumns] = {0};
  int honeyCombArrayIndex = 0;

  Texture honeyCombTexture;
  honeyCombTexture.loadFromFile("./Textures/honeycomb.png");
  honeyCombTexture.setSmooth(true);
  Sprite honeyCombSpriteArray[20];
  for (int i=0; i<20; i++) {
    honeyCombSpriteArray[i].setTexture(honeyCombTexture);
    honeyCombSpriteArray[i].setScale(0.5, 0.5);
  }

	// The ground on which player moves

	RectangleShape groundRectangle(Vector2f(980, 64));
	groundRectangle.setPosition(0, (gameRows - 2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Green);

	// Implementing menu system
	const int MENU_STATE = 0;
	const int LEVEL_SELECT_STATE = 1;
	const int GAME_STATE = 2;
	const int EXIT_STATE = 3;
	int currentState = MENU_STATE;
	int selectedOption = 0;
  int selectedLevel = 0;


	while (window.isOpen()) {

		window.clear();
		switch (currentState) {
      case MENU_STATE:
          drawMenu(window, selectedOption, currentState);
          handleMenuInput(window, selectedOption, currentState);
          break;

      case LEVEL_SELECT_STATE:
          drawLevelSelect(window, selectedLevel, currentState);
          handleLevelSelectInput(window, selectedLevel, currentState);
          break;

      case GAME_STATE:
          runGame(selectedLevel, playerSprite, bulletSprite, bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beeSprites, groundRectangle, window, boxPixelsX, beePositions, player_x, player_y, honeyCombArray, honeyCombArrayIndex, honeyCombSpriteArray, beeBulletCollisionSound, obstacleBulletCollisionSound, fireSound);
          break;

      case EXIT_STATE:
          window.close();
          break;
    }

		window.display();

	}
}

void runGame(int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[][20], float& player_x, float& player_y, int honeyCombArray[][gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound) {
    // Using selectedLevel to modify game difficulty

    switch (selectedLevel) {
        case 0:
    	    Event e;
          while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
              exit(0);
              return;
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Right) {
              if (static_cast<int>(player_x)!=928) {
                player_x+=boxPixelsX;
                bullet_x+= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Left) {
              if (static_cast<int>(player_x)!=0) {
                player_x-=boxPixelsX;
                bullet_x-= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
              if (!bullet_exists) { // so that the sound is played only once
                fireSound.play();
                sleep(seconds(0.1)); // so that the sound can be heard
              }
              bullet_exists = true;
            }
          }
          float seconds = gameClock.getElapsedTime().asSeconds();

          static Clock beeClocks[20] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 20; i++) {
            if (seconds>(1.0f+static_cast<float>(i)/.5f)) {
              moveBee(beePositions, beeClocks[i], i);
              drawBee(window, beePositions, beeSprites, i);
              // HEREEEEEEEEEEEEEEEEEE!!!
              checkBulletBeeCollision(bullet_x, bullet_y, beePositions, i, honeyCombArray, honeyCombArrayIndex, bullet_exists, beeBulletCollisionSound);
              drawHoneyCombs(honeyCombArray, honeyCombArrayIndex, window, honeyCombSpriteArray);
            }
          }

          if (bullet_exists)
          {
            moveBullet(bullet_y, bullet_exists, bulletClock, fireSound);
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
          }
          else
          {
            bullet_x = player_x;
            bullet_y = player_y;
          }

          drawPlayer(window, player_x, player_y, playerSprite);
          window.draw(groundRectangle);
          break;
        // case 1:
        //     cout<< "hello2"<< endl;
        //     break;
        // case 2:
        //     cout<< "hello3"<< endl;
        //     break;
    }
}


// function that displays the menu
void drawMenu(RenderWindow& window, int& selectedOption, int currentState) {
	Font menuFont;
    menuFont.loadFromFile("Fonts/arial.ttf");

    // Title
    Text titleText;
	  titleText.setString("Buzz Bombers");
	  titleText.setFont(menuFont);
	  titleText.setCharacterSize(50);
    titleText.setPosition(
      resolutionX/2 - 180,        
      150
    );
    titleText.setFillColor(Color::White);

    // Menu Options
    string menuOptions[] = {"Start Game", "Choose Level", "Exit"};
    Text optionTexts[3];

    for (int i = 0; i < 3; i++) {
        optionTexts[i].setString(menuOptions[i]);
        optionTexts[i].setCharacterSize(30);
        optionTexts[i].setPosition(
            resolutionX/2 - 100, 
            250 + i * 50
        );
		    optionTexts[i].setFont(menuFont);
        
        // Highlight selected option
        optionTexts[i].setFillColor(
            (i == selectedOption) ? Color::Yellow : Color::White
        );

        window.draw(optionTexts[i]);
    }

    window.draw(titleText);
}

// function that handles after user selects an option
int handleMenuInput(RenderWindow& window, int& selectedOption, int& currentState) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return 3;
        }

        // Keyboard input for menu navigation
        if (event.type == Event::KeyPressed) {
            switch (event.key.code) {
                case Keyboard::Up:
                    selectedOption = (selectedOption + 2) % 3;
                    break;
                case Keyboard::Down:
                    selectedOption = (selectedOption + 1) % 3;
                    break;
                case Keyboard::Enter:
                    switch (selectedOption) {
                        case 0: // Start Game
                            currentState = 2; // GAME_STATE
                            return 2;
                        case 1: // Choose Level
                            currentState = 1; // LEVEL_SELECT_STATE
                            return 1;
                        case 2: // Exit
                            currentState = 3; // EXIT_STATE
                            return 3;
                    }
                    break;
            }
        }
    }
    return currentState;
}

// Function to draw level select
void drawLevelSelect(RenderWindow& window, int& selectedLevel, int& currentState) {
    Font menuFont;
    menuFont.loadFromFile("Fonts/arial.ttf");

    // Title
    Text titleText("SELECT LEVEL", menuFont, 50);
    titleText.setPosition(
        resolutionX/2 - 180, 
        160
    );
    titleText.setFillColor(Color::White);

    // Level Options
    string levelOptions[] = {"Level 1", "Level 2", "Level 3"};
    Text levelTexts[3];

    for (int i = 0; i < 3; i++) {
        levelTexts[i].setFont(menuFont);
        levelTexts[i].setString(levelOptions[i]);
        levelTexts[i].setCharacterSize(30);
        levelTexts[i].setPosition(
            resolutionX/2 - 50, 
            250 + i * 50
        );
        
        // Highlight selected level
        levelTexts[i].setFillColor(
            (i == selectedLevel) ? Color::Yellow : Color::White
        );

        window.draw(levelTexts[i]);
    }

    window.draw(titleText);
}

// functionality after level has been selected by the user
int handleLevelSelectInput(RenderWindow& window, int& selectedLevel, int& currentState) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return 3; // EXIT_STATE
        }

        // Keyboard input for level selection
        if (event.type == Event::KeyPressed) {
            switch (event.key.code) {
                case Keyboard::Up:
                    selectedLevel = (selectedLevel - 1 + 3) % 3;
                    break;
                case Keyboard::Down:
                    selectedLevel = (selectedLevel + 1) % 3;
                    break;
                case Keyboard::Enter:
                    currentState = 2; // GAME_STATE
                    return 2;
                case Keyboard::Escape:
                    currentState = 0; // MENU_STATE
                    return 0;
            }
        }
    }
    return currentState;
}

// for displaying the trash can
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite) {
	playerSprite.setPosition(player_x, player_y);
	window.draw(playerSprite);
}
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, Sound fireSound) {
	if (bulletClock.getElapsedTime().asMilliseconds() < 20)
		return;

	bulletClock.restart();
	bullet_y -= 16;
	if (bullet_y < -32)
		bullet_exists = false;
}
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite bulletSprite) {
	bulletSprite.setPosition(bullet_x, bullet_y);
	window.draw(bulletSprite);
}

// function to move bee
void moveBee(float beePositions[4][20], Clock& beeClock, int i) {
    if (beeClock.getElapsedTime().asSeconds() < 0.3) {
  		return;  // Wait before next movement
    }

	  beeClock.restart();

    if (beePositions[3][i]) { // if bee moving right
		if (beePositions[0][i] < resolutionX-32)
	        beePositions[0][i] += boxPixelsX;
        
        // Check if reached right edge
        if (beePositions[0][i] == resolutionX-32 && !beePositions[2][i]) {
			      beePositions[2][i] = 1;
        } else if (beePositions[0][i] == resolutionX-32 && beePositions[2][i]) {
			      beePositions[1][i] += boxPixelsY;  // Move down to next row
            beePositions[3][i] = 0;
			      beePositions[2][i] = 0;
		}
    } else { // if bee moving left
		if (beePositions[0][i] > 0)
            beePositions[0][i] -= boxPixelsX;

        // Check if reached right edge
        if (beePositions[0][i] == 0 && !beePositions[2][i]) {
            beePositions[2][i] = 1;
        } else if (beePositions[0][i] == 0 && beePositions[2][i]) {
            beePositions[1][i] += boxPixelsY;  // Move down to next row
            beePositions[3][i] = 1;
            beePositions[2][i] = 0;
        }    

	}
    
    // Reset to top if reached bottom

    // if (bee_current_row > 16) {
    //     bee_x = 0;  // Or use a random start position
    //     bee_y = 0;
    //     bee_current_row = 0;
    //     bee_moving_right = true;
    // }
}

// Drawing function for a bee
void drawBee(RenderWindow& window, float beePositions[][20], Sprite beeSprites[20], int i) {
    beeSprites[i].setPosition(beePositions[0][i], beePositions[1][i]);
    window.draw(beeSprites[i]);
}

// Checks collision between bullet and bee
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[][20], int i, int honeyCombArray[gameRows][gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound) {
  if (bullet_x >= beePositions[0][i]-10.45 && bullet_x <= beePositions[0][i]+35 && bullet_y == beePositions[1][i]) { // if collision occurs
    honeyCombArray[0][honeyCombArrayIndex] = bullet_x;
    honeyCombArray[1][honeyCombArrayIndex] = bullet_y;
    honeyCombArrayIndex++;
    beePositions[1][i] = 99999999; // bee sent down the screen
    bullet_exists = false;
    // play the music
    beeBulletCollisionSound.play();
    sleep(seconds(0.1)); // so that the sound can be heard
  }
}

void drawHoneyCombs(int honeyCombArray[gameRows][gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]) {
  for (int i=0; i<honeyCombArrayIndex; i++) {
    honeyCombSpriteArray[i].setPosition(honeyCombArray[0][i], honeyCombArray[1][i]);
    window.draw(honeyCombSpriteArray[i]);
  }
}