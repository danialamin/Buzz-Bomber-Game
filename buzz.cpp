#include <iostream>
#include <cmath> // for taking square root and abs()
#include <cstring> // for converting int datatype to string
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 704;
const int resolutionY = 576;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionY / boxPixelsX; //20: Total rows on grid
const int gameColumns = resolutionX / boxPixelsY; //22: Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {}; // gameGrid is a 2d array with the exact same shape as the grid of the game

void drawMenu(RenderWindow& window, int& selectedOption, int currentState);
int handleMenuInput(RenderWindow& window, int& selectedOption, int& currentState);
void drawLevelSelect(RenderWindow& window, int& selectedLevel, int& currentState);
int handleLevelSelectInput(RenderWindow& window, int& selectedLevel, int& currentState);
void initializeGameResources();
void runGame(int& currentState, int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[5][20], float& player_x, float& player_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound, Sprite beeHiveSprites[40], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, Texture textureBeeMovingLeft, Texture textureBeeMovingRight, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], Sound, Texture TextureBirdRight, Texture TextureBirdLeft, Texture TextureBirdStill, Sprite& hummingBirdSprite, Sound hummingBirdSound, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, RectangleShape bigRectangles[], float rectangleHeights[], int& numberOfRectangles, int& score, bool&, Music&, Clock& fastBeeClock, Texture TextureFastBeeMovingLeft, Texture TextureFastBeeMovingRight, Sprite fastBeeSprites[], float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, Texture redHoneyCombTexture, Sprite redHoneyCombSpriteArray[], int& totalShots, bool& scoreGreaterThan20k, bool& scoreGreaterThan40k, bool& scoreGreaterThan80k, bool& scoreGreaterThan160k, bool& scoreGreaterThan240k, bool& scoreGreaterThan320k);
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, Sound fireSound);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite beeSprite);
void moveBee(float beePositions[5][20], Clock&, int, int[][gameRows*gameColumns], int[][gameRows*gameColumns], int& beeHiveArrayIndex, int& honeyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], int redHoneyCombArray[][gameRows*gameColumns]);
void drawBee(RenderWindow&, float beePositions[5][20], Sprite beeSprites[20], int, Texture, Texture);
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[5][20], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score);
void drawHoneyCombs(int honeyCombArray[][gameRows*gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]);
void drawBeeHives(int beeHiveArray[][gameRows*gameColumns], int beeHiveArrayIndex, RenderWindow& window, Sprite beeHiveSprites[]);
void drawFlowers(RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]);
void checkBulletHoneyCombCollision(float bullet_x, float bullet_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic);
void checkBulletBeeHiveCollision(float bullet_x, float bullet_y, int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic);
void checkBulletBirdCollision(int bullet_x, int bullet_y, Sound hummingBirdSound, int& bulletCollisionCount, Clock& respawnClock, bool&, Sprite&, int& moveToX, int& moveToY);
void moveHummingBird(int& moveToX, int& moveToY, Sprite& hummingBirdSprite, Texture TextureBirdRight, Texture TextureBirdLeft, Texture TextureBirdStill);
void drawSprayCans(RenderWindow& window, RectangleShape bigRectangles[], float rectangleHeights[], int& numberOfRectangles, int& bulletCount);
void determineBirdMovement(Clock& gameClock, Clock& movementClock, Clock& respawnClock, int& moveToX, int& moveToY, int& movementCount, bool& combFound, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, int& score, Texture TextureBirdRight, Texture TextureBirdLeft, Sprite&, bool& redCombFound, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex);
void drawScore(RenderWindow& window, int score);
int checkLevelComplete(float beePositions[][20], int flowersArrayIndex, int bulletCount, int selectedLevel, float fastBeePositions[][10], int totalShots);
int drawNameInput(RenderWindow& window, char* name, int maxLength, int& charCount);
void resetForLevel1(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[5][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots);
void countHivePoints(int beeHiveArray[][gameRows*gameColumns], int beeHiveArrayIndex, int& score);
void moveFastBee(float beePositions[][10], Clock& fastBeeClock, int i, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]);
void drawFastBee(RenderWindow& window, float beePositions[][10], Sprite fastBeeSprites[], int i, Texture textureFastBeeMovingRight, Texture textureFastBeeMovingLeft);
void checkBulletFastBeeCollision(int bullet_x, int bullet_y, float fastBeePositions[][10], int i, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score);
void drawRedHoneyCombs(int honeyCombArray[][gameRows*gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]);
void checkBulletRedHoneyCombCollision(float bullet_x, float bullet_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic);
void resetForLevel2(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[5][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots);
void resetForLevel3(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[5][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots, int selectedLevel);
void determineNumberOfRectangles(int& numberOfRectangles, int bulletCount, int score, int& totalShots, bool& scoreGreaterThan20k, bool& scoreGreaterThan40k, bool& scoreGreaterThan80k, bool& scoreGreaterThan160k, bool& scoreGreaterThan240k, bool& scoreGreaterThan320k);

int main()
{
	srand(time(0));

	// Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX+14, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(180, 0));

	// Declaring different buffers and sounds
	Music bgMusic;
	
  SoundBuffer beeBulletCollisionBuffer;
  beeBulletCollisionBuffer.loadFromFile("./Sound Effects/hit.wav");
  Sound beeBulletCollisionSound;
  beeBulletCollisionSound.setBuffer(beeBulletCollisionBuffer);
  beeBulletCollisionSound.setVolume(90.0f);

  SoundBuffer fireBuffer;
  fireBuffer.loadFromFile("./Sound Effects/fire.wav");
  Sound fireSound;
  fireSound.setBuffer(fireBuffer);

  SoundBuffer honeyCombOrBeeHiveBuffer;
  honeyCombOrBeeHiveBuffer.loadFromFile("./Sound Effects/Obstacle.wav");
  Sound honeyCombOrBeeHiveMusic;
  honeyCombOrBeeHiveMusic.setBuffer(honeyCombOrBeeHiveBuffer);

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
  playerSprite.setOrigin(playerTexture.getSize().x / 4.0f, 0);

	// Initializing Bullet and Bullet Sprites

	float bullet_x = player_x;
	float bullet_y = player_y;
	bool bullet_exists = false;
  int bulletCount = 0;
  int totalShots = 168;

	Clock bulletClock;
	Texture bulletTexture;
	Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
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

  // The fast bee sprite
  Clock fastBeeClock;
  Texture textureFastBeeMovingLeft;
  textureFastBeeMovingLeft.loadFromFile("./Textures/Fast_bee.png");
  textureFastBeeMovingLeft.setSmooth(true);

  Texture textureFastBeeMovingRight;
  textureFastBeeMovingRight.loadFromFile("./Textures/Fast_bee_reversed.png");
  textureFastBeeMovingRight.setSmooth(true);
  Sprite fastBeeSprites[10] = {Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite()};

  float fastBeePositions[5][10];
  for (int i = 0; i < 10; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
  }

  // Honeycomb
  int honeyCombArray[2][gameRows*gameColumns];
  int honeyCombArrayIndex = 0;

  Texture honeyCombTexture;
  honeyCombTexture.loadFromFile("./Textures/honeycomb.png");
  honeyCombTexture.setSmooth(true);
  Sprite honeyCombSpriteArray[100];
  for (int i=0; i<100; i++) {
    honeyCombSpriteArray[i].setTexture(honeyCombTexture);
  }

  // Red Honeycomb
  int redHoneyCombArray[2][gameRows*gameColumns];
  int redHoneyCombArrayIndex = 0;

  Texture redHoneyCombTexture;
  redHoneyCombTexture.loadFromFile("./Textures/honeycomb_red.png");
  redHoneyCombTexture.setSmooth(true);
  Sprite redHoneyCombSpriteArray[100];
  for (int i=0; i<100; i++) {
    redHoneyCombSpriteArray[i].setTexture(redHoneyCombTexture);
  }

  // Beehives
  Texture beehiveTexture;
  beehiveTexture.loadFromFile("./Textures/hive.png");
  beehiveTexture.setSmooth(true);
  Sprite beeHiveSprites[40] = {Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite()};
  for (int i=0; i<40; i++) {
    beeHiveSprites[i].setTexture(beehiveTexture);
  }
  int beeHiveArrayIndex = 0;
  int beeHiveArray[2][gameRows*gameColumns] = {0};

  // Flowers
  Texture flowerTexture;
  flowerTexture.loadFromFile("./Textures/obstacles.png");
  flowerTexture.setSmooth(true);
  Sprite flowerSprite;
  flowerSprite.setTexture(flowerTexture);
  Sprite flowerSprites[gameColumns+2] = {flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite, flowerSprite};
  int flowersArray[gameColumns+2] = {0};
  int flowersArrayIndex = 0;

  // humming bird

  Texture TextureBirdRight;
  TextureBirdRight.loadFromFile("./Textures/bird1.png");
  Texture TextureBirdLeft;
  TextureBirdLeft.loadFromFile("./Textures/bird2.png");
  Texture TextureBirdStill;
  TextureBirdStill.loadFromFile("./Textures/bird3.png");
  TextureBirdRight.setSmooth(true);
  TextureBirdLeft.setSmooth(true);
  TextureBirdStill.setSmooth(true);
  Sprite hummingBirdSprite;
  hummingBirdSprite.setPosition(-100, -100);
  hummingBirdSprite.setTexture(TextureBirdRight);

  SoundBuffer buffer;
  buffer.loadFromFile("./Sound Effects/hummingBirdSound.wav");
  Sound hummingBirdSound(buffer);

  Clock movementClock;
  Clock bulletCollisionClock;
  Clock respawnClock;

  int movementCount = 0;
  int bulletCollisionCount = 0;

  // Spray cans

  RectangleShape bigRectangles[20];
  float rectangleHeights[20];
  int numberOfRectangles=2; // 2 rectangles at the bottom at the start of the game
  bool scoreGreaterThan20k = false;
  bool scoreGreaterThan40k = false;
  bool scoreGreaterThan80k = false;
  bool scoreGreaterThan160k = false;
  bool scoreGreaterThan240k = false;
  bool scoreGreaterThan320k = false;

  // Score counter
  int score = 0;

  // powerups
  int powerUpsArray[4][400]; // first row is for if the powerup is active, second row is for the type of the powerup, third is for the x position and fourth is for the y position
  Sprite powerUpsSprites[400];
  int powerUpsArrayIndex = 0;

	// The ground on which player moves

	RectangleShape groundRectangle(Vector2f(980, 64));
	groundRectangle.setPosition(0, (gameRows - 2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Green);

	// Implementing menu system
  const int ENTER_NAME = -1;
	const int MENU_STATE = 0;
	const int LEVEL_SELECT_STATE = 1;
	const int GAME_STATE = 2;
	const int EXIT_STATE = 3;
	int currentState = MENU_STATE;
	int selectedOption = 0;
  int selectedLevel = 0;

  // first time for when a new level starts
  static bool firstTime = true;

  // name of the user
  char name[30];
  int charCount = 0;

	while (window.isOpen()) {
		switch (currentState) {
      case ENTER_NAME:
          window.clear();

          currentState = drawNameInput(window, name, 30, charCount);
          break;
      case MENU_STATE:
          window.clear();
          drawMenu(window, selectedOption, currentState);
          handleMenuInput(window, selectedOption, currentState);
          break;

      case LEVEL_SELECT_STATE:
          window.clear();
          drawLevelSelect(window, selectedLevel, currentState);
          handleLevelSelectInput(window, selectedLevel, currentState);
          break;

      case GAME_STATE:
          runGame(currentState,selectedLevel, playerSprite, bulletSprite, bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beeSprites, groundRectangle, window, boxPixelsX, beePositions, player_x, player_y, honeyCombArray, honeyCombArrayIndex, honeyCombSpriteArray, beeBulletCollisionSound, obstacleBulletCollisionSound, fireSound, beeHiveSprites, beeHiveArray, beeHiveArrayIndex, textureBeeMovingLeft, textureBeeMovingRight, flowersArray, flowersArrayIndex, flowerSprites, honeyCombOrBeeHiveMusic, TextureBirdRight, TextureBirdLeft, TextureBirdStill, hummingBirdSprite, hummingBirdSound, movementClock, bulletCollisionClock, respawnClock, movementCount, bulletCollisionCount, bulletCount, bigRectangles, rectangleHeights, numberOfRectangles, score, firstTime, bgMusic, fastBeeClock, textureFastBeeMovingLeft, textureFastBeeMovingRight, fastBeeSprites, fastBeePositions, redHoneyCombArray, redHoneyCombArrayIndex, redHoneyCombTexture, redHoneyCombSpriteArray, totalShots, scoreGreaterThan20k, scoreGreaterThan40k, scoreGreaterThan80k, scoreGreaterThan160k, scoreGreaterThan240k, scoreGreaterThan320k);
          break;


      case EXIT_STATE:
          window.close();
          break;
    }

		window.display();

	}
}
void runGame(int& currentState, int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[5][20], float& player_x, float& player_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound, Sprite beeHiveSprites[], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, Texture textureBeeMovingLeft, Texture textureBeeMovingRight, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], Sound honeyCombOrBeeHiveMusic, Texture TextureBirdRight, Texture TextureBirdLeft, Texture TextureBirdStill, Sprite& hummingBirdSprite, Sound hummingBirdSound, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, RectangleShape bigRectangles[], float rectangleHeights[], int& numberOfRectangles, int& score, bool& firstTime, Music& bgMusic, Clock& fastBeeClock, Texture TextureFastBeeMovingLeft, Texture TextureFastBeeMovingRight, Sprite fastBeeSprites[], float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, Texture redHoneyCombTexture, Sprite redHoneyCombSpriteArray[], int& totalShots, bool& scoreGreaterThan20k, bool& scoreGreaterThan40k, bool& scoreGreaterThan80k, bool& scoreGreaterThan160k, bool& scoreGreaterThan240k, bool& scoreGreaterThan320k) {
    // Using selectedLevel to modify game difficulty
    if (selectedLevel==0) {
          window.clear();

          // resetting variables according to requirements of level 1
          if (firstTime) {
            resetForLevel1(bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beePositions, player_x, player_y, honeyCombArrayIndex, beeHiveArrayIndex, flowersArrayIndex, hummingBirdSprite, movementClock, bulletCollisionClock, respawnClock, movementCount, bulletCollisionCount, bulletCount, rectangleHeights, numberOfRectangles, firstTime, honeyCombArray, beeHiveArray, flowersArray, bgMusic, fastBeePositions, redHoneyCombArray, redHoneyCombArrayIndex, totalShots);
          }

          firstTime = false;

          // the hopping logic of the player
          bool isOnObstacle = false; // isOnObstacle set to true if player is on a flower
          for (int a=0; a<flowersArrayIndex; a++) {
            if (player_x == flowersArray[a]) {
              isOnObstacle = true;
            }
          }
          int player_x_right = -1;
          int player_x_left = -1;
          if (isOnObstacle) {
            for (int b=player_x; b<=672; b+=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_right = b;
                break;
              }
            }
            

            for (int b=player_x; b>=0; b-=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_left = b;
                break;
              }
            }

            // Choose the closer unflowered space
            if (player_x_right == -1) {
                player_x = player_x_left;
            } else if (player_x_left == -1) {
                player_x = player_x_right;
            } else {
                player_x = (player_x - player_x_left > player_x_right - player_x) 
                    ? player_x_right 
                    : player_x_left;
            }
          }

          // y = 99999999 if shot AND y = 9999999 if humming bird pollinates it
          // determining where humming bird needs to go
          static int moveToX = -1, moveToY = -1;
          static bool combFound = false; // combfound is true if the humming bird found a honeycomb to go
          static bool redCombFound = false; // redcombfound is true if the humming bird found a red honeycomb to go
          determineBirdMovement(gameClock, movementClock, respawnClock, moveToX, moveToY, movementCount, combFound, honeyCombArray, honeyCombArrayIndex, score, TextureBirdRight, TextureBirdLeft, hummingBirdSprite, redCombFound, redHoneyCombArray, redHoneyCombArrayIndex);

          // move humming bird
          moveHummingBird(moveToX, moveToY, hummingBirdSprite, TextureBirdRight, TextureBirdLeft, TextureBirdStill);

    	    Event e;
          while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
              exit(0);
              return;
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Right) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the right
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x+32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=672 && !isObstacle) {
                player_x+=boxPixelsX;
                bullet_x+= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Left) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the left
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x-32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=0 && !isObstacle) {
                player_x-=boxPixelsX;
                bullet_x-= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
              if (!bullet_exists && bulletCount<totalShots) {
                fireSound.play();
                sleep(seconds(0.1)); // so that the sound can be heard
                bulletCount++;
                bullet_exists = true; 
                determineNumberOfRectangles(numberOfRectangles, bulletCount, score, totalShots, scoreGreaterThan20k,scoreGreaterThan40k, scoreGreaterThan80k, scoreGreaterThan160k, scoreGreaterThan240k, scoreGreaterThan320k);
              }
            }
          }
          float seconds = gameClock.getElapsedTime().asSeconds();

          static Clock beeClocks[20] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 20; i++) {
            if (seconds>(1.0f+static_cast<float>(i)/.5f)) {
              moveBee(beePositions, beeClocks[i], i, honeyCombArray, beeHiveArray, beeHiveArrayIndex, honeyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites, redHoneyCombArray);
              drawBee(window, beePositions, beeSprites, i, textureBeeMovingRight, textureBeeMovingLeft);
              checkBulletBeeCollision(bullet_x, bullet_y, beePositions, i, honeyCombArray, honeyCombArrayIndex, bullet_exists, beeBulletCollisionSound, score);
            }
          }

          if (bullet_exists)
          {
            moveBullet(bullet_y, bullet_exists, bulletClock, fireSound);
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
            checkBulletHoneyCombCollision(bullet_x, bullet_y, honeyCombArray, honeyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBeeHiveCollision(bullet_x, bullet_y, beeHiveArray, beeHiveArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBirdCollision(bullet_x, bullet_y, hummingBirdSound, bulletCollisionCount, respawnClock, bullet_exists, hummingBirdSprite, moveToX, moveToY);
          }
          else
          {
            bullet_x = player_x;
            bullet_y = player_y; 
          }

          // drawing different stuff
          drawPlayer(window, player_x, player_y, playerSprite);
          window.draw(groundRectangle);
          drawScore(window, score);
          drawSprayCans(window, bigRectangles, rectangleHeights, numberOfRectangles, bulletCount);
          drawFlowers(window, flowersArray, flowersArrayIndex, flowerSprites);
          drawBeeHives(beeHiveArray, beeHiveArrayIndex, window, beeHiveSprites);
          drawHoneyCombs(honeyCombArray, honeyCombArrayIndex, window, honeyCombSpriteArray);
          window.draw(hummingBirdSprite);

          // checking if the level is complete OR the user has lost OR move to next level
          int level1Complete = checkLevelComplete(beePositions, flowersArrayIndex, bulletCount, selectedLevel, fastBeePositions, totalShots); // returns 0 for lose, 1 for restart, 2 for win, 3 for continue with the current level, 4 for winning the last level
          
          if (level1Complete !=3 ) { // level has finished
            countHivePoints(beeHiveArray, beeHiveArrayIndex, score);
          }

          if (level1Complete == 2) {
            selectedLevel = 1;
            firstTime = true;
          } else if (level1Complete == 0) {
            currentState = -1;
          } else if (level1Complete == 1) {
            // subtract one spray can and restart the game
            totalShots-=56;
            numberOfRectangles-=1;
            firstTime = true;
          }

    } else if (selectedLevel==1) {
          window.clear(sf::Color(0,0,139));
          
          // resetting variables according to requirements of level 2
          if (firstTime) {
            resetForLevel2(bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beePositions, player_x, player_y, honeyCombArrayIndex, beeHiveArrayIndex, flowersArrayIndex, hummingBirdSprite, movementClock, bulletCollisionClock, respawnClock, movementCount, bulletCollisionCount, bulletCount, firstTime, honeyCombArray, beeHiveArray, flowersArray, bgMusic, fastBeePositions, redHoneyCombArray, redHoneyCombArrayIndex, totalShots);
          }

          firstTime = false;

          // the hopping logic of the player
          bool isOnObstacle = false; // isOnObstacle set to true if player is on a flower
          for (int a=0; a<flowersArrayIndex; a++) {
            if (player_x == flowersArray[a]) {
              isOnObstacle = true;
            }
          }
          int player_x_right = -1;
          int player_x_left = -1;
          if (isOnObstacle) {
            for (int b=player_x; b<=672; b+=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_right = b;
                break;
              }
            }
            

            for (int b=player_x; b>=0; b-=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_left = b;
                break;
              }
            }

            // Choose the closer unflowered space
            if (player_x_right == -1) {
                player_x = player_x_left;
            } else if (player_x_left == -1) {
                player_x = player_x_right;
            } else {
                player_x = (player_x - player_x_left > player_x_right - player_x) 
                    ? player_x_right 
                    : player_x_left;
            }
          }

          // y = 99999999 if shot AND y = 9999999 if humming bird pollinates it
          // determining where humming bird needs to go
          static int moveToX = -1, moveToY = -1;
          static bool combFound = false; // combfound is true if the humming bird found a honeycomb to go
          static bool redCombFound = false; // redcombfound is true if the humming bird found a red honeycomb to go
          determineBirdMovement(gameClock, movementClock, respawnClock, moveToX, moveToY, movementCount, combFound, honeyCombArray, honeyCombArrayIndex, score, TextureBirdRight, TextureBirdLeft, hummingBirdSprite, redCombFound, redHoneyCombArray, redHoneyCombArrayIndex);

          // move humming bird
          moveHummingBird(moveToX, moveToY, hummingBirdSprite, TextureBirdRight, TextureBirdLeft, TextureBirdStill);

    	    Event e;
          while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
              exit(0);
              return;
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Right) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the right
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x+32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=672 && !isObstacle) {
                player_x+=boxPixelsX;
                bullet_x+= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Left) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the left
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x-32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=0 && !isObstacle) {
                player_x-=boxPixelsX;
                bullet_x-= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
              if (!bullet_exists && bulletCount<totalShots) {
                fireSound.play();
                sleep(seconds(0.03)); // so that the sound can be heard
                bulletCount++;
                bullet_exists = true; 
                determineNumberOfRectangles(numberOfRectangles, bulletCount, score, totalShots, scoreGreaterThan20k, scoreGreaterThan40k, scoreGreaterThan80k, scoreGreaterThan160k, scoreGreaterThan240k, scoreGreaterThan320k);
              }
            }
          }
          float seconds = gameClock.getElapsedTime().asSeconds();

          static Clock beeClocks[15] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 15; i++) {
            if (seconds>(1.0f+static_cast<float>(i)/.5f)) {
              moveBee(beePositions, beeClocks[i], i, honeyCombArray, beeHiveArray, beeHiveArrayIndex, honeyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites, redHoneyCombArray);
              drawBee(window, beePositions, beeSprites, i, textureBeeMovingRight, textureBeeMovingLeft);
              checkBulletBeeCollision(bullet_x, bullet_y, beePositions, i, honeyCombArray, honeyCombArrayIndex, bullet_exists, beeBulletCollisionSound, score);
            }
          }

          static Clock fastBeeClocks[5] = {Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 5; i++) {
            if (seconds>(5.0f+static_cast<float>(i)/.25f)) {
              moveFastBee(fastBeePositions, fastBeeClocks[i], i, redHoneyCombArray, redHoneyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites);
              drawFastBee(window, fastBeePositions, fastBeeSprites, i, TextureFastBeeMovingRight, TextureFastBeeMovingLeft);
              checkBulletFastBeeCollision(bullet_x, bullet_y, fastBeePositions, i, redHoneyCombArray, redHoneyCombArrayIndex, bullet_exists, beeBulletCollisionSound, score);
            }
          }

          if (bullet_exists)
          {
            moveBullet(bullet_y, bullet_exists, bulletClock, fireSound);
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
            checkBulletHoneyCombCollision(bullet_x, bullet_y, honeyCombArray, honeyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletRedHoneyCombCollision(bullet_x, bullet_y, redHoneyCombArray, redHoneyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBeeHiveCollision(bullet_x, bullet_y, beeHiveArray, beeHiveArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBirdCollision(bullet_x, bullet_y, hummingBirdSound, bulletCollisionCount, respawnClock, bullet_exists, hummingBirdSprite, moveToX, moveToY);
          }
          else
          {
            bullet_x = player_x;
            bullet_y = player_y; 
          }

          // drawing different stuff
          drawPlayer(window, player_x, player_y, playerSprite);
          window.draw(groundRectangle);
          drawScore(window, score);
          drawSprayCans(window, bigRectangles, rectangleHeights, numberOfRectangles, bulletCount);
          drawFlowers(window, flowersArray, flowersArrayIndex, flowerSprites);
          drawBeeHives(beeHiveArray, beeHiveArrayIndex, window, beeHiveSprites);
          drawHoneyCombs(honeyCombArray, honeyCombArrayIndex, window, honeyCombSpriteArray);
          drawRedHoneyCombs(redHoneyCombArray, redHoneyCombArrayIndex, window, redHoneyCombSpriteArray);
          window.draw(hummingBirdSprite);

          // checking if the level is complete OR the user has lost OR move to next level
          int level2Complete = checkLevelComplete(beePositions, flowersArrayIndex, bulletCount, selectedLevel, fastBeePositions, totalShots); // returns 0 for lose, 1 for restart, 2 for win, 3 for continue with the current level, 4 for winning the last level
          // counting bee hive score at the end of the level
          if (level2Complete != 3) { // level has finished
            countHivePoints(beeHiveArray, beeHiveArrayIndex, score);
          }

          if (level2Complete == 2) {
            selectedLevel = 2;
            firstTime = true;
          } else if (level2Complete == 0) {
            currentState = -1;
          } else if (level2Complete == 1) {
            // subtract one spray can and restart the game
            totalShots-=56;
            numberOfRectangles-=1;
            firstTime = true;
          }

    }else if (selectedLevel==2) {
          window.clear(sf::Color(255, 140, 0));
          
          // resetting variables according to requirements of level 3
          if (firstTime) {
            resetForLevel3(bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beePositions, player_x, player_y, honeyCombArrayIndex, beeHiveArrayIndex, flowersArrayIndex, hummingBirdSprite, movementClock, bulletCollisionClock, respawnClock, movementCount, bulletCollisionCount, bulletCount, rectangleHeights, numberOfRectangles, firstTime, honeyCombArray, beeHiveArray, flowersArray, bgMusic, fastBeePositions, redHoneyCombArray, redHoneyCombArrayIndex, totalShots, selectedLevel);
          }

          firstTime = false;

          // the hopping logic of the player
          bool isOnObstacle = false; // isOnObstacle set to true if player is on a flower
          for (int a=0; a<flowersArrayIndex; a++) {
            if (player_x == flowersArray[a]) {
              isOnObstacle = true;
            }
          }
          int player_x_right = -1;
          int player_x_left = -1;
          if (isOnObstacle) {
            for (int b=player_x; b<=672; b+=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_right = b;
                break;
              }
            }
            

            for (int b=player_x; b>=0; b-=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_left = b;
                break;
              }
            }

            // Choose the closer unflowered space
            if (player_x_right == -1) {
                player_x = player_x_left;
            } else if (player_x_left == -1) {
                player_x = player_x_right;
            } else {
                player_x = (player_x - player_x_left > player_x_right - player_x) 
                    ? player_x_right 
                    : player_x_left;
            }
          }

          // y = 99999999 if shot AND y = 9999999 if humming bird pollinates it
          // determining where humming bird needs to go
          static int moveToX = -1, moveToY = -1;
          static bool combFound = false; // combfound is true if the humming bird found a honeycomb to go
          static bool redCombFound = false; // redcombfound is true if the humming bird found a red honeycomb to go
          determineBirdMovement(gameClock, movementClock, respawnClock, moveToX, moveToY, movementCount, combFound, honeyCombArray, honeyCombArrayIndex, score, TextureBirdRight, TextureBirdLeft, hummingBirdSprite, redCombFound, redHoneyCombArray, redHoneyCombArrayIndex);

          // move humming bird
          moveHummingBird(moveToX, moveToY, hummingBirdSprite, TextureBirdRight, TextureBirdLeft, TextureBirdStill);

    	    Event e;
          while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
              exit(0);
              return;
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Right) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the right
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x+32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=672 && !isObstacle) {
                player_x+=boxPixelsX;
                bullet_x+= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Left) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the left
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x-32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=0 && !isObstacle) {
                player_x-=boxPixelsX;
                bullet_x-= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
              if (!bullet_exists && bulletCount<totalShots) {
                fireSound.play();
                sleep(seconds(0.03)); // so that the sound can be heard
                bulletCount++;
                bullet_exists = true; 
                determineNumberOfRectangles(numberOfRectangles, bulletCount, score, totalShots, scoreGreaterThan20k, scoreGreaterThan40k, scoreGreaterThan80k, scoreGreaterThan160k, scoreGreaterThan240k, scoreGreaterThan320k);
              }
            }
          }
          float seconds = gameClock.getElapsedTime().asSeconds();

          static Clock beeClocks[20] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 20; i++) {
            if (seconds>(1.0f+static_cast<float>(i)/.5f)) {
              moveBee(beePositions, beeClocks[i], i, honeyCombArray, beeHiveArray, beeHiveArrayIndex, honeyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites, redHoneyCombArray);
              drawBee(window, beePositions, beeSprites, i, textureBeeMovingRight, textureBeeMovingLeft);
              checkBulletBeeCollision(bullet_x, bullet_y, beePositions, i, honeyCombArray, honeyCombArrayIndex, bullet_exists, beeBulletCollisionSound, score);
            }
          }

          static Clock fastBeeClocks[10] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 10; i++) {
            if (seconds>(5.0f+static_cast<float>(i)/.25f)) {
              moveFastBee(fastBeePositions, fastBeeClocks[i], i, redHoneyCombArray, redHoneyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites);
              drawFastBee(window, fastBeePositions, fastBeeSprites, i, TextureFastBeeMovingRight, TextureFastBeeMovingLeft);
              checkBulletFastBeeCollision(bullet_x, bullet_y, fastBeePositions, i, redHoneyCombArray, redHoneyCombArrayIndex, bullet_exists, beeBulletCollisionSound, score);
            }
          }

          if (bullet_exists)
          {
            moveBullet(bullet_y, bullet_exists, bulletClock, fireSound);
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
            checkBulletHoneyCombCollision(bullet_x, bullet_y, honeyCombArray, honeyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletRedHoneyCombCollision(bullet_x, bullet_y, redHoneyCombArray, redHoneyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBeeHiveCollision(bullet_x, bullet_y, beeHiveArray, beeHiveArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBirdCollision(bullet_x, bullet_y, hummingBirdSound, bulletCollisionCount, respawnClock, bullet_exists, hummingBirdSprite, moveToX, moveToY);
          }
          else
          {
            bullet_x = player_x;
            bullet_y = player_y; 
          }

          // drawing different stuff
          drawPlayer(window, player_x, player_y, playerSprite);
          window.draw(groundRectangle);
          drawScore(window, score);
          drawSprayCans(window, bigRectangles, rectangleHeights, numberOfRectangles, bulletCount);
          drawFlowers(window, flowersArray, flowersArrayIndex, flowerSprites);
          drawBeeHives(beeHiveArray, beeHiveArrayIndex, window, beeHiveSprites);
          drawHoneyCombs(honeyCombArray, honeyCombArrayIndex, window, honeyCombSpriteArray);
          drawRedHoneyCombs(redHoneyCombArray, redHoneyCombArrayIndex, window, redHoneyCombSpriteArray);
          window.draw(hummingBirdSprite);

          // checking if the level is complete OR the user has lost OR move to next level
          int level3Complete = checkLevelComplete(beePositions, flowersArrayIndex, bulletCount, selectedLevel, fastBeePositions, totalShots); // returns 0 for lose, 1 for restart, 2 for win, 3 for continue with the current level, 4 for winning the last level
          // counting bee hive score at the end of the level
          if (level3Complete != 3) { // level has finished
            countHivePoints(beeHiveArray, beeHiveArrayIndex, score);
          }

          if (level3Complete == 2) {
            selectedLevel = 3;
            firstTime = true;
          } else if (level3Complete == 0) {
            currentState = -1;
          } else if (level3Complete == 1) {
            // subtract one spray can and restart the game
            totalShots-=56;
            numberOfRectangles-=1;
            firstTime = true;
          }
    } else if (selectedLevel==3) {
            window.clear(sf::Color(1, 50, 32));
          
          // resetting variables according to requirements of level 3
          if (firstTime) {
            resetForLevel3(bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beePositions, player_x, player_y, honeyCombArrayIndex, beeHiveArrayIndex, flowersArrayIndex, hummingBirdSprite, movementClock, bulletCollisionClock, respawnClock, movementCount, bulletCollisionCount, bulletCount, rectangleHeights, numberOfRectangles, firstTime, honeyCombArray, beeHiveArray, flowersArray, bgMusic, fastBeePositions, redHoneyCombArray, redHoneyCombArrayIndex, totalShots, selectedLevel);
          }

          firstTime = false;

          // the hopping logic of the player
          bool isOnObstacle = false; // isOnObstacle set to true if player is on a flower
          for (int a=0; a<flowersArrayIndex; a++) {
            if (player_x == flowersArray[a]) {
              isOnObstacle = true;
            }
          }
          int player_x_right = -1;
          int player_x_left = -1;
          if (isOnObstacle) {
            for (int b=player_x; b<=672; b+=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_right = b;
                break;
              }
            }
            

            for (int b=player_x; b>=0; b-=32) {
              bool isMoveable = true;
              for (int c=0; c<flowersArrayIndex; c++) {
                if (flowersArray[c] == b) {
                  isMoveable = false;
                  break;
                }
              }
              if (isMoveable) {
                player_x_left = b;
                break;
              }
            }

            // Choose the closer unflowered space
            if (player_x_right == -1) {
                player_x = player_x_left;
            } else if (player_x_left == -1) {
                player_x = player_x_right;
            } else {
                player_x = (player_x - player_x_left > player_x_right - player_x) 
                    ? player_x_right 
                    : player_x_left;
            }
          }

          // y = 99999999 if shot AND y = 9999999 if humming bird pollinates it
          // determining where humming bird needs to go
          static int moveToX = -1, moveToY = -1;
          static bool combFound = false; // combfound is true if the humming bird found a honeycomb to go
          static bool redCombFound = false; // redcombfound is true if the humming bird found a red honeycomb to go
          determineBirdMovement(gameClock, movementClock, respawnClock, moveToX, moveToY, movementCount, combFound, honeyCombArray, honeyCombArrayIndex, score, TextureBirdRight, TextureBirdLeft, hummingBirdSprite, redCombFound, redHoneyCombArray, redHoneyCombArrayIndex);

          // move humming bird
          moveHummingBird(moveToX, moveToY, hummingBirdSprite, TextureBirdRight, TextureBirdLeft, TextureBirdStill);

    	    Event e;
          while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
              exit(0);
              return;
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Right) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the right
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x+32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=672 && !isObstacle) {
                player_x+=boxPixelsX;
                bullet_x+= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Left) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the left
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x-32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=0 && !isObstacle) {
                player_x-=boxPixelsX;
                bullet_x-= bullet_exists ? 0 : boxPixelsX;
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
              if (!bullet_exists && bulletCount<totalShots) {
                fireSound.play();
                sleep(seconds(0.03)); // so that the sound can be heard
                bulletCount++;
                bullet_exists = true; 
                determineNumberOfRectangles(numberOfRectangles, bulletCount, score, totalShots, scoreGreaterThan20k, scoreGreaterThan40k, scoreGreaterThan80k, scoreGreaterThan160k, scoreGreaterThan240k, scoreGreaterThan320k);
              }
            }
          }
          float seconds = gameClock.getElapsedTime().asSeconds();

          static Clock beeClocks[20] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 20; i++) {
            if (seconds>(1.0f+static_cast<float>(i)/.5f)) {
              moveBee(beePositions, beeClocks[i], i, honeyCombArray, beeHiveArray, beeHiveArrayIndex, honeyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites, redHoneyCombArray);
              drawBee(window, beePositions, beeSprites, i, textureBeeMovingRight, textureBeeMovingLeft);
              checkBulletBeeCollision(bullet_x, bullet_y, beePositions, i, honeyCombArray, honeyCombArrayIndex, bullet_exists, beeBulletCollisionSound, score);
            }
          }

          static Clock fastBeeClocks[10] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 10; i++) {
            if (seconds>(5.0f+static_cast<float>(i)/.25f)) {
              moveFastBee(fastBeePositions, fastBeeClocks[i], i, redHoneyCombArray, redHoneyCombArrayIndex, window, flowersArray, flowersArrayIndex, flowerSprites);
              drawFastBee(window, fastBeePositions, fastBeeSprites, i, TextureFastBeeMovingRight, TextureFastBeeMovingLeft);
              checkBulletFastBeeCollision(bullet_x, bullet_y, fastBeePositions, i, redHoneyCombArray, redHoneyCombArrayIndex, bullet_exists, beeBulletCollisionSound, score);
            }
          }

          if (bullet_exists)
          {
            moveBullet(bullet_y, bullet_exists, bulletClock, fireSound);
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
            checkBulletHoneyCombCollision(bullet_x, bullet_y, honeyCombArray, honeyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletRedHoneyCombCollision(bullet_x, bullet_y, redHoneyCombArray, redHoneyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBeeHiveCollision(bullet_x, bullet_y, beeHiveArray, beeHiveArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBirdCollision(bullet_x, bullet_y, hummingBirdSound, bulletCollisionCount, respawnClock, bullet_exists, hummingBirdSprite, moveToX, moveToY);
          }
          else
          {
            bullet_x = player_x;
            bullet_y = player_y; 
          }

          // drawing different stuff
          drawPlayer(window, player_x, player_y, playerSprite);
          window.draw(groundRectangle);
          drawScore(window, score);
          drawSprayCans(window, bigRectangles, rectangleHeights, numberOfRectangles, bulletCount);
          drawFlowers(window, flowersArray, flowersArrayIndex, flowerSprites);
          drawBeeHives(beeHiveArray, beeHiveArrayIndex, window, beeHiveSprites);
          drawHoneyCombs(honeyCombArray, honeyCombArrayIndex, window, honeyCombSpriteArray);
          drawRedHoneyCombs(redHoneyCombArray, redHoneyCombArrayIndex, window, redHoneyCombSpriteArray);
          window.draw(hummingBirdSprite);

          // checking if the level is complete OR the user has lost OR the user has won OR continue OR restart the current level
          int level3Complete = checkLevelComplete(beePositions, flowersArrayIndex, bulletCount, selectedLevel, fastBeePositions, totalShots); // returns 0 for lose, 1 for restart, 2 for win, 3 for continue with the current level, 4 for winning the last level
          // counting bee hive score at the end of the level
          if (level3Complete != 3) { // level has finished
            countHivePoints(beeHiveArray, beeHiveArrayIndex, score);
          }

          if (level3Complete == 2) {
            selectedLevel = 3;
            firstTime = true;
          } else if (level3Complete == 0) {
            currentState = -1;
          } else if (level3Complete == 1) {
            // subtract one spray can and restart the game
            totalShots-=56;
            numberOfRectangles-=1;
            firstTime = true;
          } 
    }
    
    
}

// function that displays the name input page
int drawNameInput(RenderWindow& window, char* name, int maxLength, int& charCount) {
    Font menuFont;
    menuFont.loadFromFile("Fonts/arial.ttf");

    // display "enter your name"
    Text nameInputText;
    nameInputText.setString("Enter your name:");
    nameInputText.setFont(menuFont);
    nameInputText.setCharacterSize(40);
    nameInputText.setPosition(resolutionX/2-150, 200);
    nameInputText.setFillColor(Color::White);

    // nameText
    Text nameText;
	  nameText.setString("Buzz Bombers");
	  nameText.setFont(menuFont);
	  nameText.setCharacterSize(30);
    nameText.setPosition(resolutionX/2-110, 270);
    nameText.setFillColor(Color::White);
    window.draw(nameInputText);

    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (event.type == Event::TextEntered) {
            if (event.text.unicode < 128 && charCount < maxLength - 1) {
                if (event.text.unicode == '\b' && charCount > 0) {
                    // Backspace
                    name[--charCount] = '\0';
                } else if (event.text.unicode != '\b' && event.text.unicode != '\r') {
                    // Regular character input
                    name[charCount++] = event.text.unicode;
                    name[charCount] = '\0';
                }
            }
        }

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && charCount != 0) {
            cout<< "name: "<< name<< endl;
            return 0; // 0 for MENU_STATE
        }
    }

    nameText.setString(name);
    
    if (charCount != 0) {
      window.draw(nameText);
    }
    
    return -1; // -1 for name input state
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

