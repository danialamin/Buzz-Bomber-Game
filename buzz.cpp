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
void runGame(int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[5][20], float& player_x, float& player_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound, Sprite beeHiveSprites[20], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, Texture textureBeeMovingLeft, Texture textureBeeMovingRight, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]);
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, Sound fireSound);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite beeSprite);
void moveBee(float beePositions[5][20], Clock&, int, int[][gameRows*gameColumns], int[][gameRows*gameColumns], int& beeHiveArrayIndex, int& honeyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]);
void drawBee(RenderWindow&, float beePositions[5][20], Sprite beeSprites[20], int, Texture, Texture);
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[5][20], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound);
void drawHoneyCombs(int honeyCombArray[][gameRows*gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]);
void drawBeeHives(int beeHiveArray[][gameRows*gameColumns], int beeHiveArrayIndex, RenderWindow& window, Sprite beeHiveSprites[]);
void drawFlowers(RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]);

int main()
{
	srand(time(0));

	// Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX+14, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(180, 0));

	// Initializing Background Music.
	Music bgMusic;
	if (!bgMusic.openFromFile("Music/Music3.ogg")) {
	    cout << "Error: Could not load music file!" << endl;
	}
	bgMusic.setVolume(10.0f);
	bgMusic.setLoop(true);
	bgMusic.play();

  // Bee Bullet collision music
  SoundBuffer beeBulletCollisionBuffer;
  beeBulletCollisionBuffer.loadFromFile("./Sound Effects/hit.wav");
  Sound beeBulletCollisionSound;
  beeBulletCollisionSound.setBuffer(beeBulletCollisionBuffer);
  beeBulletCollisionSound.setVolume(90.0f);

  // Fire music
  SoundBuffer fireBuffer;
  fireBuffer.loadFromFile("./Sound Effects/fire.wav");
  Sound fireSound;
  fireSound.setBuffer(fireBuffer);

  // Beehive Bullet collision music
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
	float bullet_y = player_y; // so that bullet is one box above the player
	bool bullet_exists = false;

	Clock bulletClock;
	Texture bulletTexture;
	Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(2, 2);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// The regular bee sprite

	Clock beeClock;
  Clock gameClock;
  Time elapsed = gameClock.getElapsedTime();

  Texture textureBeeMovingLeft;
  textureBeeMovingLeft.loadFromFile("./Textures/Regular_bee.png");
  textureBeeMovingLeft.setSmooth(true);

  Texture textureBeeMovingRight;
  textureBeeMovingRight.loadFromFile("./Textures/Regular_bee_reversed.png");
  textureBeeMovingRight.setSmooth(true);
  Sprite beeSprites[20] = {Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite()};

  float beePositions[5][20];
  for (int i = 0; i < 20; i++) {
    beePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    beePositions[1][i] = 0; // bee_y
    beePositions[2][i] = 0; // moveDown flag
    beePositions[3][i] = static_cast<int>(beePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    beePositions[4][i] = 0; // isNextHoneyComb flag
  }

  // Honeycomb
  int honeyCombArray[2][gameRows*gameColumns] = {0};
  int honeyCombArrayIndex = 0;

  Texture honeyCombTexture;
  honeyCombTexture.loadFromFile("./Textures/honeycomb.png");
  honeyCombTexture.setSmooth(true);
  Sprite honeyCombSpriteArray[20];
  for (int i=0; i<20; i++) {
    honeyCombSpriteArray[i].setTexture(honeyCombTexture);
    honeyCombSpriteArray[i].setScale(0.5, 0.5);
  }

  // Beehives
  Texture beehiveTexture;
  beehiveTexture.loadFromFile("./Textures/hive.png");
  beehiveTexture.setSmooth(true);
  Sprite beeHiveSprites[20] = {Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite()};
  for (int i=0; i<20; i++) {
    beeHiveSprites[i].setTexture(beehiveTexture);
    beeHiveSprites[i].setScale(0.6, 0.5);
  }
  int beeHiveArrayIndex = 0;
  int beeHiveArray[2][gameRows*gameColumns] = {0};

  // Flowers
  Texture flowerTexture;
  flowerTexture.loadFromFile("./Textures/obstacles.png");
  flowerTexture.setSmooth(true);
  Sprite flowerSprite;
  flowerSprite.setTexture(flowerTexture);
  Sprite flowerSprites[gameColumns+1] = {flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite};
  int flowersArray[gameColumns+1] = {0};
  int flowersArrayIndex = 0;

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
          runGame(selectedLevel, playerSprite, bulletSprite, bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beeSprites, groundRectangle, window, boxPixelsX, beePositions, player_x, player_y, honeyCombArray, honeyCombArrayIndex, honeyCombSpriteArray, beeBulletCollisionSound, obstacleBulletCollisionSound, fireSound, beeHiveSprites, beeHiveArray, beeHiveArrayIndex, textureBeeMovingLeft, textureBeeMovingRight, flowersArray, flowersArrayIndex, flowerSprites);
          break;

      case EXIT_STATE:
          window.close();
          break;
    }

		window.display();

	}
}

