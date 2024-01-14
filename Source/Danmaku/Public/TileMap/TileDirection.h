// Copyright Huy Phan. All Rights Reserved.

#pragma once


UENUM()
enum class ETileDirection : uint8
{
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest,
};

inline ETileDirection operator+(ETileDirection Left, const uint8 Right)
{
	return static_cast<ETileDirection>((static_cast<uint8>(Left) + Right) % 8);
}

inline ETileDirection operator-(ETileDirection Left, const uint8 Right)
{
	return static_cast<ETileDirection>((static_cast<uint8>(Left) + 8 - Right) % 8);
}