// function that draws the score
void drawScore(RenderWindow& window, int score) {
  Font menuFont;
  menuFont.loadFromFile("Fonts/arial.ttf");
  Text scoreText; 
  scoreText.setFont(menuFont);
  scoreText.setCharacterSize(30);
  scoreText.setPosition(resolutionX - 125, 526);
  scoreText.setFillColor(Color::Black);
  scoreText.setString(to_string(score));
  window.draw(scoreText);
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
	if (bullet_y <= -32)
		bullet_exists = false;
}
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite bulletSprite) {
	bulletSprite.setPosition(bullet_x, bullet_y);
	window.draw(bulletSprite);
}

// function to move bee
void moveBee(float beePositions[5][20], Clock& beeClock, int i, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, int& honeyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], int redHoneyCombArray[][gameRows*gameColumns]) {
  if (beeClock.getElapsedTime().asSeconds() < 0.16)
    return;

  beeClock.restart();

  if (beePositions[3][i]) { // if bee moving right
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 448 || beePositions[1][i] == 480) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]+32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]+32 <= 672 && beePositions[0][i]+32 >= 0) {
            flowersArray[flowersArrayIndex] = beePositions[0][i]+32;
            flowersArrayIndex++;

            if (beePositions[0][i]+32 == 32) {
              flowersArray[flowersArrayIndex] = 0;
              flowersArrayIndex++;
            }

            if (beePositions[0][i]+32 == 640) {
              flowersArray[flowersArrayIndex] = 672;
              flowersArrayIndex++;
            }

            // set bee's y position to 99999999 AFTER creating flowers
            beePositions[1][i] = 99999999;
        }
    }
    
    // Check if a beehive can be created
    for (int a=0; a<gameRows*gameColumns/6; a++) {
      if ((honeyCombArray[0][a] == beePositions[0][i]+32 && honeyCombArray[1][a] == beePositions[1][i]) || (beePositions[0][i] == resolutionX-32 ) || (beeHiveArray[0][a] == beePositions[0][i]+32 && beeHiveArray[1][a] == beePositions[1][i]) || (redHoneyCombArray[0][a] == beePositions[0][i]+32 && redHoneyCombArray[1][a] == beePositions[1][i])) { // if a honeycomb or beehive is to the right or bee is at the edge of the screen
        for (int b=0; b<gameRows*gameColumns/6; b++) {
          if (((honeyCombArray[0][b] == beePositions[0][i]) && (honeyCombArray[1][b] == beePositions[1][i]+32)) || (beeHiveArray[0][b] == beePositions[0][i]) && (beeHiveArray[1][b] == beePositions[1][i]+32) || ((redHoneyCombArray[0][b] == beePositions[0][i]) && (redHoneyCombArray[1][b] == beePositions[1][i]+32))) { // if honeycomb or beehive is below the bee as well
            beeHiveArray[0][beeHiveArrayIndex] = beePositions[0][i];
            beeHiveArray[1][beeHiveArrayIndex] = beePositions[1][i];
            beeHiveArrayIndex++;
            beePositions[1][i] = 99999999; // bee sent down the screen
          }
        }
      }
    }

    // Check if there is a honeycomb or beehive next
    for (int a=0; a<gameColumns; a++) {
      if ((honeyCombArray[0][a] == beePositions[0][i]+32 && honeyCombArray[1][a] == beePositions[1][i]) || (beeHiveArray[0][a] == beePositions[0][i]+32 && beeHiveArray[1][a] == beePositions[1][i]) || (redHoneyCombArray[0][a] == beePositions[0][i]+32 && redHoneyCombArray[1][a] == beePositions[1][i])) { // if a honeycomb is next then move down
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
    if (beePositions[0][i] < resolutionX-32)  { 
    if (static_cast<int>(rand()%10) > 2) // 8/10 chance of moving right
      beePositions[0][i] += boxPixelsX;
    else 
      beePositions[0][i] += 0;
    }
  } else { // if bee moving left
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 448 || beePositions[1][i] == 480) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]-32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]-32 <= 672 && beePositions[0][i]-32 >= 0) {
            flowersArray[flowersArrayIndex] = beePositions[0][i]-32;
            flowersArrayIndex++;

            if (beePositions[0][i]-32 == 32) {
              flowersArray[flowersArrayIndex] = 0;
              flowersArrayIndex++;
            }

            if (beePositions[0][i]-32 == 640) {
              flowersArray[flowersArrayIndex] = 672;
              flowersArrayIndex++;
            }

            // set bee's y position to 9999999 AFTER creating flowers
            beePositions[1][i] = 9999999;
        }
    }

    // Check if a beehive can be created
    for (int a=0; a<gameColumns; a++) {
      if ((honeyCombArray[0][a] == beePositions[0][i]-32 && honeyCombArray[1][a] == beePositions[1][i]) || (beePositions[0][i] == 0 ) || (beeHiveArray[0][a] == beePositions[0][i]-32 && beeHiveArray[1][a] == beePositions[1][i]) || (redHoneyCombArray[0][a] == beePositions[0][i]-32 && redHoneyCombArray[1][a] == beePositions[1][i])) { // if a honeycomb is to the left or bee is at the edge of the screen
        for (int b=0; b<gameColumns; b++) {
          if (((honeyCombArray[0][b] == beePositions[0][i]) && (honeyCombArray[1][b] == beePositions[1][i]+32)) || ((beeHiveArray[0][b] == beePositions[0][i]) && (beeHiveArray[1][b] == beePositions[1][i]+32)) || ((redHoneyCombArray[0][b] == beePositions[0][i]) && (redHoneyCombArray[1][b] == beePositions[1][i]+32))) { // if honeycomb or beehive is below the bee as well
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
      if ((honeyCombArray[0][a] == beePositions[0][i]-32 && honeyCombArray[1][a] == beePositions[1][i]) || (beeHiveArray[0][a] == beePositions[0][i]-32 && beeHiveArray[1][a] == beePositions[1][i]) || (redHoneyCombArray[0][a] == beePositions[0][i]-32 && redHoneyCombArray[1][a] == beePositions[1][i])) { // if a honeycomb is next then move down
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
    if (beePositions[0][i] == 0 && !beePositions[2][i]) {
      beePositions[2][i] = 1;
      return;
    } else if (beePositions[0][i] == 0 && beePositions[2][i]) {
      beePositions[1][i] += boxPixelsY;  // Move down to next row
      beePositions[3][i] = 1; // move right set to true
      beePositions[2][i] = 0; // move down set to false
      return;
    }

    // Move left 32 px
    if (beePositions[0][i] > 0)  { 
      if (static_cast<int>(rand()%10) > 2) // 8/10 chance of moving left
        beePositions[0][i] -= boxPixelsX;
      else 
        beePositions[0][i] -= 0;
    }

  }
}

// moving fast bee

void moveFastBee(float beePositions[][10], Clock& fastBeeClock, int i, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]) {
  if (fastBeeClock.getElapsedTime().asSeconds() < 0.02)
    return;

  fastBeeClock.restart();

  if (beePositions[3][i]) { // if bee moving right
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 448 || beePositions[1][i] == 480) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]+32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]+32 <= 672 && beePositions[0][i]+32 >= 0) {
            flowersArray[flowersArrayIndex] = beePositions[0][i]+32;
            flowersArrayIndex++;

            if (beePositions[0][i]+32 == 32) {
              flowersArray[flowersArrayIndex] = 0;
              flowersArrayIndex++;
            }

            if (beePositions[0][i]+32 == 640) {
              flowersArray[flowersArrayIndex] = 672;
              flowersArrayIndex++;
            }

            // set bee's y position to 99999999 AFTER creating flowers
            beePositions[1][i] = 99999999;
        }
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
    if (beePositions[0][i] < resolutionX-32)  { 
    beePositions[0][i] += boxPixelsX;
    }
  } else { // if bee moving left
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 448 || beePositions[1][i] == 480) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]-32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]-32 <= 672 && beePositions[0][i]-32 >= 0) {
            flowersArray[flowersArrayIndex] = beePositions[0][i]-32;
            flowersArrayIndex++;

            if (beePositions[0][i]-32 == 32) {
              flowersArray[flowersArrayIndex] = 0;
              flowersArrayIndex++;
            }

            if (beePositions[0][i]-32 == 640) {
              flowersArray[flowersArrayIndex] = 672;
              flowersArrayIndex++;
            }

            // set bee's y position to 9999999 AFTER creating flowers
            beePositions[1][i] = 9999999;
        }
    }

    // Check if reached left edge
    if (beePositions[0][i] == 0 && !beePositions[2][i]) {
      beePositions[2][i] = 1;
      return;
    } else if (beePositions[0][i] == 0 && beePositions[2][i]) {
      beePositions[1][i] += boxPixelsY;  // Move down to next row
      beePositions[3][i] = 1; // move right set to true
      beePositions[2][i] = 0; // move down set to false
      return;
    }

    // Move left 32 px
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