void runGame(int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[5][20], float& player_x, float& player_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound, Sprite beeHiveSprites[20], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, Texture textureBeeMovingLeft, Texture textureBeeMovingRight, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]) {
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
              moveBee(beePositions, beeClocks[i], i, honeyCombArray, beeHiveArray, beeHiveArrayIndex, honeyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites);
              drawBee(window, beePositions, beeSprites, i, textureBeeMovingRight, textureBeeMovingLeft);
              checkBulletBeeCollision(bullet_x, bullet_y, beePositions, i, honeyCombArray, honeyCombArrayIndex, bullet_exists, beeBulletCollisionSound);
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
          drawFlowers(window, flowersArray, flowersArrayIndex, flowerSprites);
          drawBeeHives(beeHiveArray, beeHiveArrayIndex, window, beeHiveSprites);
          drawHoneyCombs(honeyCombArray, honeyCombArrayIndex, window, honeyCombSpriteArray);
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
void moveBee(float beePositions[5][20], Clock& beeClock, int i, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, int& honeyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]) {
  if (beeClock.getElapsedTime().asSeconds() < 0.3)
    return;

  beeClock.restart();

  if (beePositions[3][i]) { // if bee moving right
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 544) {
      // cout<< "reached bottom"<< endl;
          // cout<< beePositions[0][i]<< endl;
      bool flowerAlreadyDrawn = false;
      bool nextFlowerAlreadyDrawn = false;
      for (int a=0; a<gameColumns+1; a++) {
        if (flowersArray[a] == beePositions[0][i]) {
          flowerAlreadyDrawn = true;
        }
        if (flowersArray[a] == beePositions[0][i]+32 || beePositions[0][i] == 928) {
          nextFlowerAlreadyDrawn = true;
        }
      }
      if (!flowerAlreadyDrawn) {
        flowersArray[flowersArrayIndex] = beePositions[0][i];
        flowersArrayIndex++;
      }

      if (!nextFlowerAlreadyDrawn) {
        flowersArray[flowersArrayIndex] = beePositions[0][i]+32;
        flowersArrayIndex++;
      }
    }
    
    // Check if a beehive can be created
    for (int a=0; a<gameRows*gameColumns/6; a++) {
      if ((honeyCombArray[0][a] == beePositions[0][i]+32 && honeyCombArray[1][a] == beePositions[1][i]) || (beePositions[0][i] == resolutionX-32 ) || (beeHiveArray[0][a] == beePositions[0][i]+32 && beeHiveArray[1][a] == beePositions[1][i])) { // if a honeycomb or beehive is to the right or bee is at the edge of the screen
        for (int b=0; b<gameRows*gameColumns/6; b++) {
          if (((honeyCombArray[0][b] == beePositions[0][i]) && (honeyCombArray[1][b] == beePositions[1][i]+32)) || (beeHiveArray[0][b] == beePositions[0][i]) && (beeHiveArray[1][b] == beePositions[1][i]+32)) { // if honeycomb or beehive is below the bee as well
            beeHiveArray[0][beeHiveArrayIndex] = beePositions[0][i];
            beeHiveArray[1][beeHiveArrayIndex] = beePositions[1][i];
            beeHiveArrayIndex++;
            beePositions[1][i] = 9999999; // bee sent down the screen
          }
        }
      }
    }

    // Check if there is a honeycomb or beehive next
    for (int a=0; a<gameColumns; a++) {
      if ((honeyCombArray[0][a] == beePositions[0][i]+32 && honeyCombArray[1][a] == beePositions[1][i]) || (beeHiveArray[0][a] == beePositions[0][i]+32 && beeHiveArray[1][a] == beePositions[1][i])) { // if a honeycomb is next then move down
        beePositions[4][i] = 1; // isNextHoneyComb flag set to true
      }
    }

    if (beePositions[4][i]) {
      beePositions[1][i] += boxPixelsY;  // Move down to next row
      beePositions[4][i] = 0; // isHoneyCombNext flag set to false
      beePositions[3][i] = 0; // Move right set to false
      return;
    }
        
    // Check if reached right edge
    if (beePositions[0][i] == resolutionX-32 && !beePositions[2][i]) {
      beePositions[2][i] = 1;
      return;
    } else if (beePositions[0][i] == resolutionX-32 && beePositions[2][i]) {
      beePositions[1][i] += boxPixelsY;  // Move down to next row
      beePositions[3][i] = 0; // move right set to false
      beePositions[2][i] = 0; // move down set to false
      return;
    }

    // Move right 32 px
    if (beePositions[0][i] < resolutionX-32)
      beePositions[0][i] += boxPixelsX;

  } else { // if bee moving left
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 544) {
      // cout<< "reached bottom"<< endl;
      bool flowerAlreadyDrawn = false;
      bool nextFlowerAlreadyDrawn = false;
      for (int a=0; a<gameColumns+1; a++) {
        if (flowersArray[a] == beePositions[0][i]) {
          flowerAlreadyDrawn = true;
        }
        if (flowersArray[a] == beePositions[0][i]+32 || beePositions[0][i] == 928) {
          nextFlowerAlreadyDrawn = true;
        }
      }
      if (!flowerAlreadyDrawn) {
        flowersArray[flowersArrayIndex] = beePositions[0][i];
        flowersArrayIndex++;
      }

      if (!nextFlowerAlreadyDrawn) {
        flowersArray[flowersArrayIndex] = beePositions[0][i]+32;
        flowersArrayIndex++;
      }
    }

    // Check if a beehive can be created
    for (int a=0; a<gameColumns; a++) {
      if ((honeyCombArray[0][a] == beePositions[0][i]-32 && honeyCombArray[1][a] == beePositions[1][i]) || (beePositions[0][i] == 0 ) || (beeHiveArray[0][a] == beePositions[0][i]-32 && beeHiveArray[1][a] == beePositions[1][i])) { // if a honeycomb is to the left or bee is at the edge of the screen
        for (int b=0; b<gameColumns; b++) {
          if (((honeyCombArray[0][b] == beePositions[0][i]) && (honeyCombArray[1][b] == beePositions[1][i]+32)) || ((beeHiveArray[0][b] == beePositions[0][i]) && (beeHiveArray[1][b] == beePositions[1][i]+32))) { // if honeycomb is below the bee as well
            beeHiveArray[0][beeHiveArrayIndex] = beePositions[0][i];
            beeHiveArray[1][beeHiveArrayIndex] = beePositions[1][i];
            beeHiveArrayIndex++;
            beePositions[1][i] = 9999999; // bee sent down the screen
          }
        }
      }
    }

    // Check if there is a honeycomb or beehive next
    for (int a=0; a<gameColumns; a++) {
      if ((honeyCombArray[0][a] == beePositions[0][i]-32 && honeyCombArray[1][a] == beePositions[1][i]) || (beeHiveArray[0][a] == beePositions[0][i]-32 && beeHiveArray[1][a] == beePositions[1][i])) { // if a honeycomb is next then move down
        beePositions[4][i] = 1; // isNextHoneyComb flag set to true
      }
    }

    if (beePositions[4][i]) {
      beePositions[1][i] += boxPixelsY;  // Move down to next row
      beePositions[4][i] = 0; // isHoneyCombNext flag set to false
      beePositions[3][i] = 1; // Move right set to true
      return;
    }

    // Check if reached left edge
    bool FlowerOnFirstCol = false;
    if (beePositions[0][i] == 0 && !beePositions[2][i]) {
      beePositions[2][i] = 1;
      if (beePositions[1][i] == 544) {
        for (int a=0; a<flowersArrayIndex; a++) {
          if (flowersArray[a] == 0) {
            FlowerOnFirstCol = true;
          }
        }
        if (!FlowerOnFirstCol) {
          flowersArray[flowersArrayIndex] = 0;
          flowersArrayIndex++;
        }
      }
      return;
    } else if (beePositions[0][i] == 0 && beePositions[2][i]) {
      beePositions[1][i] += boxPixelsY;  // Move down to next row
      beePositions[3][i] = 1; // move right set to true
      beePositions[2][i] = 0; // move down set to false
      return;
    }

    // Move left 32 px
    if (beePositions[0][i] > 0)
      beePositions[0][i] -= boxPixelsX;

  }
}

