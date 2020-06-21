#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"

void print_hand(deck_t * hand){
  size_t i=0;
  print_card(*hand->cards[i++]);
  while(i<hand->n_cards){
    printf(" ");
    print_card(*hand->cards[i++]);
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(int i=0;i<d->n_cards;i++){
    if(c.value==d->cards[i]->value && c.suit==d->cards[i]->suit){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  size_t m=random()%6;
  for(size_t i=0;i<m;i++){
    size_t low=i*(d->n_cards / m);
    size_t high=(i+1)*(d->n_cards / m);
    for(size_t j=low;j<high;j++){
      card_t *temp=d->cards[j];
      size_t n=(random()*random()) % d->n_cards;
      d->cards[j]=d->cards[n];
      d->cards[n]=temp;
    }
  }
  /*Another Shuffle*/
  for(size_t j=0; j<d->n_cards; j++){
    card_t *temp=d->cards[j];
    size_t n=(random()*random()) % d->n_cards;
    d->cards[j]=d->cards[n];
    d->cards[n]=temp;
  }
}

void assert_full_deck(deck_t * d) {
  unsigned rep[52]={0};
  for(unsigned i=0;i<52;i++){
    if(deck_contains(d,card_from_num(i))){
      rep[i]++;
    }
  }
  for(unsigned i=0;i<52;i++){
    if(rep[i]>1){
      assert(rep[i]>1);
    }
  }
}

