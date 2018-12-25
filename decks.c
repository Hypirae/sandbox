#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>

typedef enum suit_e {
    HEART,
    DIAMOND,
    CLUB,
    SPADE
} suit_e;

typedef enum value_e {
    HEAD,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} value_e;

typedef struct card_t {
    struct card_t   *prev;
    struct card_t   *next;
    suit_e          suit;
    value_e         value;
} card_t;

typedef struct decks_t {
    card_t  *stock;
    card_t  *firstPlayer;
    card_t  *secondPlayer;
    card_t  *thirdPlayer;
    card_t  *fourthPlayer;
    card_t  *gamePile;
    card_t  *discardPile;
} decks_t;

card_t * createCard (suit_e suit, value_e value) {
    card_t *card = malloc(sizeof(card_t));

    card->prev  = NULL;
    card->next  = NULL;
    card->suit  = suit;
    card->value = value;

    return card;
}

card_t * findLast (card_t *deck) {
    card_t *curr = deck;
    
    while (curr->next) {
        curr = curr->next;
    }
    
    return curr;
}

decks_t * createDecks () {
    decks_t *decks = malloc(sizeof(decks_t));

    decks->stock        = createCard(HEART, HEAD);
    decks->firstPlayer  = createCard(HEART, HEAD);
    decks->secondPlayer = createCard(HEART, HEAD);
    decks->thirdPlayer  = createCard(HEART, HEAD);
    decks->fourthPlayer = createCard(HEART, HEAD);
    decks->gamePile     = createCard(HEART, HEAD);
    decks->discardPile  = createCard(HEART, HEAD);

    return decks;
}

/*void destroyDecks (decks_t *decks) {
    card_t *curr;
    int i = 0;

    while (i < 7) {
        switch (i) {
            case 0: curr = decks->stock;
            case 1: curr = decks->firstPlayer;
            case 2: curr = decks->secondPlayer;
            case 3: curr = decks->thirdPlayer;
            case 4: curr = decks->fourthPlayer;
            case 5: curr = decks->gamePile;
            case 6: curr = decks->discardPile;
        }

        while (curr->prev) {
            curr = curr->prev;
            free(curr->next);
        }

        free(curr);

        i++;
    }

    free(decks);
}*/

card_t * addCard (card_t *dest, card_t *card) {
    card_t *last = findLast(dest);

    last->next = card;
    card->prev = last;

    return dest;
}

card_t * moveCard (card_t *dest, card_t *src) {
    card_t *srcLast     = findLast(src);
    card_t *destLast    = findLast(dest);

    // remove card from src
    srcLast->prev->next = NULL;

    // add card to dest
    destLast->next  = srcLast;
    srcLast->prev   = destLast;

    return dest;
}

decks_t * populateStock (decks_t *decks) {
    card_t *curr = findLast(decks->stock);
    card_t *new; 
    int suit, value;

    suit    = 0;
    value   = 1;

    while (suit < 4) {   
        while (value < 15) {
            new = createCard(suit, value);
            addCard(decks->stock, new);
            curr = curr->next;
            value++;
        }

        value = 1;
        suit++;
    }

    return decks;
}

void printDeck (card_t *deck) {
    card_t *curr = deck;

    while (1) {
        if (curr->value != HEAD) {
            printf("Suit: %d, Value: %d\n", curr->suit, curr->value);            
        }

        if (!curr->next) {
            break;
        }

        curr = curr->next;
    }
}

int main () {
    decks_t *decks = createDecks();
    
    decks = populateStock(decks);

    moveCard(decks->firstPlayer, decks->stock);
    printDeck(decks->firstPlayer);
    //destroyDecks(decks);
    return 0;
}