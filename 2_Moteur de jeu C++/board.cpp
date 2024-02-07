#include "board.h"
#include <iostream>

Piece::Piece() : size(Size::NONE), holder(Player::NO_PLAYER) {}

Piece::Piece(Size s, Player h) : size(s), holder(h) {}

Size Piece::getSize() const {
    return size;
}
Player Piece::getHolder() const {
    return holder;
}

PlayerPieces::PlayerPieces() : small(0), medium(0), large(0) {}

void PlayerPieces::initializePieces() {
    // Initialiser le nombre de pièces de chaque taille
    small = 2;
    medium = 2;
    large = 2;
}
void PlayerPieces::decrementSize(Size size) {
    // Décrémenter le compteur de la taille spécifiée
    switch (size) {
    case Size::SMALL:
        --small;
        break;
    case Size::MEDIUM:
        --medium;
        break;
    case Size::LARGE:
        --large;
        break;
    default:
        break;
    }
}

int PlayerPieces::getSizeCount(Size size) const {
    // Renvoie le nombre de pièces de la taille spécifiée
    switch (size) {
    case Size::SMALL:
        return small;
    case Size::MEDIUM:
        return medium;
    case Size::LARGE:
        return large;
    default:
        return 0;
    }
}

Board::Board() {
    // Initialiser le plateau avec des pièces vides
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j].push_back(Piece(Size::NONE, Player::NO_PLAYER));
        }
    }
    // Initialiser les pièces des joueurs
    playerPieces[0] = PlayerPieces();
    playerPieces[0].initializePieces();  // Initialiser les pièces du joueur 1
    playerPieces[1] = PlayerPieces();
    playerPieces[1].initializePieces();  // Initialiser les pièces du joueur 2
}
Board::~Board() {
    std::cout << "Merci d'avoir joué !" << std::endl;
}

int Board::placePiece(Player player, Size size, int row, int col) {
    // On vérifie que le joueur possède bien une pièce de la taille souhaitée
    if ((player == Player::PLAYER_1 && playerPieces[0].getSizeCount(size) == 0) | (player == Player::PLAYER_2 && playerPieces[1].getSizeCount(size) == 0)){
        return 1;
    }
    // On vérifie qu'il n'y pas une pièce de taille égale ou plus importante sur la même case
    else if (board[row][col].back().getSize() >= size){
        return 2;
    }
    // On vérifie les entrées possibles (joueur, taille pièce, ligne, colonne)
    else if (size < Size::SMALL | size > Size::LARGE | row < 0 | row >= DIMENSIONS | col < 0 | col >= DIMENSIONS) {
        return 3;
    }

    // On place la pièce sur le plateau
    board[row][col].push_back(Piece( size, player));
    // On met à jour le nombre de pièces restantes pour le joueur
    if (player == Player::PLAYER_1){
        playerPieces[0].decrementSize(size);
    }
    else{
        playerPieces[1].decrementSize(size);
        }
    return 0;
}

int Board::movePiece(Player current_player,int source_line, int source_column, int target_line, int target_column) {
    if (board[source_line][source_column].empty()) {
        return 1; // Pas de pièces à la place de départ
    }
    else if(board[source_line][source_column].back().getSize() <= board[target_line][target_column].back().getSize()){
        return 2; // pièce à déplacer trop petite
    }
    else if (source_line < 0 | source_line >= DIMENSIONS | source_column < 0 | source_column >= DIMENSIONS | target_line < 0 | target_line >= DIMENSIONS | target_column < 0 | target_column >= DIMENSIONS){
        return 3; // entrée illégale
    }
    else if(board[source_line][source_column].back().getHolder() != current_player){
        return 4; // Action illégale, joueur ne possède pas cette pièce
    }

    // Obtenir la pièce du dessus de la pile dans la case source
    Piece pieceToMove = board[source_line][source_column].back();

    // Déplacer la pièce vers la case cible
    board[target_line][target_column].push_back(pieceToMove);
    board[source_line][source_column].pop_back(); // Retirer la pièce de la case source

    return 0;

}

Player Board::next_player(Player current_player) {
    return (current_player == Player::PLAYER_1) ? Player::PLAYER_2 : Player::PLAYER_1;
}
Player Board::get_place_holder(int line, int column) {
    // Trouver le joueur possédant la pièce la plus forte dans la case spécifiée
    Player player = Player::NO_PLAYER;
    Size maxSize = Size::NONE;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j].back().getSize() != Size::NONE) {
                if (board[i][j].back().getSize() > maxSize) {
                    maxSize = board[i][j].back().getSize();
                    player = board[i][j].back().getHolder();
                }
            }
        }
    }

    return player;
}

Player Board::get_winner() {
    // Déterminer s'il y a une ligne gagnante
    for (int i = 0; i < DIMENSIONS; ++i) {
        if (board[i][0].back().getHolder() == board[i][1].back().getHolder() && board[i][1].back().getHolder() == board[i][2].back().getHolder() && board[i][0].back().getHolder() != Player::NO_PLAYER) {
            return board[i][0].back().getHolder();
        }
    }

    // Déterminer s'il y a une colonne gagante
    for (int i = 0; i < DIMENSIONS; ++i) {
        if (board[0][i].back().getHolder() == board[1][i].back().getHolder() && board[1][i].back().getHolder() == board[2][i].back().getHolder() && board[0][i].back().getHolder() != Player::NO_PLAYER) {
            return board[i][0].back().getHolder();
        }
    }

    // Déterminer s'il y a une diagonale gagnante
    if ((board[0][0].back().getHolder() == board[1][1].back().getHolder() && board[1][1].back().getHolder() == board[2][2].back().getHolder() && board[0][0].back().getHolder() != Player::NO_PLAYER) ||
        (board[0][2].back().getHolder() == board[1][1].back().getHolder() && board[1][1].back().getHolder() == board[2][0].back().getHolder() && board[0][2].back().getHolder() != Player::NO_PLAYER)) {
        return board[1][1].back().getHolder();
    }

    return Player::NO_PLAYER; // No winner yet
}






