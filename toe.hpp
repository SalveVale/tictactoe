#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <vector>

class Toe
{
private:
  //window
  sf::RenderWindow* window;
  sf::VideoMode videomode;
  sf::Event evnt;
  
  //mouse
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;
  
  //grid
  sf::RectangleShape box;

  std::vector<sf::RectangleShape> grid1;
  std::vector<sf::RectangleShape> grid2;
  std::vector<sf::RectangleShape> grid3;

  std::vector<std::vector<sf::RectangleShape>> grid;
  
  //pieces
  sf::Texture xTexture;
  sf::Texture oTexture;
  sf::Texture emptyTexture;
  
  sf::Sprite x;
  sf::Sprite o;
  sf::Sprite emptySprite;

  std::vector<sf::Sprite> sprites1;
  std::vector<sf::Sprite> sprites2;
  std::vector<sf::Sprite> sprites3;
  
  std::vector<std::vector<sf::Sprite>> sprites;

  std::vector<int> pieces1;
  std::vector<int> pieces2;
  std::vector<int> pieces3;
  
  std::vector<std::vector<int>> pieces;
  
  //logic
  int toMove;
  unsigned clickTimer;
  
  //functions
  void initVariables();
  
  //window
  void initWindow();
  void pollEvents();
  void updateMousePos();
  
  //grid
  void updateGrid();
  void drawStuff();
  
  //pieces
  void updateSprites();
  void updatePieces();
  
public:
  //functions
  Toe();
  ~Toe();
  
  //window
  const bool running() const;
  void update();
  void render();

  bool xWin;
  bool oWin;
};
