#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_WEIGHT 5
#define MAX_BAG 25


typedef struct {
  char   *name; // no limit on length of string
  float  weight;
  char   frozen;
  float  cost;
} GroceryItem;

typedef struct {
  GroceryItem **items; // pointer to array
  int total;
  float totalWeight;
} Bag;

typedef struct {
  GroceryItem **looseItems;// pointer to array
  Bag **cartBag; // pointer to array
  int numBags;
  int numItems;
} Cart;

int addToCart(GroceryItem *items, Cart *shoppingCart){
  // increase the number of items by 1 since we are adding an item to the cart
  shoppingCart->numItems+=1;
  // reallocating space since just allocating is not dynanmic
  shoppingCart->looseItems = (GroceryItem **) realloc(shoppingCart->looseItems, sizeof(GroceryItem)*shoppingCart->numItems);
  // checks to see if there are problems allocating memory
  if (shoppingCart == NULL) {
    printf("Memory allocation error\n");
    exit(-1);
  }
  // add the item to the last index of array inside cart
  shoppingCart->looseItems[shoppingCart->numItems-1] = items;
  if(shoppingCart->looseItems[shoppingCart->numItems-1]!= NULL){
      return 1;
  }
  return 0;
}

int addToBag(GroceryItem *items, Bag *bag){
  bag->total+=1; // add 1 to the total to increase bag size
  bag->items = realloc(bag->items, sizeof(GroceryItem)*bag->total); // realloc space for dynamic memory
  // memory error checking
  if (bag->items == NULL) {
    printf("Memory allocation error\n");
    exit(-1);
  }
  // add item to last index of array inside bag
  bag->items[bag->total-1] = items; // if this doesn't work do bag->[total-1]
  // returns 1 if adding the item was successful
  if(bag->items[bag->total-1]!= NULL){
      return 1;
  }
  // else return 0
  return 0;
}

int removeFromBag(GroceryItem *items, Bag *bag){
  Bag *tmp = bag;
  bag->items = realloc(bag->items, sizeof(GroceryItem)*bag->total); // realloc space
  if (bag->items == NULL) {
    printf("Memory allocation error\n");
    exit(-1);
  }

  bag->total-=1; // remove 1 from the total to decrease bag size
  return 1;
}
int removeFromCart(GroceryItem *items, Cart *shoppingCart){
  Cart *tmp = shoppingCart;
  shoppingCart->looseItems = realloc(shoppingCart->looseItems, sizeof(GroceryItem)*shoppingCart->numItems); // realloc space
  if (shoppingCart->looseItems == NULL) {
    printf("Memory allocation error\n");
    exit(-1);
  }

  shoppingCart->numItems-=1; // remove 1 from the total to decrease bag size
  return 1;
}

void displayItem(GroceryItem *items){
  printf("%s weighing %.3f kg with price $ %.2f\n", items->name, items->weight, items->cost);
}

void displayBag(Bag *bag, int bagNumber){
  // look for heaviest
  float heaviest =0;
  for(int i=0; i < bag->total;i++){
    // selection sort to find largest weight
    if (bag->items[i]->weight > heaviest){
      heaviest = bag->items[i]->weight;
    }
  }

  printf("Bag %d (Total Weight = %.3fkg)\n", bagNumber, bag->totalWeight);
  for(int i = 0; i < bag->total; i++){
    if (bag->items[i]->weight == heaviest){
      printf("*");
      displayItem(bag->items[i]);
    }
    else{
      displayItem(bag->items[i]);
    }
  }
  printf("\n" );
}