// Drawing function for the fast bee
void drawFastBee(RenderWindow& window, float beePositions[][10], Sprite fastBeeSprites[], int i, Texture textureFastBeeMovingRight, Texture textureFastBeeMovingLeft) {
  if (beePositions[3][i]) {
      fastBeeSprites[i].setTexture(textureFastBeeMovingRight);
    } else {
      fastBeeSprites[i].setTexture(textureFastBeeMovingLeft);
    }

    fastBeeSprites[i].setPosition(beePositions[0][i], beePositions[1][i]);

    window.draw(fastBeeSprites[i]);
}

// Checks collision between bullet and bee
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[5][20], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score) {

  if (beePositions[1][i] != 448) { // to prevent collision with the player
    if (bullet_x >= beePositions[0][i]-30 && bullet_x <= beePositions[0][i]+32 && bullet_y == beePositions[1][i]) { // if collision occurs
        honeyCombArray[0][honeyCombArrayIndex] = bullet_x;
        honeyCombArray[1][honeyCombArrayIndex] = bullet_y;
        honeyCombArrayIndex++;
        beePositions[1][i] = 99999999; // bee sent down the screen
        bullet_exists = false;
        // play the music
        beeBulletCollisionSound.play();
        sleep(seconds(0.1)); // so that the sound can be heard
        // adding to score
        score+=100;
      } 
  }
}

