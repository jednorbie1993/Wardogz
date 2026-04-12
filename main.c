#include <stdio.h>

// Structure for Dog
struct Dog {
    char name[50];
    int hp;
    int attack;
    int speed;
};

int main() {
    struct Dog player;

    // Assign values
    printf("Enter your dog's name: ");
    scanf("%s", player.name);

    player.hp = 100;
    player.attack = 20;
    player.speed = 10;

    // Display stats
    printf("\n--- Your Dog ---\n");
    printf("Name: %s\n", player.name);
    printf("HP: %d\n", player.hp);
    printf("Attack: %d\n", player.attack);
    printf("Speed: %d\n", player.speed);

    return 0;
}