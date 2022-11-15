#pragma once

#include "gameRenderer.h"
#include <memory>
#include "constants.h"
#include <array>
#include "delegate.h"
#include "gameMaster.h"

class gameWorld final {
public:
	enum class gameState {
		player1Win,
		player2Win,
		draw,
		waitToStart,
		inProgress,
	};

	gameWorld(const std::array<characterData, constants::nbPlayers> datas);

	// start the game and return the result
	const gameState start();

	delegate<void, const unsigned short> newTurnDelegate;

public:
	const gameState getState() const { return this->state; }
	const unsigned short getTurn() const { return this->turn; }
	const gameMaster& getMaster() const { return *this->master.get(); }

private:
	// test if one of the game end conditions is true
	void testGameEnd();

	unsigned short turn;
	gameState state;
	sharedCharacter characters[constants::nbPlayers];
	std::unique_ptr<gameRenderer> renderer;
	std::unique_ptr<gameMaster> master;
};