// Checks collision between bullet and fast bee
void checkBulletFastBeeCollision(int bullet_x, int bullet_y, float beePositions[][10], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score) {
  if (beePositions[1][i] != 448) { // to prevent collision with the player
    if (bullet_x >= beePositions[0][i]-30 && bullet_x <= beePositions[0][i]+32 && bullet_y == beePositions[1][i]) { // if collision occurs
        honeyCombArray[0][honeyCombArrayIndex] = bullet_x;
        honeyCombArray[1][honeyCombArrayIndex] = bullet_y;
        honeyCombArrayIndex++;
        beePositions[1][i] = 99999999; // bee sent down the screen
        bullet_exists = false;
        // play the music
        beeBulletCollisionSound.play();
        sleep(seconds(0.1)); // so that the sound can be heard
        // adding to score
        score+=1000;
      } 
  }
}

void drawHoneyCombs(int honeyCombArray[][gameRows*gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]) {
  for (int i=0; i<honeyCombArrayIndex; i++) {
    honeyCombSpriteArray[i].setPosition(honeyCombArray[0][i], honeyCombArray[1][i]);

    window.draw(honeyCombSpriteArray[i]);
  }
}

void drawRedHoneyCombs(int honeyCombArray[][gameRows*gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]) {
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
    flowerSprites[i].setPosition(flowersArray[i], 480);
    window.draw(flowerSprites[i]);
  }
}

