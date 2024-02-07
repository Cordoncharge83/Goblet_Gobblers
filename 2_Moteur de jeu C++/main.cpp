#include <stdio.h>
#include "board.h"

#include <iostream>

void Board::display() const {
    for (int i = 0; i < DIMENSIONS; ++i) {
        for (int j = 0; j < DIMENSIONS; ++j) {
            if (!board[i][j].empty()) {
                // Afficher la taille et le joueur de la pièce la plus récente dans la case
                std::cout << "(";
                switch (board[i][j].back().getSize()) {
                case Size::NONE:
                    std::cout << "-";
                    break;
                case Size::SMALL:
                    std::cout << "S";
                    break;
                case Size::MEDIUM:
                    std::cout << "M";
                    break;
                case Size::LARGE:
                    std::cout << "L";
                    break;
                default:
                    break;
                }
                std::cout << ", " << (board[i][j].back().getHolder() == Player::PLAYER_1 ? "X" : (board[i][j].back().getHolder() == Player::PLAYER_2 ? "O" : ".")) << ") | ";
            } else {
                // Case vide
                std::cout << "(Empty) | ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    // Afficher les listes de PlayerPieces
    std::cout << "Player 1 Pieces: (S: " << playerPieces[0].getSizeCount(Size::SMALL) << ", M: " << playerPieces[0].getSizeCount(Size::MEDIUM) << ", L: " << playerPieces[0].getSizeCount(Size::LARGE) << ")" << std::endl;
    std::cout << "Player 2 Pieces: (S: " << playerPieces[1].getSizeCount(Size::SMALL) << ", M: " << playerPieces[1].getSizeCount(Size::MEDIUM) << ", L: " << playerPieces[1].getSizeCount(Size::LARGE) << ")" << std::endl;
}


int main() {
    //Créer le plateau et initialiser le premier joueur
    Board game;
    Player current_player = Player::PLAYER_1;

    // Boucle de jeu
    while (1) {
        // Afficher l'état du plateau
        game.display();

        // Demander à l'utilisateur de choisir une action (placement ou déplacement)
        printf("Joueur %c, choisissez une action (P pour placer, D pour déplacer, Q pour Quitter): ", current_player == Player::PLAYER_1 ? 'X' : 'O');
        char action;
        scanf(" %c", &action);

        if (action == 'Q' || action == 'q'){
            // Quitter le jeu si l'utilisateur choisit de quitter
            printf("Vous avez choisi de quitter le jeu. Au revoir !\n");
            break;
        }
        else if (action == 'P' || action == 'p') {
            // Si l'utilisateur choisit de placer une pièce
            // Demander les coordonnées et la taille de la pièce
            int line, column;
            Size piece_size;

            printf("Entrez la ligne (0-2) : ");
            scanf("%d", &line);

            printf("Entrez la colonne (0-2) : ");
            scanf("%d", &column);

            printf("Entrez la taille de la pièce (S, M, L) : ");
            char size_input;
            scanf(" %c", &size_input);

            // Convertir la taille de la pièce en énumération
            if (size_input == 'S' || size_input == 's') {
                piece_size = Size::SMALL;
            } else if (size_input == 'M' || size_input == 'm') {
                piece_size = Size::MEDIUM;
            } else if (size_input == 'L' || size_input == 'l') {
                piece_size = Size::LARGE;
            } else {
                printf("Taille de pièce non valide.\n");
                continue;
            }

            // Placer la pièce sur le plateau de jeu
            int result = game.placePiece(current_player, piece_size, line, column);

            if (result != 0) {
            // Afficher un message d'erreur en fonction du résultat
            switch (result) {
                case 1:
                    printf("Erreur : Le joueur n'a pas la pièce de la taille souhaitée.\n");
                    break;
                case 2:
                    printf("Erreur : La pièce à placer est trop petite ou égale à la pièce existante.\n");
                    break;
                case 3:
                    printf("Erreur : Coordonnées invalides.\n");
                    break;
                // Ajoutez d'autres codes d'erreur si nécessaire
                default:
                    printf("Erreur inconnue.\n");
            }
            }
            else {
                // Passer au joueur suivant
                current_player = game.next_player(current_player);
            }
        } else if (action == 'D' || action == 'd') {
            // Si l'utilisateur choisit de déplacer une pièce
            // Demander les coordonnées source et destination
            int source_line, source_column, target_line, target_column;

            printf("Entrez la ligne source (0-2) : ");
            scanf("%d", &source_line);

            printf("Entrez la colonne source (0-2) : ");
            scanf("%d", &source_column);

            printf("Entrez la ligne cible (0-2) : ");
            scanf("%d", &target_line);

            printf("Entrez la colonne cible (0-2) : ");
            scanf("%d", &target_column);

            // Déplacer la pièce sur le plateau de jeu
            int result = game.movePiece(current_player, source_line, source_column, target_line, target_column);

            if (result != 0) {
            // Afficher un message d'erreur en fonction du résultat
            switch (result) {
                case 1:
                    printf("Erreur : Pas de pièce disponible à la case de départ.\n");
                    break;
                case 2:
                    printf("Erreur : La pièce à placer est trop petite ou égale à la pièce existante.\n");
                    break;
                case 3:
                    printf("Erreur : Coordonnées invalides.\n");
                    break;
                case 4:
                    printf("Erreur : Cette pièce appartient à l'autre joueur. \n");
                    break;
                // Ajoutez d'autres codes d'erreur si nécessaire
                default:
                    printf("Erreur inconnue.\n");
            }
            }
            else {
                // Passer au joueur suivant
                current_player = game.next_player(current_player);
            }
        } else {
            // Si l'utilisateur entre une action non reconnue
            printf("Action non reconnue. Entrez P pour placer, D pour déplacer.\n");
            continue;
        }

        // Vérifier s'il y a un gagnant
        Player winner = game.get_winner();

        if (winner != Player::NO_PLAYER) {
            // Afficher le plateau une dernière fois et annoncer le gagnant
            game.display();
            printf("Le joueur %c a gagné !\n", winner == Player::PLAYER_1 ? 'X' : 'O');
            break;
        }


    }

    return 0;
}
