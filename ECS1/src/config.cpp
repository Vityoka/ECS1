#include "config.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

Config g_config;

void Config::loadConfig()
{
  std::ifstream fin;
  std::string line;
  std::string str;
  fin.open("config.ini");
  std::vector<std::string> configValues;
  static int i = 0;

  if (fin.is_open())
  {
    std::cout << "config.ini found" << std::endl;
    while (fin >> str)
    {
      std::cout << str << std::endl;
      if (i % 2)
      {
        configValues.push_back(str);
      }
      i++;
    }
  }
  else
  {
    std::cout << "config.ini could not be found" << std::endl;
  }

  if (configValues.size() == numOfConfigVariables)
  {
    windowConfig.width             = std::stoi(configValues[0]);
    windowConfig.height            = std::stoi(configValues[1]);
    windowConfig.frameRateLimit    = std::stoi(configValues[2]);

    playerConfig.shapeRadius       = std::stof(configValues[3]);
    playerConfig.collisionRadius   = std::stof(configValues[4]);
    playerConfig.speed             = std::stof(configValues[5]);
    playerConfig.fillColorRed      = std::stoi(configValues[6]);
    playerConfig.fillColorGreen    = std::stoi(configValues[7]);
    playerConfig.fillColorBlue     = std::stoi(configValues[8]);
    playerConfig.outlineColorRed   = std::stoi(configValues[9]);
    playerConfig.outlineColorGreen = std::stoi(configValues[10]);
    playerConfig.outlineColorBlue  = std::stoi(configValues[11]);
    playerConfig.outlineThickness  = std::stof(configValues[12]);
    playerConfig.numOfVertices     = std::stoi(configValues[13]);

    enemyConfig.shapeRadius        = std::stof(configValues[14]);
    enemyConfig.collisionRadius    = std::stof(configValues[15]);
    enemyConfig.minSpeed           = std::stof(configValues[16]);
    enemyConfig.maxSpeed           = std::stof(configValues[17]);
    enemyConfig.fillColorRed       = std::stoi(configValues[18]);
    enemyConfig.fillColorGreen     = std::stoi(configValues[19]);
    enemyConfig.fillColorBlue      = std::stoi(configValues[20]);
    enemyConfig.outlineColorRed    = std::stoi(configValues[21]);
    enemyConfig.outlineColorGreen  = std::stoi(configValues[22]);
    enemyConfig.outlineColorBlue   = std::stoi(configValues[23]);
    enemyConfig.outlineThickness   = std::stof(configValues[24]);
    enemyConfig.minNumOfVertices   = std::stoi(configValues[25]);
    enemyConfig.maxNumOfVertices   = std::stoi(configValues[26]);
    enemyConfig.smallLifespan      = std::stoi(configValues[27]);
    enemyConfig.spawnInterval      = std::stoi(configValues[28]);

    bulletConfig.shapeRadius       = std::stof(configValues[29]);
    bulletConfig.collisionRadius   = std::stof(configValues[30]);
    bulletConfig.speed             = std::stof(configValues[31]);
    bulletConfig.fillColorRed      = std::stoi(configValues[32]);
    bulletConfig.fillColorGreen    = std::stoi(configValues[33]);
    bulletConfig.fillColorBlue     = std::stoi(configValues[34]);
    bulletConfig.outlineColorRed   = std::stoi(configValues[35]);
    bulletConfig.outlineColorGreen = std::stoi(configValues[36]);
    bulletConfig.outlineColorBlue  = std::stoi(configValues[37]);
    bulletConfig.outlineThickness  = std::stof(configValues[38]);
    bulletConfig.numOfVertices     = std::stoi(configValues[39]);
    bulletConfig.lifespan          = std::stoi(configValues[40]);

    std::cout << "Configuration parameters loaded successfully." << std::endl;

    assert(enemyConfig.minNumOfVertices >= 3);
    assert(enemyConfig.minNumOfVertices < enemyConfig.maxNumOfVertices);
  }
  else
  {
    std::cout << "Invalid config file, number of values does not the required number." << std::endl;
  }

  fin.close();
}