void checkBulletHoneyCombCollision(float bullet_x, float bullet_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic) {
  for (int i=0; i<honeyCombArrayIndex; i++) {
    if (bullet_x == honeyCombArray[0][i] && bullet_y == honeyCombArray[1][i]) {// if collision occurs
      honeyCombArray[1][i] = 99999999;
      bullet_exists = false;
      // play music
      honeyCombOrBeeHiveMusic.play();
      sleep(seconds(0.1)); // so that the sound can be heard
    }
  }
}

void checkBulletRedHoneyCombCollision(float bullet_x, float bullet_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic) {
  for (int i=0; i<honeyCombArrayIndex; i++) {
    if (bullet_x == honeyCombArray[0][i] && bullet_y == honeyCombArray[1][i]) {// if collision occurs
      honeyCombArray[1][i] = 99999999;
      bullet_exists = false;
      // play music
      honeyCombOrBeeHiveMusic.play();
      sleep(seconds(0.1)); // so that the sound can be heard
    }
  }
}

void checkBulletBeeHiveCollision(float bullet_x, float bullet_y, int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic) {
  for (int i=0; i<beeHiveArrayIndex; i++) {
    if (bullet_x == beeHiveArray[0][i] && bullet_y == beeHiveArray[1][i]) {// if collision occurs
      beeHiveArray[1][i] = 99999999;
      bullet_exists = false;
      // play music
      honeyCombOrBeeHiveMusic.play();
      sleep(seconds(0.1)); // so that the sound can be heard
    }
  }
}

