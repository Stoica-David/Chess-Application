#pragma once

#include "Position.h"
#include "IGameStatus.h"
#include "IGameListener.h"

#include <string>
#include <unordered_map>

using String = std::string;
using IGamePtr = std::shared_ptr<class IGame>;

enum class EFileFormat
{
	FEN,
	PGN
};

class IGame
{
public:
	/**
	 * Produces a game by calling the Game() constructor
	 * 
	 * @param wantTimer specifies type of game that user chooses
	 * 
	 * @return pointer to a IGame
	 */
	static IGamePtr Produce(bool wantTimer = false);

	/**
	 * Necessary virtual destructor
	 */
	virtual ~IGame() = default;

	/**
	 * Adds a listeners 
	 * Binds timer class method "SetNotifyChange" to game class method "NotifyTimerChange"
	 * 
	 * @param IGameListenerPtr is a shared pointer to a listener
	 */
	virtual void AddListener(IGameListenerPtr) = 0;
	/**
	* Removes listeners by making them weak pointers
	* 
	* @param IGameListener* normal pointer to listener
	*/
	virtual void RemoveListener(IGameListener*) = 0;

	/**
	 * Restarts a game and informs ChessUiQt listener
	 */
	virtual void Restart() = 0;

	/**
	 * Moves a piece from an initial position to another position
	 * Contains all the logic of pieces, checks the surroundings to see if a specific move is possible 
	 * It throws specific exceptions if the move is not possible
	 * Notifies the Ui listener about the move
	 * Adds moves to the PGN format
	 * 
	 * @param Position is a pair with two coordinates
	 */
	virtual void Move(Position, Position) = 0;
	/**
	 * Updates state of the game 
	 * Switches turn for the other player to in order to respond
	 */
	virtual void ProposeDraw() = 0;
	/**
	 * Dictates is the game stops or continues depending on the other player's response
	 * 
	 * @param bool true if the player agreed to draw, false otherwise
	 */
	virtual void DrawResponse(bool) = 0;
	/**
	 * Promotes a piece
	 * Updates the PGN 
	 * Resumes the game to playing state
	 * Switches turn
	 * 
	 * @param EPieceType specifies the type wanted to promote in
	 */
	virtual void PromoteTo(EPieceType) = 0;

	/**
	 * Goes in the bitset vector, takes the confNrth configuration from history
	 * Transforms this configuration into a Board
	 * Updates current board to the newly converted one
	 * @param confNr configuration number
	 */
	virtual void ShowConfiguration(int confNr) = 0;

	/**
	 * Contains getters for all informations related to a game status
	 * 
	 * @return IGameStatus pointer to a IGameStatus class
	 */
	virtual const IGameStatus* GetStatus() const = 0;

	/**
	 * Saves either FEN or PGN formats to computer
	 * 
	 * @param format specifies the format in which to save the state of the board
	 * @param file the string containing the info
	 */
	virtual void Save(EFileFormat format, const String& file) const = 0;
	/**
	 * Loads either FEN or PGN formats from computer to board
	 * 
	 * @param format specifies the format in which to load the state of the board
	 * @param file the string containing the info
	 */
	virtual void Load(EFileFormat format, const String& file) = 0;

	/**
	 * Updates the state of the game 
	 * Stops timer
	 */
	virtual void PauseGame() = 0;
	/**
	 * Updates the state of the game
	 * Starts timer again
	 */
	virtual void ResumeGame() = 0;
};
