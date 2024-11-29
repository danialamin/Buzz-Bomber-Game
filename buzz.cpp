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
void runGame(int& selectedLevel, float& player_x, float& player_y, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float& bee_x, float& bee_y, bool& bee_moving_right, int& bee_current_row, Sprite& beeSprite, Clock& beeClock, bool& moveDown, RectangleShape& groundRectangle, RenderWindow& window);
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void moveBee(float&, float&, bool&, int&, Sprite&, Clock&, bool&);
void drawBee(RenderWindow&, float&, float&, Sprite&);

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
	bgMusic.setVolume(50);
	bgMusic.setLoop(true);
	bgMusic.play();

	// Initializing Player and Player Sprites.
	float player_x = (gameColumns / 2) * boxPixelsX;
	float player_y = (gameRows - 4) * boxPixelsY;

	Texture playerTexture;
	Sprite playerSprite;
	playerTexture.loadFromFile("Textures/spray.png");
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
	Texture beeTexture;
	Sprite beeSprite;
	beeTexture.loadFromFile("Textures/Regular_bee.png");
	beeSprite.setTexture(beeTexture);
	beeSprite.setScale(1.3, 1.3);

	float bee_x = (rand() % 2 == 0) ? 0 : resolutionX-32;  // Starting x position
	float bee_y = 0;  // Starting y position at top of screen
	bool bee_moving_right = static_cast<int>(bee_x)==0 ? true : false;  // Initial movement direction
	int bee_current_row = 0;  // Track current row
	bool moveDown = 0; // a flag to tell when the bee should move down

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
                runGame(selectedLevel, player_x, player_y, playerSprite, bulletSprite, bulletClock, bullet_x, bullet_y, bullet_exists, bee_x, bee_y, bee_moving_right, bee_current_row, beeSprite, beeClock, moveDown, groundRectangle, window);
                // currentState = MENU_STATE;
                break;

            case EXIT_STATE:
                window.close();
                break;
        }

		window.display();

	}
}

void runGame(int& selectedLevel, float& player_x, float& player_y, Sprite& playerSprite, Sprite& bulletSprite, Clock& bulletClock, float& bullet_x, float& bullet_y, bool& bullet_exists, float& bee_x, float& bee_y, bool& bee_moving_right, int& bee_current_row, Sprite& beeSprite, Clock& beeClock, bool& moveDown, RectangleShape& groundRectangle, RenderWindow& window) {
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
						bullet_exists = true;
        	    }
			}

			moveBee(bee_x, bee_y, bee_moving_right, bee_current_row, beeSprite, beeClock, moveDown);
        	drawBee(window, bee_x, bee_y, beeSprite);

			if (bullet_exists)
			{
				moveBullet(bullet_y, bullet_exists, bulletClock);
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
        case 1:
            cout<< "hello2"<< endl;
            break;
        case 2:
            cout<< "hello3"<< endl;
            break;
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
        resolutionX/2 - titleText.getGlobalBounds().width/2, 
        100
    );
    titleText.setFillColor(Color::White);

    // Menu Options
    string menuOptions[] = {"Start Game", "Choose Level", "Exit"};
    Text optionTexts[3];

    for (int i = 0; i < 3; i++) {
        optionTexts[i].setString(menuOptions[i]);
        optionTexts[i].setCharacterSize(30);
        optionTexts[i].setPosition(
            resolutionX/2 - optionTexts[i].getGlobalBounds().width/2, 
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
        resolutionX/2 - titleText.getGlobalBounds().width/2, 
        100
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
            resolutionX/2 - levelTexts[i].getGlobalBounds().width/2, 
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
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock) {
	if (bulletClock.getElapsedTime().asMilliseconds() < 20)
		return;

	bulletClock.restart();
	bullet_y -= 16;
	if (bullet_y < -32)
		bullet_exists = false;
}
void drawBullet(sf::RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet_x, bullet_y);
	window.draw(bulletSprite);
}

// function to move bee
void moveBee(float& bee_x, float& bee_y, bool& bee_moving_right, int& bee_current_row, Sprite& beeSprite, Clock& beeClock, bool& moveDown) {
    if (beeClock.getElapsedTime().asSeconds() < 0.3) {
		cout<< "bee_x= "<< bee_x<< " bee_y="<< bee_y<< endl;
		return;  // Wait before next movement
    }

	beeClock.restart();

    if (bee_moving_right) { // if bee moving right
		if (bee_x < resolutionX-32)
	        bee_x += boxPixelsX;
        
        // Check if reached right edge
        if (bee_x == resolutionX-32 && !moveDown) {
			moveDown = true;
        } else if (bee_x == resolutionX-32 && moveDown) {
			bee_y += boxPixelsY;  // Move down to next row
            bee_current_row++; 
            bee_moving_right = false;
			moveDown = false;
		}
    } else { // if bee moving left
		if (bee_x > 0)
            bee_x -= boxPixelsX;

        // Check if reached right edge
        if (bee_x == 0 && !moveDown) {
            moveDown = true;
        } else if (bee_x == 0 && moveDown) {
            bee_y += boxPixelsY;  // Move down to next row
            bee_current_row++;
            bee_moving_right = true;
            moveDown = false;
        }    

	}
    
    // Reset to top if reached bottom
    if (bee_current_row > 16) {
        bee_x = 0;  // Or use a random start position
        bee_y = 0;
        bee_current_row = 0;
        bee_moving_right = true;
    }
}

// Drawing function for a bee
void drawBee(RenderWindow& window, float& bee_x, float& bee_y, Sprite& beeSprite) {
    beeSprite.setPosition(bee_x, bee_y);
    window.draw(beeSprite);
}