void checkBulletBirdCollision(int bullet_x, int bullet_y, Sound hummingBirdSound, int& bulletCollisionCount, Clock& respawnClock, bool& bullet_exists, Sprite& hummingBirdSprite, int& moveToX, int& moveToY) {
  if (abs(bullet_x-hummingBirdSprite.getPosition().x) <=20 && abs(bullet_y-hummingBirdSprite.getPosition().y) <=10) { // collision occurs
    hummingBirdSound.play();
    sleep(seconds(0.1));
    bulletCollisionCount++;
    bullet_exists = false;
    if (bulletCollisionCount % 3 == 0) {
      hummingBirdSound.play();
      sleep(seconds(0.1));
      respawnClock.restart();

      // take humming bird outside the screen
      if (hummingBirdSprite.getPosition().x > resolutionX/2) {
        moveToX = 1000;
        moveToY = hummingBirdSprite.getPosition().y;
      } else {
        moveToX = -50;
        moveToY = hummingBirdSprite.getPosition().y;
      }
      respawnClock.restart();
    }
  }
}

void moveHummingBird(int& moveToX, int& moveToY, Sprite& hummingBirdSprite, Texture TextureBirdRight, Texture TextureBirdLeft, Texture TextureBirdStill) {
  if (moveToX!=-1 && moveToY!=-1 && (abs(hummingBirdSprite.getPosition().x-moveToX)>=2 || abs(hummingBirdSprite.getPosition().y-moveToY)>=2)) { // move humming bird
    float dx = moveToX - hummingBirdSprite.getPosition().x;
    float dy = moveToY - hummingBirdSprite.getPosition().y;
    float distance = sqrt(dx*dx + dy*dy);
    float speed = 4.0f;  // Pixels per frame

    float moveX = (dx / distance) * speed;
    float moveY = (dy / distance) * speed;

    // Move sprite
    hummingBirdSprite.move(moveX, moveY);

  } else if (moveToX!=-1 && moveToY!=-1 && abs(hummingBirdSprite.getPosition().x-moveToX)<2 && abs(hummingBirdSprite.getPosition().y)<2) { // don't move humming bird
    moveToX = -1;
    moveToY = -1;
  }
}

