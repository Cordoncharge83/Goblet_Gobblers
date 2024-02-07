// board.h
#ifndef BOARD_H
#define BOARD_H
#include <vector>


enum class Size { NONE, SMALL, MEDIUM, LARGE };
enum class Player { NO_PLAYER, PLAYER_1, PLAYER_2 };

#define DIMENSIONS 3


class Piece {
private:
    Size size;
    Player holder;

public:
    //Constructeurs
    Piece();
    Piece(Size s, Player h);
    //Vérifier la taille de la pièce
    Size getSize() const;
    //Déterminer le joueur possédant la pièce
    Player getHolder() const;
};

class PlayerPieces {
private:
    int small;
    int medium;
    int large;

public:
    PlayerPieces();
    void initializePieces();
    void decrementSize(Size size);
    int getSizeCount(Size size) const;
};

class Board {
private:
    /**
     * @brief Structure du plateau
     * Le plateau est composé de vecteurs de Piece et de deux listes PlayerPieces qui stockent
     * les pièces de chaque taille possédées par chaque joueur.
     * Le choix de vecteurs de pièces est pour pouvoir stocker les différentes pièces placeés les une au dessus des
     * autres dans une case données, et donc, dans le cas où le joueur possédant la plus grande pièce va la déplacer à une autre
     * case, on aura accès directement à la pièce en dessous
     */
    std::vector<Piece> board[3][3];
    PlayerPieces playerPieces[2];

public:
    // Constructeur
    Board();
    // Afficher le Plateau
    void display() const;
    // Supprimer le Plateau
    ~Board();
    // Placer une pièce
    int placePiece(Player player, Size size, int row, int col);
    // Déplacer une pièce
    int movePiece(Player current_player, int source_line, int source_column, int target_line, int target_column);
    // Joueur suivant
    Player next_player(Player current_player);
    //Déterminer le joueur occupant une telle case
    Player get_place_holder(int line, int column);
    //Vérifier le gagnant
    Player get_winner();
};

#endif // BOARD_H
