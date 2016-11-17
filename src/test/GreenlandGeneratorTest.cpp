// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

#include "mapGenerator/GreenlandGenerator.h"
#include <boost/test/unit_test.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(GreenlandGeneratorTest)

/**
 * Tests the GreenlandGenerator.GenerateMap method. The generated map must have the 
 * same width and height as defined inside of the settings.
 */
BOOST_FIXTURE_TEST_CASE(GenerateMap_CorrectSize, GreenlandGenerator)
{
    MapSettings settings;
    settings.width = 32;
    settings.height = 32;
    settings.players = 3;
    settings.type = 0x0;

    GreenlandGenerator* generator = new GreenlandGenerator();
    Map* map = generator->Create(settings);
    
    BOOST_REQUIRE_EQUAL(map->width, settings.width);
    BOOST_REQUIRE_EQUAL(map->height, settings.height);
    
    delete map;
    delete generator;
}

/**
 * Tests the GreenlandGenerator.GenerateMap method. The generated map must contain the
 * the same number of headquarters as the number of players in the settings.
 */
BOOST_FIXTURE_TEST_CASE(GenerateMap_Headquarters, GreenlandGenerator)
{
    MapSettings settings;
    settings.width = 32;
    settings.height = 32;
    settings.players = 3;
    settings.type = 0x0;
    
    GreenlandGenerator* generator = new GreenlandGenerator();
    Map* map = generator->Create(settings);

    BOOST_REQUIRE_EQUAL(map->players, settings.players);

    for (int i = 0; i < settings.players; i++)
    {
        const Vec2 p = map->positions[i];
        BOOST_REQUIRE_NE(p.x, 0xFF);
        BOOST_REQUIRE_NE(p.y, 0xFF);
        
        const Vertex v = map->vertex[p.y * settings.width + p.x];
        BOOST_REQUIRE_EQUAL(v.object.first, (unsigned int)i);
        BOOST_REQUIRE_EQUAL(v.object.second, 0x80);
    }

    for (int i = settings.players; i < 7; i++)
    {
        BOOST_REQUIRE_EQUAL(map->positions[i].x, 0xFF);
        BOOST_REQUIRE_EQUAL(map->positions[i].y, 0xFF);
    }
    
    delete map;
    delete generator;
}

/**
 * Tests the GreenlandGenerator.GenerateMap method. The generated map must contain the
 * the same number of headquarters as the number of players in the settings - even if the
 * constructor settings indicate a water-only map.
 */
BOOST_FIXTURE_TEST_CASE(GenerateMap_WaterOnly, GreenlandGenerator)
{
    MapSettings settings;
    settings.width = 64;
    settings.height = 64;
    settings.players = 4;
    settings.type = 0x0;

    GreenlandGenerator* generator = new GreenlandGenerator(0.3, 0.8, 0.0, 0.0, 0.0, 0.0, 5, 20);
    Map* map = generator->Create(settings);
    
    BOOST_REQUIRE_EQUAL(map->players, settings.players);
    
    for (int i = 0; i < settings.players; i++)
    {
        const Vec2 p = map->positions[i];
        BOOST_REQUIRE_NE(p.x, 0xFF);
        BOOST_REQUIRE_NE(p.y, 0xFF);
        
        const Vertex v = map->vertex[p.y * settings.width + p.x];
        BOOST_REQUIRE_EQUAL(v.object.first, (unsigned int)i);
        BOOST_REQUIRE_EQUAL(v.object.second, 0x80);
    }
    
    for (int i = settings.players; i < 7; i++)
    {
        BOOST_REQUIRE_EQUAL(map->positions[i].x, 0xFF);
        BOOST_REQUIRE_EQUAL(map->positions[i].y, 0xFF);
    }
    
    delete map;
    delete generator;
}

BOOST_AUTO_TEST_SUITE_END()

