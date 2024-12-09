#include <iostream>
#include <cmath> // for taking square root and abs()
#include <cstring> // for converting int datatype to string and also using string datatype instead of char and also for strcpy
#include <fstream>
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
void runGame(int& currentState, int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[][20], float& player_x, float& player_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound, Sprite beeHiveSprites[40], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, Texture textureBeeMovingLeft, Texture textureBeeMovingRight, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], Sound, Texture TextureBirdRight, Texture TextureBirdLeft, Texture TextureBirdStill, Sprite& hummingBirdSprite, Sound hummingBirdSound, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, RectangleShape bigRectangles[], float rectangleHeights[], int& numberOfRectangles, int& score, bool&, Music&, Clock& fastBeeClock, Texture TextureFastBeeMovingLeft, Texture TextureFastBeeMovingRight, Sprite fastBeeSprites[], float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, Texture redHoneyCombTexture, Sprite redHoneyCombSpriteArray[], int& totalShots, bool& scoreGreaterThan20k, bool& scoreGreaterThan40k, bool& scoreGreaterThan80k, bool& scoreGreaterThan160k, bool& scoreGreaterThan240k, bool& scoreGreaterThan320k, int powerUpsArray[][400], Sprite powerUpsSprites[400], int& powerUpsArrayIndex, Texture HeightDecTexture, Texture HeightIncTexture, Texture speedUpTexture, Texture speedDecTexture, int powersOfPlayer[], Texture sprayCanHalfTexture, Texture sprayCanDoubleTexture, Texture playerTexture, RectangleShape progressBars[4], RectangleShape& filledBody);
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, int totalShots, int bulletCount, RectangleShape& filledBody);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock, Sound fireSound);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite beeSprite);
void moveBee(float beePositions[][20], Clock&, int, int[][gameRows*gameColumns], int[][gameRows*gameColumns], int& beeHiveArrayIndex, int& honeyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], int redHoneyCombArray[][gameRows*gameColumns]);
void drawBee(RenderWindow&, float beePositions[][20], Sprite beeSprites[20], int, Texture, Texture);
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[][20], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score);
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
int checkLevelComplete(float beePositions[][20], int flowersArrayIndex, int bulletCount, int selectedLevel, float fastBeePositions[][15], int totalShots);
int drawNameInput(RenderWindow& window, char* name, int maxLength, int& charCount, int score);
void resetForLevel1(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots);
void countHivePoints(int beeHiveArray[][gameRows*gameColumns], int beeHiveArrayIndex, int& score);
void moveFastBee(float beePositions[][15], Clock& fastBeeClock, int i, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]);
void drawFastBee(RenderWindow& window, float beePositions[][15], Sprite fastBeeSprites[], int i, Texture textureFastBeeMovingRight, Texture textureFastBeeMovingLeft);
void checkBulletFastBeeCollision(int bullet_x, int bullet_y, float fastBeePositions[][15], int i, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score);
void drawRedHoneyCombs(int honeyCombArray[][gameRows*gameColumns], int honeyCombArrayIndex, RenderWindow& window, Sprite honeyCombSpriteArray[]);
void checkBulletRedHoneyCombCollision(float bullet_x, float bullet_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic);
void resetForLevel2(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots);
void resetForLevel3(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots, int selectedLevel);
void determineNumberOfRectangles(int& numberOfRectangles, int bulletCount, int score, int& totalShots, bool& scoreGreaterThan20k, bool& scoreGreaterThan40k, bool& scoreGreaterThan80k, bool& scoreGreaterThan160k, bool& scoreGreaterThan240k, bool& scoreGreaterThan320k);
void checkBulletRedHoneyCombCollisionForLevel4(float bullet_x, float bullet_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic, int powerUpsArray[][400], int& powerUpsArrayIndex);
void movePowerUp(int powerUpsArray[][400], int powerUpsArrayIndex, int i);
void drawPowerUp(int powerUpsArray[][400], int powerUpsArrayIndex, int i, RenderWindow& window, Sprite powerUpsSprites[], Texture HeightDecTexture, Texture HeightIncTexture, Texture speedUpTexture, Texture speedDecTexture);
void determineBirdMovementForLevel4(Clock& gameClock, Clock& movementClock, Clock& respawnClock, int& moveToX, int& moveToY, int& movementCount, bool& combFound, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, int& score, Texture TextureBirdRight, Texture TextureBirdLeft, Sprite& hummingBirdSprite, bool& redCombFound, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int powerUpsArray[][400], int& powerUpsArrayIndex);
void updatePowerUpsArray(int powerUpsArray[][400], int& powerUpsArrayIndex, int player_x, int player_y, int powersOfPlayer[], Clock powersOfPlayerClocks[]);
void drawPlayerForLevel4(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, Texture sprayCanHalfTexture, Texture sprayCanDoubleTexture, Texture playerTexture, int powersOfPlayer[], RectangleShape& filledBody, int bulletCount, int totalShots);
void handlePowerUpsTime(int powerUpsArray[][400], int& powerUpsArrayIndex, int powersOfPlayer[], Clock powersOfPlayerClocks[], float& player_x, RectangleShape progressBars[4], RenderWindow& window);
void drawHighScores(RenderWindow& window, char name[], int score, int& currentState, int charCount);


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

  float beePositions[6][20];
  for (int i = 0; i < 20; i++) {
    beePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    beePositions[1][i] = 0; // bee_y
    beePositions[2][i] = 0; // moveDown flag
    beePositions[3][i] = static_cast<int>(beePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    beePositions[4][i] = 0; // isNextHoneyComb flag
    beePositions[5][i] = 0; // hasMadeFlower flag
  }

  // The fast bee sprite
  Clock fastBeeClock;
  Texture textureFastBeeMovingLeft;
  textureFastBeeMovingLeft.loadFromFile("./Textures/Fast_bee.png");
  textureFastBeeMovingLeft.setSmooth(true);

  Texture textureFastBeeMovingRight;
  textureFastBeeMovingRight.loadFromFile("./Textures/Fast_bee_reversed.png");
  textureFastBeeMovingRight.setSmooth(true);
  Sprite fastBeeSprites[15] = {Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite(), Sprite()};

  float fastBeePositions[6][15];
  for (int i = 0; i < 15; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
    fastBeePositions[5][i] = 0; // hasMadeFlower flag
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
  RectangleShape filledBody;
  filledBody.setFillColor(Color::White);

  // Score counter
  int score = 0;

  // powerups
  int powerUpsArray[4][400]; // first row is for if the powerup is active, second row is for the type of the powerup, third is for the x position and fourth is for the y position
  int powersOfPlayer[4] = {0};
  for (int a=0; a<4; a++) {
    for (int b=0; b<400; b++) {
      powerUpsArray[a][b] = 0;
    }
  }
  Sprite powerUpsSprites[400];
  int powerUpsArrayIndex = 0;
  Texture HeightDecTexture;
  HeightDecTexture.loadFromFile("./Textures/Height_Dec.png");
  Texture HeightIncTexture;
  HeightIncTexture.loadFromFile("./Textures/Height_Inc.png");
  Texture speedUpTexture;
  speedUpTexture.loadFromFile("./Textures/Speed_Inc.png");
  Texture speedDecTexture;
  speedDecTexture.loadFromFile("./Textures/Speed_Dec.png");

  Texture sprayCanHalfTexture;
  sprayCanHalfTexture.loadFromFile("./Textures/spray_half.png");
  Texture sprayCanDoubleTexture;
  sprayCanDoubleTexture.loadFromFile("./Textures/spray_double.png");

  // progress bar for powerUps

  RectangleShape progressBars[4];
  
	// The ground on which player moves

	RectangleShape groundRectangle(Vector2f(980, 64));
	groundRectangle.setPosition(0, (gameRows - 2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Green);

	// Implementing menu system
  const int HIGH_SCORES = -2;
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
          currentState = drawNameInput(window, name, 30, charCount, score);
          break;
      case -2: // HIGH_SCORES
          window.clear();
          drawHighScores(window, name, score, currentState, charCount);
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
          runGame(currentState,selectedLevel, playerSprite, bulletSprite, bulletClock, gameClock, bullet_x, bullet_y, bullet_exists, beeSprites, groundRectangle, window, boxPixelsX, beePositions, player_x, player_y, honeyCombArray, honeyCombArrayIndex, honeyCombSpriteArray, beeBulletCollisionSound, obstacleBulletCollisionSound, fireSound, beeHiveSprites, beeHiveArray, beeHiveArrayIndex, textureBeeMovingLeft, textureBeeMovingRight, flowersArray, flowersArrayIndex, flowerSprites, honeyCombOrBeeHiveMusic, TextureBirdRight, TextureBirdLeft, TextureBirdStill, hummingBirdSprite, hummingBirdSound, movementClock, bulletCollisionClock, respawnClock, movementCount, bulletCollisionCount, bulletCount, bigRectangles, rectangleHeights, numberOfRectangles, score, firstTime, bgMusic, fastBeeClock, textureFastBeeMovingLeft, textureFastBeeMovingRight, fastBeeSprites, fastBeePositions, redHoneyCombArray, redHoneyCombArrayIndex, redHoneyCombTexture, redHoneyCombSpriteArray, totalShots, scoreGreaterThan20k, scoreGreaterThan40k, scoreGreaterThan80k, scoreGreaterThan160k, scoreGreaterThan240k, scoreGreaterThan320k, powerUpsArray, powerUpsSprites, powerUpsArrayIndex, HeightDecTexture, HeightIncTexture, speedUpTexture, speedDecTexture, powersOfPlayer, sprayCanHalfTexture, sprayCanDoubleTexture, playerTexture, progressBars, filledBody);
          break;


      case EXIT_STATE:
          window.close();
          break;
    }

		window.display();

	}
}
void runGame(int& currentState, int& selectedLevel, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, Sprite beeSprites[20], RectangleShape& groundRectangle, RenderWindow& window, int boxPixelsX, float beePositions[][20], float& player_x, float& player_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, Sprite honeyCombSpriteArray[], Sound beeBulletCollisionSound, Sound obstacleBulletCollisionSound, Sound fireSound, Sprite beeHiveSprites[], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, Texture textureBeeMovingLeft, Texture textureBeeMovingRight, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], Sound honeyCombOrBeeHiveMusic, Texture TextureBirdRight, Texture TextureBirdLeft, Texture TextureBirdStill, Sprite& hummingBirdSprite, Sound hummingBirdSound, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, RectangleShape bigRectangles[], float rectangleHeights[], int& numberOfRectangles, int& score, bool& firstTime, Music& bgMusic, Clock& fastBeeClock, Texture TextureFastBeeMovingLeft, Texture TextureFastBeeMovingRight, Sprite fastBeeSprites[], float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, Texture redHoneyCombTexture, Sprite redHoneyCombSpriteArray[], int& totalShots, bool& scoreGreaterThan20k, bool& scoreGreaterThan40k, bool& scoreGreaterThan80k, bool& scoreGreaterThan160k, bool& scoreGreaterThan240k, bool& scoreGreaterThan320k, int powerUpsArray[][400], Sprite powerUpsSprites[400], int& powerUpsArrayIndex, Texture HeightDecTexture, Texture HeightIncTexture, Texture speedUpTexture, Texture speedDecTexture, int powersOfPlayer[], Texture sprayCanHalfTexture, Texture sprayCanDoubleTexture, Texture playerTexture, RectangleShape progressBars[4], RectangleShape& filledBody) {
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
          drawPlayer(window, player_x, player_y, playerSprite, totalShots, bulletCount, filledBody);
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
            firstTime = true;
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
          drawPlayer(window, player_x, player_y, playerSprite, totalShots, bulletCount, filledBody);
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
            firstTime = true;
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
          drawPlayer(window, player_x, player_y, playerSprite, totalShots, bulletCount, filledBody);
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
            firstTime = true;
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
          determineBirdMovementForLevel4(gameClock, movementClock, respawnClock, moveToX, moveToY, movementCount, combFound, honeyCombArray, honeyCombArrayIndex, score, TextureBirdRight, TextureBirdLeft, hummingBirdSprite, redCombFound, redHoneyCombArray, redHoneyCombArrayIndex, powerUpsArray, powerUpsArrayIndex);

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
                if (powersOfPlayer[0]>=1) { // if speed up power up is on
                  if (static_cast<int>(player_x)!=640) {
                    player_x+=boxPixelsX*2;
                    bullet_x+= bullet_exists ? 0 : boxPixelsX*2;
                  }
                } else if (powersOfPlayer[1]>=1) { // if speed down power up is on
                  player_x+=boxPixelsX/2;
                  bullet_x+= bullet_exists ? 0 : boxPixelsX/2;                  
                } else { // both powers are off
                  player_x+=boxPixelsX;
                  bullet_x+= bullet_exists ? 0 : boxPixelsX;
                }
              }
            } else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Left) {
              bool isObstacle = false; // isObstacle set to true if there's a flower to the left
              for (int i = 0; i < flowersArrayIndex; i++) {
                if (player_x-32 == flowersArray[i]) {
                  isObstacle = true;
                }
              }
              if (static_cast<int>(player_x)!=0 && !isObstacle) {
                if (powersOfPlayer[0]>=1) { // if speed up power up is on
                  if (static_cast<int>(player_x)!=32) {
                    player_x-=boxPixelsX*2;
                    bullet_x-= bullet_exists ? 0 : boxPixelsX*2;
                  }
                } else if (powersOfPlayer[1]>=1) { // if speed down power up is on
                  player_x-=boxPixelsX/2;
                  bullet_x-= bullet_exists ? 0 : boxPixelsX/2;
                } else { // both powers are off
                  player_x-=boxPixelsX;
                  bullet_x-= bullet_exists ? 0 : boxPixelsX;
                }
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

          static Clock fastBeeClocks[15] = {Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock(), Clock()};
          for (int i = 0; i < 15; i++) {
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
            checkBulletRedHoneyCombCollisionForLevel4(bullet_x, bullet_y, redHoneyCombArray, redHoneyCombArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic, powerUpsArray, powerUpsArrayIndex);
            checkBulletBeeHiveCollision(bullet_x, bullet_y, beeHiveArray, beeHiveArrayIndex, bullet_exists, honeyCombOrBeeHiveMusic);
            checkBulletBirdCollision(bullet_x, bullet_y, hummingBirdSound, bulletCollisionCount, respawnClock, bullet_exists, hummingBirdSprite, moveToX, moveToY);
          }
          else
          {
            bullet_x = player_x;
            bullet_y = 448;
          }

          // moving powerups
          for (int i=0; i<powerUpsArrayIndex; i++) {
            movePowerUp(powerUpsArray, powerUpsArrayIndex, i);
            drawPowerUp(powerUpsArray, powerUpsArrayIndex, i, window, powerUpsSprites, HeightDecTexture, HeightIncTexture, speedUpTexture, speedDecTexture);
          }

          // checking if the player has picked a powerup
          static Clock powersOfPlayerClocks[4]; // clock for powerups that the player has picked
          updatePowerUpsArray(powerUpsArray, powerUpsArrayIndex, player_x, player_y, powersOfPlayer, powersOfPlayerClocks);
          handlePowerUpsTime(powerUpsArray, powerUpsArrayIndex, powersOfPlayer, powersOfPlayerClocks, player_x, progressBars, window);

          // drawing different stuff
          window.draw(groundRectangle);
          drawScore(window, score);
          drawSprayCans(window, bigRectangles, rectangleHeights, numberOfRectangles, bulletCount);
          drawFlowers(window, flowersArray, flowersArrayIndex, flowerSprites);
          drawBeeHives(beeHiveArray, beeHiveArrayIndex, window, beeHiveSprites);
          drawHoneyCombs(honeyCombArray, honeyCombArrayIndex, window, honeyCombSpriteArray);
          drawRedHoneyCombs(redHoneyCombArray, redHoneyCombArrayIndex, window, redHoneyCombSpriteArray);
          drawPlayerForLevel4(window, player_x, player_y, playerSprite, sprayCanHalfTexture, sprayCanDoubleTexture, playerTexture, powersOfPlayer, filledBody, bulletCount, totalShots);
          window.draw(hummingBirdSprite);

          // 0 for lose, 1 for restart, 2 for win, 3 for continue with the current level, 4 for winning the last level
          int level4Complete = checkLevelComplete(beePositions, flowersArrayIndex, bulletCount, selectedLevel, fastBeePositions, totalShots); // returns 0 for lose, 1 for restart, 2 for win, 3 for continue with the current level, 4 for winning the last level
          // counting bee hive score at the end of the level
          if (level4Complete != 3) { // level has finished
            countHivePoints(beeHiveArray, beeHiveArrayIndex, score);
            
          }

          if (level4Complete == 4) {
            currentState = -1;
            firstTime = true;
          } else if (level4Complete == 0) {
            currentState = -1;
            firstTime = true;
          } else if (level4Complete == 1) {
            // subtract one spray can and restart the game
            totalShots-=56;
            numberOfRectangles-=1;
            firstTime = true;
          } 
    }
    
    
}

