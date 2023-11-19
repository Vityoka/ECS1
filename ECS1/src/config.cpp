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
    playerConfig.shapeRadius       = std::stof(configValues[0]);
    playerConfig.collisionRadius   = std::stof(configValues[1]);
    playerConfig.speed             = std::stof(configValues[2]);
    playerConfig.fillColorRed      = std::stoi(configValues[3]);
    playerConfig.fillColorGreen    = std::stoi(configValues[4]);
    playerConfig.fillColorBlue     = std::stoi(configValues[5]);
    playerConfig.outlineColorRed   = std::stoi(configValues[6]);
    playerConfig.outlineColorGreen = std::stoi(configValues[7]);
    playerConfig.outlineColorBlue  = std::stoi(configValues[8]);
    playerConfig.outlineThickness  = std::stof(configValues[9]);
    playerConfig.numOfVertices     = std::stoi(configValues[10]);

    enemyConfig.shapeRadius        = std::stof(configValues[11]);
    enemyConfig.collisionRadius    = std::stof(configValues[12]);
    enemyConfig.minSpeed           = std::stof(configValues[13]);
    enemyConfig.maxSpeed           = std::stof(configValues[14]);
    enemyConfig.fillColorRed       = std::stoi(configValues[15]);
    enemyConfig.fillColorGreen     = std::stoi(configValues[16]);
    enemyConfig.fillColorBlue      = std::stoi(configValues[17]);
    enemyConfig.outlineColorRed    = std::stoi(configValues[18]);
    enemyConfig.outlineColorGreen  = std::stoi(configValues[19]);
    enemyConfig.outlineColorBlue   = std::stoi(configValues[20]);
    enemyConfig.outlineThickness   = std::stof(configValues[21]);
    enemyConfig.minNumOfVertices   = std::stoi(configValues[22]);
    enemyConfig.maxNumOfVertices   = std::stoi(configValues[23]);

    bulletConfig.shapeRadius       = std::stof(configValues[24]);
    bulletConfig.collisionRadius   = std::stof(configValues[25]);
    bulletConfig.speed             = std::stof(configValues[26]);
    bulletConfig.fillColorRed      = std::stoi(configValues[27]);
    bulletConfig.fillColorGreen    = std::stoi(configValues[28]);
    bulletConfig.fillColorBlue     = std::stoi(configValues[29]);
    bulletConfig.outlineColorRed   = std::stoi(configValues[30]);
    bulletConfig.outlineColorGreen = std::stoi(configValues[31]);
    bulletConfig.outlineColorBlue  = std::stoi(configValues[32]);
    bulletConfig.outlineThickness  = std::stof(configValues[33]);
    bulletConfig.numOfVertices     = std::stoi(configValues[34]);
    bulletConfig.lifespan          = std::stoi(configValues[35]);

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
