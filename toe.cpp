#include "toe.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

Toe::Toe()
{
  this->initVariables();
  this->initWindow();
}

Toe::~Toe()
{
  delete this->window;
}

void Toe::initVariables()
{
  this->window = nullptr;

  //init box
  this->grid.push_back(grid1);
  this->grid.push_back(grid2);
  this->grid.push_back(grid3);
  this->box.setSize(sf::Vector2f(300.f, 300.f));
  this->box.setFillColor(sf::Color::Red);
  
  //init grid of boxes
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      this->box.setPosition(sf::Vector2f(300 * i, 300 * j));
      this->grid[i].push_back(box);
    }
  }
  
  //init sprites
  if (!this->xTexture.loadFromFile("xTexture.png")) std::cout << "Could not load xTexture" << std::endl;
  if (!this->oTexture.loadFromFile("oTexture.png")) std::cout << "Could not load oTexture" << std::endl;
  if (!this->emptyTexture.loadFromFile("emptyTexture.png")) std::cout << "Could not load emptyTexture" << std::endl;
  
  this->x.setTexture(this->xTexture);
  this->o.setTexture(this->oTexture);
  this->emptySprite.setTexture(this->emptyTexture);
  
  this->sprites.push_back(this->sprites1);
  this->sprites.push_back(this->sprites2);
  this->sprites.push_back(this->sprites3);
  
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
       sprites[i].push_back(this->emptySprite);
    }
  }
  
  //logic
  this->clickTimer = 0;
  this->toMove = 0;
  this->xWin = false;
  this->oWin = false;
  
  for (int i=0; i<3; i++)
  {
    this->pieces1.push_back(0);
    this->pieces2.push_back(0);
    this->pieces3.push_back(0);
  }
  this->pieces.push_back(this->pieces1);
  this->pieces.push_back(this->pieces2);
  this->pieces.push_back(this->pieces3);
}

void Toe::initWindow()
{
  this->videomode.width = 900;
  this->videomode.height = 900;
  
  this->window = new sf::RenderWindow(videomode, "Tic Tac Toe");
  
  this->window->setFramerateLimit(60);
}

const bool Toe::running() const
{
  return this->window->isOpen();
}

void Toe::pollEvents()
{
  while (this->window->pollEvent(this->evnt))
  {
    switch (this->evnt.type)
    {
      case sf::Event::Closed:
        this->window->close();
        break;
      case sf::Event::KeyPressed:
        if (evnt.key.code == sf::Keyboard::Escape) this->window->close();
        break;
      default:
        break;
    }
  }
}

void Toe::updateMousePos()
{
  this->mousePosWindow = sf::Mouse::getPosition(*this->window);
  this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Toe::updateGrid()
{
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      if (this->grid[i][j].getGlobalBounds().contains(mousePosView))
      {
        this->grid[i][j].setFillColor(sf::Color(30, 30, 30));
      }
      else
      {
        this->grid[i][j].setFillColor(sf::Color::Black);
      }
    }
  }
}

void Toe::updateSprites()
{
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->grid[i][j].getGlobalBounds().contains(mousePosView) && this->clickTimer == 0)
      {
        this->clickTimer = 20;
        
        if (this->pieces[i][j] > 0) break;
        
        if (this->toMove == 0)
        {
          this->pieces[i][j] = 1;
          this->x.setPosition(sf::Vector2f(300 * i, 300 * j));
          this->sprites[i][j] = this->x;
          
          this->toMove = 1;
        }
        else
        {
          this->pieces[i][j] = -1;

          this->o.setPosition(sf::Vector2f(300 * i, 300 * j));
          this->sprites[i][j] = this->o;
          
          this->toMove = 0;
        }
        this->updatePieces();
      }  
    }
  }
}

void Toe::updatePieces()
{
  for (int i=0; i<3; i++)
  {
    int sum = 0;
    for (int j=0; j<3; j++)
    {
      sum += this->pieces[i][j];
    }
    switch (sum)
    {
      case 3:
        this->xWin = true;
        break;
      case -3:
        this->oWin = true;
      default:
        break;
    }
  }
  
  for (int i=0; i<3; i++)
  {
    int sum = 0;
    for (int j=0; j<3; j++)
    {
      sum += this->pieces[j][i];
    }
    switch (sum)
    {
      case 3:
        this->xWin = true;
        break;
      case -3:
        this->oWin = true;
      default:
        break;
    }
  }

  int sum = 0;
  sum += this->pieces[0][0] + this->pieces[1][1] + this->pieces[2][2];
  switch (sum)
  {
    case 3:
      this->xWin = true;
      break;
    case -3:
      this->oWin = true;
    default:
      break;
  }
  
  sum = 0;
  sum += this->pieces[0][2] + this->pieces[1][1] + this->pieces[2][0];
  switch (sum)
  {
    case 3:
      this->xWin = true;
      break;
    case -3:
      this->oWin = true;
    default:
      break;
  }
}

void Toe::drawStuff()
{
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      this->window->draw(this->grid[i][j]);
      if (this->sprites[i].size() > 0)
      this->window->draw(this->sprites[i][j]);
    }
  }
}

void Toe::update()
{
  this->pollEvents();
  this->updateMousePos();
  this->updateGrid();
  this->updateSprites();

  if (this->clickTimer > 0) this->clickTimer--;
}

void Toe::render()
{
  this->window->clear();
  this->drawStuff();
  this->window->display();
}