// function that displays the name input page
int drawNameInput(RenderWindow& window, char* name, int maxLength, int& charCount, int score) {
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
            ofstream outFile("highscores.txt", ios::out | ios::app);
            if (!outFile) {
              cout<< "Error opening file for writing!" << endl;
            }
            outFile << name << " " << score << endl;
            outFile.close();
            return -2; // SHOULD RETURN HIGH SCORE PAGE
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
    string menuOptions[] = {"Start Game", "Choose Level", "High Scores", "Exit"};
    Text optionTexts[4];

    for (int i = 0; i < 4; i++) {
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
                    selectedOption = (selectedOption + 3) % 4;
                    break;
                case Keyboard::Down:
                    selectedOption = (selectedOption + 1) % 4;
                    break;
                case Keyboard::Enter:
                    switch (selectedOption) {
                        case 0: // Start Game
                            currentState = 2; // GAME_STATE
                            return 2;
                        case 1: // Choose Level
                            currentState = 1; // LEVEL_SELECT_STATE
                            return 1;
                        case 2: // High Scores
                            currentState = -2; // HIGH_SCORES_STATE
                            return -2;
                        case 3: // Exit
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
    string levelOptions[] = {"Level 1", "Level 2", "Level 3", "Level 4"};
    Text levelTexts[4];

    for (int i = 0; i < 4; i++) {
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
              selectedLevel = (selectedLevel - 1 + 4) % 4;
              break;
            case Keyboard::Down:
              selectedLevel = (selectedLevel + 1) % 4;
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
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, int totalShots, int bulletCount, RectangleShape& filledBody) {
  filledBody.setPosition(player_x, player_y+30);
  filledBody.setSize(Vector2f(32, ((totalShots-bulletCount-1)%56)/2));
	playerSprite.setPosition(player_x, player_y);
	window.draw(playerSprite);
  window.draw(filledBody);
}

void drawPlayerForLevel4(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, Texture sprayCanHalfTexture, Texture sprayCanDoubleTexture, Texture playerTexture, int powersOfPlayer[], RectangleShape& filledBody, int bulletCount, int totalShots) {
  // setTexture was not working so I used setScale
  if (powersOfPlayer[2] >= 1) {
    // playerSprite.setTexture(sprayCanDoubleTexture);
    playerSprite.setScale(1.5, 1.5);
    player_y = (gameRows - 5) * boxPixelsY;
    filledBody.setPosition(player_x, player_y+30);
    filledBody.setSize(Vector2f(32, ((totalShots-bulletCount-1)%56)/2));
    filledBody.setScale(1.5, 1.5);
    window.draw(filledBody);
  } else if (powersOfPlayer[3] >= 1) {
    // playerSprite.setTexture(sprayCanDoubleTexture);
    playerSprite.setScale(.75, .75);
    filledBody.setPosition(player_x, player_y+30);
    filledBody.setSize(Vector2f(32, ((totalShots-bulletCount-1)%56)/2));
    filledBody.setScale(.75, .75);
    window.draw(filledBody);
    player_y = (gameRows - 3) * boxPixelsY - 20;
  } else {
    filledBody.setPosition(player_x, player_y+30);
    filledBody.setSize(Vector2f(32, ((totalShots-bulletCount-1)%56)/2));
    filledBody.setScale(1, 1);
    playerSprite.setPosition(player_x, player_y);
    window.draw(playerSprite);
    window.draw(filledBody);
    playerSprite.setScale(1, 1);
    player_y = (gameRows - 4) * boxPixelsY;
  }
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
void moveBee(float beePositions[][20], Clock& beeClock, int i, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int& beeHiveArrayIndex, int& honeyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[], int redHoneyCombArray[][gameRows*gameColumns]) {
  if (beeClock.getElapsedTime().asSeconds() < 0.08)
    return;

  beeClock.restart();

  if (beePositions[3][i]) { // if bee moving right
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 448) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]+32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]+32 <= 672 && beePositions[0][i]+32 >= 0 && !beePositions[5][i]) {
            beePositions[5][i] = 1;
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
            
            beePositions[3][i] = 0;
        }
      // set bee's y position to 99999999 AFTER creating flowers
      if ((beePositions[0][i] == 0 || beePositions[0][i] == 672)&&beePositions[5][i]) { // if reached edge of screen then make them disappear
        beePositions[1][i] = 99999999;
      }
    }

    // if reached flowers then also make them disappear
    if (beePositions[1][i] == 480) {
      beePositions[1][i] = 99999999;
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
    if (beePositions[1][i] == 448) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]-32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]-32 <= 672 && beePositions[0][i]-32 >= 0 && !beePositions[5][i]) {
            beePositions[5][i] = 1;
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
            
            beePositions[3][i] = 1; // make it go right after making flowers
        }
      // set bee's y position to 9999999 AFTER creating flowers
      if ((beePositions[0][i] == 0 || beePositions[0][i] == 672)&&beePositions[5][i]) { // if reached edge of screen then make them disappear
        beePositions[1][i] = 9999999;
      }
    }

    // if reached flowers then also make them disappear
    if (beePositions[1][i] == 480) {
      beePositions[1][i] = 99999999;
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

void moveFastBee(float beePositions[][15], Clock& fastBeeClock, int i, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, RenderWindow& window, int flowersArray[], int& flowersArrayIndex, Sprite flowerSprites[]) {
  if (fastBeeClock.getElapsedTime().asSeconds() < 0.02)
    return;

  fastBeeClock.restart();

  if (beePositions[3][i]) { // if bee moving right
    // Check if bee is on last row, then create flowers
    if (beePositions[1][i] == 448) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]+32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]+32 <= 672 && beePositions[0][i]+32 >= 0 && !beePositions[5][i]) {
            beePositions[5][i] = 1;
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

            beePositions[3][i] = 0; // move right set to false
        }

        // set bee's y position to 99999999 AFTER creating flowers
        if ((beePositions[0][i] == 0 || beePositions[0][i] == 672)&&beePositions[5][i]) {
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
    if (beePositions[1][i] == 448) {
        bool flowerAlreadyDrawn32 = false;

        for (int a = 0; a < gameColumns+2; a++) {
            if (flowersArray[a] == beePositions[0][i]-32) {
                flowerAlreadyDrawn32 = true;
            }
        }

        // If 32px is unflowered, create it
        if (!flowerAlreadyDrawn32 && beePositions[0][i]-32 <= 672 && beePositions[0][i]-32 >= 0 && !beePositions[5][i]) {
            beePositions[5][i] = 1;
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

            beePositions[3][i] = 1; // move right set to true
        }

        // set bee's y position to 9999999 AFTER creating flowers
        if ((beePositions[0][i] == 0 || beePositions[0][i] == 672)&&beePositions[5][i]) {
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
void drawBee(RenderWindow& window, float beePositions[][20], Sprite beeSprites[20], int i, Texture textureBeeMovingRight, Texture textureBeeMovingLeft) { 
    if (beePositions[3][i]) {
      beeSprites[i].setTexture(textureBeeMovingRight);
      
    } else {
      beeSprites[i].setTexture(textureBeeMovingLeft);
    }

    beeSprites[i].setPosition(beePositions[0][i], beePositions[1][i]);

    window.draw(beeSprites[i]);
}

// Drawing function for the fast bee
void drawFastBee(RenderWindow& window, float beePositions[][15], Sprite fastBeeSprites[], int i, Texture textureFastBeeMovingRight, Texture textureFastBeeMovingLeft) {
  if (beePositions[3][i]) {
      fastBeeSprites[i].setTexture(textureFastBeeMovingRight);
    } else {
      fastBeeSprites[i].setTexture(textureFastBeeMovingLeft);
    }

    fastBeeSprites[i].setPosition(beePositions[0][i], beePositions[1][i]);

    window.draw(fastBeeSprites[i]);
}

// Checks collision between bullet and bee
void checkBulletBeeCollision(float bullet_x, float bullet_y, float beePositions[][20], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score) {

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
void checkBulletFastBeeCollision(int bullet_x, int bullet_y, float beePositions[][15], int i, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound beeBulletCollisionSound, int& score) {
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

void checkBulletRedHoneyCombCollisionForLevel4(float bullet_x, float bullet_y, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, bool& bullet_exists, Sound honeyCombOrBeeHiveMusic, int powerUpsArray[][400], int& powerUpsArrayIndex) {
  for (int i=0; i<honeyCombArrayIndex; i++) {
    if (bullet_x == honeyCombArray[0][i] && bullet_y == honeyCombArray[1][i]) {// if collision occurs
      // creating a powerup
      powerUpsArray[0][powerUpsArrayIndex] = 1;
      powerUpsArray[1][powerUpsArrayIndex] = static_cast<int>(rand())%4+1;
      powerUpsArray[2][powerUpsArrayIndex] = bullet_x;
      powerUpsArray[3][powerUpsArrayIndex] = bullet_y;
      powerUpsArrayIndex++;

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
    if (bulletCollisionCount % 3 == 0) { // if 3 collisions have occured
      hummingBirdSound.play();
      sleep(seconds(0.1));
      respawnClock.restart();
      hummingBirdSprite.setColor(Color::Green);
      
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

void determineBirdMovementForLevel4(Clock& gameClock, Clock& movementClock, Clock& respawnClock, int& moveToX, int& moveToY, int& movementCount, bool& combFound, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, int& score, Texture TextureBirdRight, Texture TextureBirdLeft, Sprite& hummingBirdSprite, bool& redCombFound, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int powerUpsArray[][400], int& powerUpsArrayIndex) {
  if (gameClock.getElapsedTime().asSeconds() >= 10 && movementClock.getElapsedTime().asSeconds() >= 4.5 && respawnClock.getElapsedTime().asSeconds() >=10) { // humming bird appears after 10 seconds of the game's start and move after 4.5 seconds AND after 10 seconds if shot by bullet 3 times
            hummingBirdSprite.setColor(Color::White);
            // making the comb diappear after 4.5 seconds
            if (combFound) { // if the humming bird was sitting on a honeycomb then make it disappear
              for (int i=0; i<honeyCombArrayIndex; i++) {
                if (honeyCombArray[1][i]<999999) {
                  // adding to the score
                  if (honeyCombArray[1][i]/32<=1) score+=1000;
                  else if (honeyCombArray[1][i]/32<=5) score+=800;
                  else score+=500;
                  // creating a powerup
                  powerUpsArray[0][powerUpsArrayIndex] = 1;
                  powerUpsArray[1][powerUpsArrayIndex] = static_cast<int>(rand())%4+1;
                  powerUpsArray[2][powerUpsArrayIndex] = honeyCombArray[0][i];
                  powerUpsArray[3][powerUpsArrayIndex] = honeyCombArray[1][i];
                  powerUpsArrayIndex++;
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
                  // creating a powerup
                  powerUpsArray[0][powerUpsArrayIndex] = 1;
                  powerUpsArray[1][powerUpsArrayIndex] = static_cast<int>(rand())%4+1;
                  powerUpsArray[2][powerUpsArrayIndex] = redHoneyCombArray[0][i];
                  powerUpsArray[3][powerUpsArrayIndex] = redHoneyCombArray[1][i];
                  powerUpsArrayIndex++;
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

void determineBirdMovement(Clock& gameClock, Clock& movementClock, Clock& respawnClock, int& moveToX, int& moveToY, int& movementCount, bool& combFound, int honeyCombArray[][gameRows*gameColumns], int& honeyCombArrayIndex, int& score, Texture TextureBirdRight, Texture TextureBirdLeft, Sprite& hummingBirdSprite, bool& redCombFound, int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex) {
  if (gameClock.getElapsedTime().asSeconds() >= 10 && movementClock.getElapsedTime().asSeconds() >= 4.5 && respawnClock.getElapsedTime().asSeconds() >=10) { // humming bird appears after 10 seconds of the game's start and move after 4.5 seconds AND after 10 seconds if shot by bullet 3 times
            hummingBirdSprite.setColor(Color::White);
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
int checkLevelComplete(float beePositions[][20], int flowersArrayIndex, int bulletCount, int selectedLevel, float fastBeePositions[][15], int totalShots) {

  // if all bees are killed AND flowers are not full then WIN . if all bees are killed AND flowers are full then LOSE
  bool allBeesKilled = true;
  int numberOfRegularBees = selectedLevel == 0 ? 20 : selectedLevel == 1 ? 15 : selectedLevel == 2 ? 20 : 20;
  int numberOfFastBees = selectedLevel == 0 ? 0 : selectedLevel == 1 ? 5 : selectedLevel == 2 ? 10 : 15;
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

  // if flowers are full AND bullets < totalShots-56 then RESTART
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

void resetForLevel1(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[5][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots) {
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
    beePositions[5][i] = 0; // hasCreatedFlower flag
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

  for (int i=3; i<gameRows*gameColumns; i++) {
    honeyCombArray[0][i] = -99;
    honeyCombArray[1][i] = -99;
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
  for (int i = 0; i < 15; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
    fastBeePositions[5][i] = 0; // hasCreatedFlower flag
  }
}

void resetForLevel2(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots) {
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
    beePositions[5][i] = 0; // hasCreatedFlower flag
  }

  for (int i = 0; i < 15; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
    fastBeePositions[5][i] = 0; // hasCreatedFlower flag
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

  for (int i=9; i<gameRows*gameColumns; i++) {
    honeyCombArray[0][i] = -99;
    honeyCombArray[1][i] = -99;
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

void resetForLevel3(Clock& bulletClock, Clock& gameClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float beePositions[][20], float& player_x, float& player_y, int& honeyCombArrayIndex, int& beeHiveArrayIndex, int& flowersArrayIndex, Sprite& hummingBirdSprite, Clock& movementClock, Clock& bulletCollisionClock, Clock& respawnClock, int& movementCount, int& bulletCollisionCount, int& bulletCount, float rectangleHeights[], int& numberOfRectangles, bool& firstTime, int honeyCombArray[][gameRows*gameColumns], int beeHiveArray[][gameRows*gameColumns], int flowersArray[], Music& bgMusic, float fastBeePositions[][15], int redHoneyCombArray[][gameRows*gameColumns], int& redHoneyCombArrayIndex, int& totalShots, int selectedLevel) {
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
    beePositions[5][i] = 0; // hasCreatedFlower flag
  }

  for (int i = 0; i < 15; i++) {
    fastBeePositions[0][i] = (rand() % 2 == 0) ? 0 : resolutionX-32; // bee_x
    fastBeePositions[1][i] = 0; // bee_y
    fastBeePositions[2][i] = 0; // moveDown flag
    fastBeePositions[3][i] = static_cast<int>(fastBeePositions[0][i])==0 ? 1 : 0; // bee_moving_right flag
    fastBeePositions[4][i] = 0; // isNextHoneyComb flag
    fastBeePositions[5][i] = 0; // hasCreatedFlower flag
  }

  player_x = (gameColumns / 2) * boxPixelsX;
	player_y = (gameRows - 4) * boxPixelsY;

  bullet_x = player_x;
  bullet_y = player_y;

  flowersArrayIndex = 0;

  for (int j=0; j<gameRows*gameColumns; j++) {
    redHoneyCombArray[1][j] = -99;
  }

  for (int j=0; j<gameColumns+2; j++) {
    flowersArray[j] = 0;
  }  

  for (int i=0; i<15; i++) { // making 15 random honeycombs
    honeyCombArray[0][i] = static_cast<int>(rand()%21)*32;
    honeyCombArray[1][i] = static_cast<int>(rand()%13)*32;
  }

  for (int i=15; i<gameRows*gameColumns; i++) {
    honeyCombArray[0][i] = -99;
    honeyCombArray[1][i] = -99;
  }

  honeyCombArrayIndex = 15;

  if (selectedLevel == 3) {
    for (int i=0; i<5; i++) { // making 5 random bee hives
      beeHiveArray[0][i] = static_cast<int>(rand()%21)*32;
      beeHiveArray[1][i] = static_cast<int>(rand()%13)*32;
    }

    for (int i=5; i<gameRows*gameColumns; i++) {
      beeHiveArray[0][i] = -99;
      beeHiveArray[1][i] = -99;
    }

    beeHiveArrayIndex = 5;
  } else {
    for (int i=0; i<gameRows*gameColumns; i++) {
      beeHiveArray[0][i] = -99;
      beeHiveArray[1][i] = -99;
    }
    beeHiveArrayIndex = 0;
  }

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
}

void movePowerUp(int powerUpsArray[][400], int powerUpsArrayIndex, int i) {
  static Clock powerUpClocks[400];
  if (powerUpsArray[0][i] == 1) { // If the power-up is visible
    // Move the power-up downward until it reaches y = 448
    if (powerUpsArray[3][i] < 480) {
        powerUpsArray[3][i] += 2;
    }

    // Make the power-up invisible after 4 seconds
    if (powerUpClocks[i].getElapsedTime().asSeconds() > 4.0f) {
        powerUpsArray[0][i] = 0; // Set visibility to 0
    }
  } else { // else keep other clocks at 0 seconds
    for (int a=powerUpsArrayIndex; a<400; a++) {
      powerUpClocks[a].restart();
    }
  }
}

void drawPowerUp(int powerUpsArray[][400], int powerUpsArrayIndex, int i, RenderWindow& window, Sprite powerUpsSprites[], Texture HeightDecTexture, Texture HeightIncTexture, Texture speedUpTexture, Texture speedDecTexture) {
  if (powerUpsArray[0][i]==1) {// if the powerUp is visible
    // setting texture based on type
    if (powerUpsArray[1][i] == 1) {
      powerUpsSprites[i].setTexture(speedUpTexture);
    } else if (powerUpsArray[1][i] == 2) {
      powerUpsSprites[i].setTexture(speedDecTexture);
    } else if (powerUpsArray[1][i] == 3) {
      powerUpsSprites[i].setTexture(HeightIncTexture);
    } else if (powerUpsArray[1][i] == 4) {
      powerUpsSprites[i].setTexture(HeightDecTexture);
    }

    powerUpsSprites[i].setPosition(powerUpsArray[2][i], powerUpsArray[3][i]);
    window.draw(powerUpsSprites[i]);
  }
}

// Function to update the powerUpsArray based on what powerup the user picks
void updatePowerUpsArray(int powerUpsArray[][400], int& powerUpsArrayIndex, int player_x, int player_y, int powersOfPlayer[], Clock powersOfPlayerClocks[]) {
  for (int i=0; i<powerUpsArrayIndex; i++) {
    if (powerUpsArray[0][i]==1 && player_x == powerUpsArray[2][i] && 448 == powerUpsArray[3][i]-32) { // if player touches a powerup
      powerUpsArray[0][i] = 0; // make it invisible
      if (powerUpsArray[1][i]==1) { // if powerup is speed up
        powersOfPlayer[0]++;
        powersOfPlayerClocks[0].restart();
      } else if (powerUpsArray[1][i]==2) { // if powerup is speed down
        powersOfPlayer[1]++;
        powersOfPlayerClocks[1].restart();
      } else if (powerUpsArray[1][i]==3) { // if powerup is height increase
        powersOfPlayer[2]++;
        powersOfPlayerClocks[2].restart();
      } else if (powerUpsArray[1][i]==4) { // if powerup is height decrease
        powersOfPlayer[3]++;
        powersOfPlayerClocks[3].restart();
      }
    }
  }
}

// Function that handles the powerups with the time
void handlePowerUpsTime(int powerUpsArray[][400], int& powerUpsArrayIndex, int powersOfPlayer[], Clock powersOfPlayerClocks[], float& player_x, RectangleShape progressBars[4], RenderWindow& window) {
  // the cancelling out of opposite powers
  if (powersOfPlayer[0]>=1 && powersOfPlayer[1]>=1) {
    powersOfPlayer[0] = 0;
    powersOfPlayer[1] = 0;
    powersOfPlayerClocks[0].restart();
    powersOfPlayerClocks[1].restart();
  }

  if (powersOfPlayer[2]>=1 && powersOfPlayer[3]>=1) {
    powersOfPlayer[2] = 0;
    powersOfPlayer[3] = 0;
    powersOfPlayerClocks[2].restart();
    powersOfPlayerClocks[3].restart();
  }

  // setting the effect until the powerup expires (ie after 6 seconds)
  if (powersOfPlayer[0]>=1 && powersOfPlayerClocks[0].getElapsedTime().asSeconds() > 6.0f) {
    powersOfPlayer[0] = 0;
  }

  if (powersOfPlayer[1]>=1 && powersOfPlayerClocks[1].getElapsedTime().asSeconds() > 6.0f) {
    if (static_cast<int>(player_x)%32 != 0) {
      player_x = player_x-16;
    }
    powersOfPlayer[1] = 0;
  }

  if (powersOfPlayer[2]>=1 && powersOfPlayerClocks[2].getElapsedTime().asSeconds() > 6.0f) {
    powersOfPlayer[2] = 0;
  }

  if (powersOfPlayer[3]>=1 && powersOfPlayerClocks[3].getElapsedTime().asSeconds() > 6.0f) {
    powersOfPlayer[3] = 0;
  }

  // showing the progress bars and calculating their widths using time elapsed
  if (powersOfPlayer[0]>=1 && powersOfPlayerClocks[0].getElapsedTime().asSeconds() < 6.0f) {
    progressBars[0].setSize(Vector2f((6-(powersOfPlayerClocks[0].getElapsedTime().asSeconds()))*25, 20));
    progressBars[0].setPosition(40, 40);
    progressBars[0].setFillColor(Color::Green);
    window.draw(progressBars[0]);
  }

  if (powersOfPlayer[1]>=1 && powersOfPlayerClocks[1].getElapsedTime().asSeconds() < 6.0f) {
    progressBars[1].setSize(Vector2f((6-(powersOfPlayerClocks[1].getElapsedTime().asSeconds()))*25, 20));
    progressBars[1].setPosition(40, 70);
    progressBars[1].setFillColor(Color::Red);
    window.draw(progressBars[1]);
  }

  if (powersOfPlayer[2]>=1 && powersOfPlayerClocks[2].getElapsedTime().asSeconds() < 6.0f) {
    progressBars[2].setSize(Vector2f((6-(powersOfPlayerClocks[2].getElapsedTime().asSeconds()))*25, 20));
    progressBars[2].setPosition(40, 100);
    progressBars[2].setFillColor(Color::Blue);
    window.draw(progressBars[2]);
  }

  if (powersOfPlayer[3]>=1 && powersOfPlayerClocks[3].getElapsedTime().asSeconds() < 6.0f) {
    progressBars[3].setSize(Vector2f((6-(powersOfPlayerClocks[3].getElapsedTime().asSeconds()))*25, 20));
    progressBars[3].setPosition(40, 130);
    progressBars[3].setFillColor(Color::Yellow);
    window.draw(progressBars[3]);
  }
}

void drawHighScores(RenderWindow& window, char name[], int score, int& currentState, int charCount) {
  Font menuFont;
  menuFont.loadFromFile("Fonts/arial.ttf");

  Text Congratulate;
  Congratulate.setFont(menuFont);
  Congratulate.setCharacterSize(30);
  Congratulate.setPosition(resolutionX/2 - 130, 40);
  Congratulate.setFillColor(Color::White);
  Congratulate.setString("Congratulations!");
  window.draw(Congratulate);

  Text scoreText;
  scoreText.setFont(menuFont);
  scoreText.setCharacterSize(20);
  scoreText.setPosition(resolutionX/2 - 180, 90);
  scoreText.setFillColor(Color::White);
  scoreText.setString("Your score is: " + to_string(score));
  window.draw(scoreText);
  

  Text nameText;
  nameText.setFont(menuFont);
  nameText.setCharacterSize(20);
  nameText.setPosition(resolutionX/2 +20, 90);
  nameText.setFillColor(Color::White);
  if (charCount != 0) {
    nameText.setString(name);
  } else {
    nameText.setString("No name entered");
  }
  window.draw(nameText);

  // getting scores from the file
  char names[10][20];
  int scores[10];
  ifstream file("highscores.txt");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
    }

    int count = 0;
    while (file >> names[count] >> scores[count]) {
        count++;
        if (count >= 10) break;
    }

    file.close();
    
    // sorting the scores
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) { // Swap if current score is less than next
                scores[j] = scores[j] ^ scores[j+1];
                scores[j+1] = scores[j] ^ scores[j+1];
                scores[j] = scores[j] ^ scores[j+1];

                char temp[20];
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp);
            }
        }
    }

    // displaying the scores
    Text text;
    text.setFont(menuFont);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);

    for (int i = 0; i < count; i++) {
        string displayText = to_string(i + 1) + ". " + names[i] + " - " + to_string(scores[i]);
        text.setString(displayText);
        text.setPosition(resolutionX/2 - 130, 140 + i * 40); // Position each text line
        window.draw(text);
    }

    // handling close event and eneter event
    sf::Event event;
    while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        currentState = 0;
    }
  }
}