// Drawing function for a bee
void drawBee(RenderWindow& window, float beePositions[5][20], Sprite beeSprites[20], int i, Texture textureBeeMovingRight, Texture textureBeeMovingLeft) { 
    if (beePositions[3][i]) {
      beeSprites[i].setTexture(textureBeeMovingRight);
      
    } else {
      beeSprites[i].setTexture(textureBeeMovingLeft);
    }

    beeSprites[i].setPosition(beePositions[0][i], beePositions[1][i]);

    window.draw(beeSprites[i]);
}

// Checks collision between bullet and bee
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[5][20], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound) {
  // due to the bee's different size on front and back, I have to check in which direction the bee is moving
  
  if (beePositions[1][i] != 512) { // to prevent collision with the player
  if (beePositions[3][i]) { // if moving right
    if (bullet_x >= beePositions[0][i]-10.45 && bullet_x <= beePositions[0][i]+30 && bullet_y == beePositions[1][i]) { // if collision occurs
        honeyCombArray[0][honeyCombArrayIndex] = bullet_x;
        honeyCombArray[1][honeyCombArrayIndex] = bullet_y;
        honeyCombArrayIndex++;
        beePositions[1][i] = 99999999; // bee sent down the screen
        bullet_exists = false;
        // play the music
        beeBulletCollisionSound.play();
        sleep(seconds(0.1)); // so that the sound can be heard
      } 
    } else { // bee moving left
        if (bullet_x >= beePositions[0][i]-30 && bullet_x <= beePositions[0][i]+10.45 && bullet_y == beePositions[1][i]) { // if collision occurs
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
  }
}

void drawHoneyCombs(int honeyCombArray[][gameRows*gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]) {
  for (int i=0; i<honeyCombArrayIndex; i++) {
    honeyCombSpriteArray[i].setPosition(honeyCombArray[0][i], honeyCombArray[1][i]);

    window.draw(honeyCombSpriteArray[i]);
  }
}

void drawBeeHives(int beeHiveArray[][gameRows*gameColumns], int beeHiveArrayIndex, RenderWindow& window, Sprite beeHiveSprites[]) {
  for (int i=0; i<beeHiveArrayIndex; i++) {
    beeHiveSprites[i].setPosition(beeHiveArray[0][i], beeHiveArray[1][i]);
    window.draw(beeHiveSprites[i]);
  }
}

void drawFlowers(RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]) {
  for (int i=0; i<flowersArrayIndex; i++) {
    flowerSprites[i].setPosition(flowersArray[i], 544);
    window.draw(flowerSprites[i]);
  }
}