void drawSprayCans(RenderWindow& window, RectangleShape bigRectangles[], float rectangleHeights[], int& numberOfRectangles, int& bulletCount) {
  Font menuFont;
  menuFont.loadFromFile("Fonts/arial.ttf");

  // drawing rectangles
  for (int a=0; a<numberOfRectangles; a++) {
    rectangleHeights[a]=60;
    bigRectangles[a].setSize(Vector2f(30, rectangleHeights[a]));
    bigRectangles[a].setPosition(40+a*40, 514);
    window.draw(bigRectangles[a]);
  }

  // drawing texts
  for (int a=0; a<numberOfRectangles; a++) {
    Text text1;
    text1.setFont(menuFont);
    text1.setCharacterSize(22);
    text1.setPosition(43+(a*40), 527);
    text1.setFillColor(Color::Black);
    text1.setString("56");
    window.draw(text1);
  }
}

void determineBirdMovement(Clock& gameClock, Clock& movementClock, Clock& respawnClock, int& moveToX, int& moveToY, int& movementCount, bool& combFound, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, int& score, Texture TextureBirdRight, Texture TextureBirdLeft, Sprite& hummingBirdSprite, bool& redCombFound, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex) {
  if (gameClock.getElapsedTime().asSeconds() >= 10 && movementClock.getElapsedTime().asSeconds() >= 4.5 && respawnClock.getElapsedTime().asSeconds() >=10) { // humming bird appears after 10 seconds of the game's start and move after 4.5 seconds AND after 10 seconds if shot by bullet 3 times
            // making the comb diappear after 4.5 seconds
            if (combFound) { // if the humming bird was sitting on a honeycomb then make it disappear
              for (int i=0; i<honeyCombArrayIndex; i++) {
                if (honeyCombArray[1][i]<999999) {
                  // adding to the score
                  if (honeyCombArray[1][i]/32<=1) score+=1000;
                  else if (honeyCombArray[1][i]/32<=5) score+=800;
                  else score+=500;
                  // sending honeycomb down the screen
                  honeyCombArray[1][i] = 9999999;
                  break;
                }
              }
            } else if (redCombFound) { // if the humming bird was sitting on a red honeycomb then make it disappear
              for (int i=0; i<redHoneyCombArrayIndex; i++) {
                if (redHoneyCombArray[1][i]<999999) {
                  // adding to the score
                  if (redHoneyCombArray[1][i]/32<=1) score+=2000;
                  else if (redHoneyCombArray[1][i]/32<=5) score+=1800;
                  else score+=1500;
                  // sending honeycomb down the screen
                  redHoneyCombArray[1][i] = 9999999;
                  break;
                }
              }
            }

            combFound = false;
            redCombFound = false;
            movementCount++;
            if (movementCount % 3 == 0) { // go to any honeycomb 

              bool redOrYellowCombDecider = static_cast<int>(rand())%2; // bool that decides which comb should the bird go
              if (redOrYellowCombDecider) { // go to a red honeycomb
                for (int i=0; i<redHoneyCombArrayIndex; i++) {
                  if (redHoneyCombArray[1][i] < 999999) { // if the honeycomb was not shot by a bullet or the humming bird drunk it
                    moveToX = redHoneyCombArray[0][i];
                    moveToY = redHoneyCombArray[1][i];
                    redCombFound = true;
                    break;
                  }
                }

                if (!redCombFound) { // if there are no red honeycombs for the humming bird to drink, find a yellow honeycomb
                  for (int i=0; i<honeyCombArrayIndex; i++) {
                    if (honeyCombArray[1][i] < 999999) { // if the honeycomb was not shot by a bullet or the humming bird drunk it
                      moveToX = honeyCombArray[0][i];
                      moveToY = honeyCombArray[1][i];
                      combFound = true;
                      break;
                    }
                  }
                }
              } else {
                for (int i=0; i<honeyCombArrayIndex; i++) {
                  if (honeyCombArray[1][i] < 999999) { // if the honeycomb was not shot by a bullet or the humming bird drunk it
                    moveToX = honeyCombArray[0][i];
                    moveToY = honeyCombArray[1][i];
                    combFound = true;
                    break;
                  }
                }

                if (!combFound) { // if there are no red honeycombs for the humming bird to drink, find a yellow honeycomb
                  for (int i=0; i<redHoneyCombArrayIndex; i++) {
                    if (redHoneyCombArray[1][i] < 999999) { // if the honeycomb was not shot by a bullet or the humming bird drunk it
                      moveToX = redHoneyCombArray[0][i];
                      moveToY = redHoneyCombArray[1][i];
                      redCombFound = true;
                      break;
                    }
                  }
                }
              }
              if (!combFound and !redCombFound) { // if there are no honeycombs for the humming bird to drink
                moveToX = (rand() % 21)*32;
                moveToY = (rand() % 14)*32;
              }
            } else { // go to a random location
              moveToX = (rand() % 21)*32;
              moveToY = (rand() % 14)*32;
            } 

            movementClock.restart();
          }
}

// returns 0 for lose, 1 for restart, 2 for win, 3 for continue with the current level, 4 for winning the last level
int checkLevelComplete(float beePositions[][20], int flowersArrayIndex, int bulletCount, int selectedLevel, float fastBeePositions[][10], int totalShots) {

  // if all bees are killed AND flowers are not full then WIN . if all bees are killed AND flowers are full then LOSE
  bool allBeesKilled = true;
  int numberOfRegularBees = selectedLevel == 0 ? 20 : selectedLevel == 1 ? 15 : selectedLevel == 2 ? 20 : 0;
  int numberOfFastBees = selectedLevel == 0 ? 0 : selectedLevel == 1 ? 5 : selectedLevel == 2 ? 10 : 0;
  for (int a=0; a<numberOfRegularBees; a++) {
    if (beePositions[1][a] < 9999999) { // when a bee is killed its y position is changed to 99999999
      allBeesKilled = false;
      break;
    }
  }
  for (int a=0; a<numberOfFastBees; a++) {
    if (fastBeePositions[1][a] < 9999999) { // when a bee is killed its y position is changed to 99999999
      allBeesKilled = false;
      break;
    }
  }

  if (allBeesKilled && flowersArrayIndex < gameColumns) {
    if (selectedLevel == 3) {
      return 4;
    }
    return 2; 
  } else if (allBeesKilled && flowersArrayIndex == gameColumns) {
    if (bulletCount<totalShots-56) {
      return 1;
    }
    return 0;
  }   

  // if flowers are full AND bullets < 112 then RESTART
  if (flowersArrayIndex == gameColumns && bulletCount < totalShots-56) {
    return 1; 
  } else if (flowersArrayIndex == gameColumns) {
    return 0;
  }

  // if bulletCount == totalShots AND bees still there then lose
  if (bulletCount == totalShots && !allBeesKilled) {
    return 0;
  }

  return 3; 
}

