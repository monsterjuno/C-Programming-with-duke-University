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
  /*printf(" ");*/
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

void add_card_to(deck_t * deck, card_t c){
  deck->n_cards++;
  deck->cards = realloc(deck->cards,(deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = NULL;
  deck->cards[deck->n_cards-1] = realloc(deck->cards[deck->n_cards-1], sizeof(*(deck->cards[deck->n_cards-1])));
  deck->cards[deck->n_cards-1]->suit = c.suit;
  deck->cards[deck->n_cards-1]->value = c.value;
}

card_t * add_empty_card(deck_t * deck){
  card_t * temp = malloc(sizeof(*temp));
  temp->suit = 0;
  temp->value = 0;
  deck->n_cards++;
  deck->cards = realloc(deck->cards, (deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = temp;
  return temp;
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  card_t temp;
  deck_t * res = malloc(sizeof(*res));
  res->n_cards = 0;
  res->cards = NULL;

  int cond = 0;
  for(unsigned i=0; i<52; i++){
    temp = card_from_num(i);
    cond = deck_contains(excluded_cards, temp);
    if(cond==0){
      add_card_to(res, temp);
    }
  }
  return res;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t * temp;
  deck_t * no_ret_d = malloc(sizeof(*no_ret_d));
  deck_t * ret_d;
  no_ret_d->n_cards = 0;
  no_ret_d->cards = NULL;
  card_t * temp_c;
  for(size_t i=0; i<n_hands; i++){
    temp = hands[i];
    for(size_t j=0; j<temp->n_cards; j++){
      temp_c = temp->cards[j];
      if(temp_c->value != 0){
	if(deck_contains(no_ret_d, *temp_c)==0){
	  add_card_to(no_ret_d, *temp_c);
	}
      }
    }
  }
  ret_d = make_deck_exclude(no_ret_d);
  free_deck(no_ret_d);
  return ret_d;
}

void free_deck(deck_t * deck){
  for(size_t i=0; i<deck->n_cards; i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}

