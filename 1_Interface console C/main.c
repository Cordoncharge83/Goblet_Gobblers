#include <stdio.h>
#include "board.h"

void display_board(board game) {
    // Afficher le plateau de jeu en utilisant les fonctions get_place_holder et get_piece_size
    for (int i = 0; i < DIMENSIONS; i++) {
        for (int j = 0; j < DIMENSIONS; j++) {
            player holder = get_place_holder(game, i, j);
            size piece_size = get_piece_size(game, i, j);

            if (holder == NO_PLAYER) {
                printf(" - ");
            } else {
                // Utilisez des caractères spécifiques pour représenter les joueurs et les tailles de pièces
                printf(" %c ", holder == PLAYER_1 ? 'X' : 'O');
            }

            // Affichez la taille de la pièce si elle est visible
            if (piece_size != NONE) {
                printf("(%c) ", piece_size == SMALL ? 'S' : (piece_size == MEDIUM ? 'M' : 'L'));
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Initialiser le jeu
    board game = new_game();
    player current_player = PLAYER_1;

    // Boucle de jeu
    while (1) {
        // Afficher le plateau de jeu
        display_board(game);

        // Demander à l'utilisateur de choisir une action (placement ou déplacement)
        printf("Joueur %c, choisissez une action (P pour placer, D pour déplacer): ", current_player == PLAYER_1 ? 'X' : 'O');
        char action;
        scanf(" %c", &action);

        if (action == 'P' || action == 'p') {
            // Si l'utilisateur choisit de placer une pièce
            // Demander les coordonnées et la taille de la pièce
            int line, column;
            size piece_size;

            printf("Entrez la ligne (0-2) : ");
            scanf("%d", &line);

            printf("Entrez la colonne (0-2) : ");
            scanf("%d", &column);

            printf("Entrez la taille de la pièce (S, M, L) : ");
            char size_input;
            scanf(" %c", &size_input);

            // Convertir la taille de la pièce en énumération
            if (size_input == 'S' || size_input == 's') {
                piece_size = SMALL;
            } else if (size_input == 'M' || size_input == 'm') {
                piece_size = MEDIUM;
            } else if (size_input == 'L' || size_input == 'l') {
                piece_size = LARGE;
            } else {
                printf("Taille de pièce non valide.\n");
                continue;
            }

            // Placer la pièce sur le plateau de jeu
            int result = place_piece(game, current_player, piece_size, line, column);

            if (result != 0) {
                // Afficher un message d'erreur en fonction du résultat
                printf("Placement de la pièce échoué. Code d'erreur : %d\n", result);
            }
            else {
                // Passer au joueur suivant
                current_player = next_player(current_player);
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
            int result = move_piece(game, source_line, source_column, target_line, target_column);

            if (result != 0) {
                // Afficher un message d'erreur en fonction du résultat
                printf("Déplacement de la pièce échoué. Code d'erreur : %d\n", result);
            }
            else {
                // Passer au joueur suivant
                current_player = next_player(current_player);
            }
        } else {
            // Si l'utilisateur entre une action non reconnue
            printf("Action non reconnue. Entrez P pour placer, D pour déplacer.\n");
            continue;
        }

        // Vérifier s'il y a un gagnant
        player winner = get_winner(game);

        if (winner != NO_PLAYER) {
            // Afficher le plateau une dernière fois et annoncer le gagnant
            display_board(game);
            printf("Le joueur %c a gagné !\n", winner == PLAYER_1 ? 'X' : 'O');
            break;
        }


    }

    // Libérer la mémoire du jeu
    destroy_game(game);

    return 0;
}