void resetForLevel1(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[5][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots) {
  bulletClock.restart();
  gameClock.restart();
  movementClock.restart();
  bulletCollisionClock.restart();
  respawnClock.restart();
  movementCount = 0;
  bulletCollisionCount = 0;
  bulletCount = (bulletCount/56)*56; // to refill the current spray can
  bullet_exists = false;

  for (int i = 0; i < 20; i++) {
    beePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    beePositions[1][i] = 0; // bee_y
    beePositions[2][i] = 0; // moveDown flag
    beePositions[3][i] = static_cast<int>(beePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    beePositions[4][i] = 0; // isNextHoneyComb flag
  }

  player_x = (gameColumns / 2) * boxPixelsX;
	player_y = (gameRows - 4) * boxPixelsY;

  bullet_x = player_x;
  bullet_y = player_y;

  beeHiveArrayIndex = 0;
  flowersArrayIndex = 0;

  for (int j=0; j<gameRows*gameColumns; j++) {
    honeyCombArray[1][j] = -99;
    beeHiveArray[1][j] = -99;
    redHoneyCombArray[1][j] = -99;
  }

  for (int j=0; j<gameColumns+2; j++) {
    flowersArray[j] = 0;
  }  

  for (int i=0; i<3; i++) { // making 3 random honeycombs
    honeyCombArray[0][i] = static_cast<int>(rand()%21)*32;
    honeyCombArray[1][i] = static_cast<int>(rand()%13)*32;
  }

  honeyCombArrayIndex = 3;


  hummingBirdSprite.setPosition(-100, -100);

  if (!bgMusic.openFromFile("Music/aMusic3.ogg")) {
	    cout << "Error: Could not load music file!" << endl;
	}
	bgMusic.setVolume(10.0f);
	bgMusic.setLoop(true);
	bgMusic.play();

  redHoneyCombArrayIndex = 0;
  for (int i = 0; i < 10; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
  }
}

void resetForLevel2(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[5][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots) {
  bulletClock.restart();
  gameClock.restart();
  movementClock.restart();
  bulletCollisionClock.restart();
  respawnClock.restart();
  movementCount = 0;
  bulletCollisionCount = 0;
  bulletCount = (bulletCount/56)*56; // to refill the current spray can
  redHoneyCombArrayIndex = 0;
  bullet_exists = false;

  for (int i = 0; i < 20; i++) {
    beePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    beePositions[1][i] = 0; // bee_y
    beePositions[2][i] = 0; // moveDown flag
    beePositions[3][i] = static_cast<int>(beePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    beePositions[4][i] = 0; // isNextHoneyComb flag
  }

  for (int i = 0; i < 10; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
  }

  player_x = (gameColumns / 2) * boxPixelsX;
	player_y = (gameRows - 4) * boxPixelsY;

  bullet_x = player_x;
  bullet_y = player_y;

  beeHiveArrayIndex = 0;
  flowersArrayIndex = 0;

  for (int j=0; j<gameRows*gameColumns; j++) {
    honeyCombArray[1][j] = -99;
    beeHiveArray[1][j] = -99;
    redHoneyCombArray[1][j] = -99;
  }

  for (int j=0; j<gameColumns+2; j++) {
    flowersArray[j] = 0;
  }  

  for (int i=0; i<9; i++) { // making 9 random honeycombs
    honeyCombArray[0][i] = static_cast<int>(rand()%21)*32;
    honeyCombArray[1][i] = static_cast<int>(rand()%13)*32;
  }

  honeyCombArrayIndex = 9;


  hummingBirdSprite.setPosition(-100, -100);

  if (!bgMusic.openFromFile("Music/Music3.ogg")) {
	    cout << "Error: Could not load music file!" << endl;
	}
	bgMusic.setVolume(10.0f);
	bgMusic.setLoop(true);
	bgMusic.play();

}

void resetForLevel3(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[5][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][10], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots, int selectedLevel) {
  bulletClock.restart();
  gameClock.restart();
  movementClock.restart();
  bulletCollisionClock.restart();
  respawnClock.restart();
  movementCount = 0;
  bulletCollisionCount = 0;
  bulletCount = (bulletCount/56)*56; // to refill the current spray can
  redHoneyCombArrayIndex = 0;
  bullet_exists = false;

  for (int i = 0; i < 20; i++) {
    beePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    beePositions[1][i] = 0; // bee_y
    beePositions[2][i] = 0; // moveDown flag
    beePositions[3][i] = static_cast<int>(beePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    beePositions[4][i] = 0; // isNextHoneyComb flag
  }

  for (int i = 0; i < 10; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
  }

  player_x = (gameColumns / 2) * boxPixelsX;
	player_y = (gameRows - 4) * boxPixelsY;

  bullet_x = player_x;
  bullet_y = player_y;

  beeHiveArrayIndex = 0;
  flowersArrayIndex = 0;

  for (int j=0; j<gameRows*gameColumns; j++) {
    honeyCombArray[1][j] = -99;
    beeHiveArray[1][j] = -99;
    redHoneyCombArray[1][j] = -99;
  }

  for (int j=0; j<gameColumns+2; j++) {
    flowersArray[j] = 0;
  }  

  for (int i=0; i<15; i++) { // making 15 random honeycombs
    honeyCombArray[0][i] = static_cast<int>(rand()%21)*32;
    honeyCombArray[1][i] = static_cast<int>(rand()%13)*32;
  }

  honeyCombArrayIndex = 15;


  hummingBirdSprite.setPosition(-100, -100);


  if (selectedLevel == 2) { // if level is level 3
    if (!bgMusic.openFromFile("Music/magical_journey.ogg")) {
        cout << "Error: Could not load music file!" << endl;
    }
  } else { // if level is level 4
    if (!bgMusic.openFromFile("Music/risk.ogg")) {
        cout << "Error: Could not load music file!" << endl;
    }
  }
	bgMusic.setVolume(10.0f);
	bgMusic.setLoop(true);
	bgMusic.play();

}

void countHivePoints(int beeHiveArray[][gameRows*gameColumns], int beeHiveArrayIndex, int& score) {
  for (int i = 0; i < beeHiveArrayIndex; i++) {
    if (beeHiveArray[1][i]<9999) { // if the beeHive was not shot
      if (beeHiveArray[1][i]/32 <= 1) { // if the beeHive was on first 2 rows
        score+=2000;
      } else if (beeHiveArray[1][i]/32 <= 5) {
        score+=1600;
      } else {
        score+=1000;
      }
    }
  }
}

void determineNumberOfRectangles(int& numberOfRectangles, int bulletCount, int score, int& totalShots, bool& scoreGreaterThan20k, bool& scoreGreaterThan40k, bool& scoreGreaterThan80k, bool& scoreGreaterThan160k, bool& scoreGreaterThan240k, bool& scoreGreaterThan320k) {
  // increasing the number of spray cans based on the score
  if (score>=320000 && !scoreGreaterThan320k) {
    numberOfRectangles += 1;
    totalShots+=56;
    scoreGreaterThan320k = true;
  } else if (score>=240000 && !scoreGreaterThan240k) {
    numberOfRectangles += 1;
    totalShots+=56;
    scoreGreaterThan240k = true;
  } else if (score>=160000 && !scoreGreaterThan160k) {
    numberOfRectangles += 1;
    totalShots+=56;
    scoreGreaterThan160k = true;
  } else if (score>=80000 && !scoreGreaterThan80k) {
    numberOfRectangles += 1;
    totalShots+=56;
    scoreGreaterThan80k = true;
  } else if (score>=40000 && !scoreGreaterThan40k) {
    numberOfRectangles += 1;
    totalShots+=56;
    scoreGreaterThan40k = true;
  } else if (score>=20000 && !scoreGreaterThan20k) {
    numberOfRectangles += 1;
    totalShots+=56;
    scoreGreaterThan20k = true;
  }

  // determining the number of spray cans
  if ((totalShots-bulletCount)%56 == 0) {
    numberOfRectangles = (totalShots-bulletCount)/56 - 1;
  } else if ((totalShots-bulletCount)%56 != 0) {
    numberOfRectangles = (totalShots-bulletCount)/56;
  }

  cout<< "numberOfRectangles: " << numberOfRectangles << endl;
  cout<< "bulletCount"<< bulletCount<< endl;
  cout<< "totalShots"<< totalShots<< endl;
  cout<< endl;
}