void displayCart(Cart *shoppingCart){
  for(int i = 0; i < shoppingCart->numItems; i++){
    displayItem(shoppingCart->looseItems[i]);
  }
  printf("\n" );
  for(int i = 0; i < shoppingCart->numBags; i++){
    displayBag(shoppingCart->cartBag[i], i);
    printf("\n" );
  }
}
void packBags(Cart *shoppingCart){
  int bagCount, bagNumber, itemNumber = 0; // initalise all ints to 0
  float weightLimit = 0;

  // loop through the items in the cart
  for(int i = 0; i < shoppingCart->numItems; i++){
    if(shoppingCart->looseItems[i]->weight < MAX_WEIGHT){
      weightLimit = weightLimit + shoppingCart->looseItems[i]->weight;
      if(weightLimit >= MAX_WEIGHT){
        weightLimit = shoppingCart->looseItems[i]->weight;
        // only add a bag once the weight reaches the max weight otherwise you have not full bags
        bagNumber+=1;
      }
    }
  }
  // allocate memory so we can reallocate memory later
  shoppingCart->cartBag = (Bag **)malloc(sizeof(Bag)*bagNumber);
  if(shoppingCart->cartBag == NULL){
    printf("Memory allocation error\n");
    exit(-1);
  }
  // make the carts number of bags to the number of bags needed
  shoppingCart->numBags = bagNumber;
  for(int i = 0; i < shoppingCart->numBags; i++){
    // allocate space, should be fine with just the size of bag, size we resize later
    shoppingCart->cartBag[i] = (Bag *)malloc(sizeof(Bag));
    // allocate space for groceryitems in the arrays reallocate later
    shoppingCart->cartBag[i]->items = (GroceryItem **)malloc(sizeof(GroceryItem));
    // initialise weight so that it can be used later
    shoppingCart->cartBag[i]->totalWeight = 0;
    // set the number of items in the bag in the cart to 0
    shoppingCart->cartBag[i]->total = 0;
  }
  for(int i = 0; i < shoppingCart->numItems; i++){
    if(itemNumber > MAX_ITEMS){
      // reset counters
      itemNumber = 0;
      bagNumber = 0;
    }
    addToBag(shoppingCart->looseItems[i], shoppingCart->cartBag[bagNumber]);
    // remove item from cart
  }
}

void removeFrozen(Cart *shoppingCart){

}


int main() {
  GroceryItem testItems[12];
  char *sampleItemNames[] = {"Smart-Ones Frozen Entrees",
  "SnackPack Pudding", "Breyers Chocolate Icecream",
  "Nabob Coffee", "Gold Seal Salmon", "Ocean Spray Cranberry Cocktail",
  "Heinz Beans Original", "Lean Ground Beef", "5-Alive Frozen Juice",
  "Coca-Cola 12-pack", "Toilet Paper - 48 pack", "Crate of milk"};
  float sampleItemPrices[] = {1.99, 0.99, 2.99, 3.99, 1.99, 2.99, 0.79, 4.94, 0.75, 3.49, 40.96, 12.99};
  float sampleItemWeights[] = {0.311, 0.396, 2.27, 0.326, 0.213, 2.26, 0.477, 0.75, 0.426, 5.112, 10.89f, 6.18f};
  float sampleItemPerish[] = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1};

  // *bag = (Bag *)malloc(sizeof(Bag));
  //
  // if (bag == NULL) {
  //   printf("Memory allocation error\n");
  //   exit(-1);
  // }
  Cart newShoppingCart;
  newShoppingCart.numItems = 0;
  newShoppingCart.numBags = 0;
  newShoppingCart.looseItems = (GroceryItem **)malloc(sizeof(GroceryItem));
  if (newShoppingCart.looseItems == NULL) {
    printf("Memory allocation error\n");
    exit(-1);
  }
  for(int i = 0; i < 12; i++){
    testItems[i].name = sampleItemNames[i];
    testItems[i].cost = sampleItemPrices[i];
    testItems[i].weight = sampleItemWeights[i];
    testItems[i].frozen = sampleItemPerish[i];
  }
  // add shopping cart with 50 random items
  for(int i = 0; i < 50; i++){
    // call the add item function
    addToCart(&testItems[rand() % 12],&newShoppingCart);
  }
  displayCart(&newShoppingCart);
  packBags(&newShoppingCart);
  displayCart(&newShoppingCart);

  free(newShoppingCart.looseItems);
  free(newShoppingCart.cartBag);
}
