#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

enum GameState {GAME, CHECK, CMATE, STALE};

static sf::Texture pawnTextureW;
static sf::Texture bishopTextureW;
static sf::Texture knightTextureW;
static sf::Texture rookTextureW;
static sf::Texture queenTextureW;
static sf::Texture kingTextureW;

static sf::Texture pawnTextureB;
static sf::Texture bishopTextureB;
static sf::Texture knightTextureB;
static sf::Texture rookTextureB;
static sf::Texture queenTextureB;
static sf::Texture kingTextureB;

void PreLoad();

void foo(sf::RenderWindow* w);
