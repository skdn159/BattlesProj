#pragma once
#include "PacketType.h"

#define MAX_SHIP_NUM 5
#define MAX_SHIP_LEN 5

#define AIRCRAFT_LEN 5
#define BATTLESHIP_LEN 4
#define CRUISER_LEN 3
#define DESTROYER_LEN 2


typedef MapDataTypes ShipType;

enum Direction
{
	DIR_HORIZONTAL,
	DIR_VERTICAL,
};


class ShipData
{
public:
	ShipData();

	Coord* GetShipCoordArray(const ShipType shipType);
	void SetShipCoord(const ShipType shipType, const int index, const Coord coord);
	void SetShip(const ShipType shipType, const Coord* const coordArr);
	void SetShip(const ShipType shipType, const Coord startCoord, const Direction dir);

	void ToMapData(char* const mapData);

public:
	static const int SHIP_LEN[MAX_SHIP_NUM + 1];

private:
	Coord ship[MAX_SHIP_NUM + 1][MAX_SHIP_LEN];

};

