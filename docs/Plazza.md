### Enum

The value of the pizza are defined by 3 enum.
The first one define the type of pizza.
The second one define the size of the pizza.
The third one define the ingredient of the pizza as a bitfield.
```c++
enum PizzaType
{
  Regina    = 1,
  Margarita = 2,
  Americana = 3,
  Fantasia  = 4
};

enum PizzaSize
{
  S   = 1,
  M   = 2,
  L   = 3,
  XL  = 4,
  XXL = 5
};

enum Ingredient
{
  DOUGH       = 0b000000001,
  TOMATO      = 0b000000010,
  GRUYERE     = 0b000000100,
  HAM         = 0b000001000,
  MUSHROOMS   = 0b000010000,
  STEAK       = 0b000100000,
  EGGPLANT    = 0b001000000,
  GOAT_CHEESE = 0b010000000,
  CHIEF_LOVE  = 0b100000000
};
```

### struct

The pizza is defined by a struct with 2 enum.
```c++
struct Pizza
{
  PizzaType type;
  PizzaSize size;
};
```

### const

The string value of the enum are define by a map.
The recipe of the pizza are define by a map.
```c++
const std::map<PizzaType, std::string> pizzaTypeToString = {
  {PizzaType::Regina,    "regina"},
  {PizzaType::Margarita, "margarita"},
  {PizzaType::Americana, "americana"},
  {PizzaType::Fantasia,  "fantasia"}
};

const std::map<PizzaSize, std::string> pizzaSizeToString = {
  {PizzaSize::S,   "S"},
  {PizzaSize::M,   "M"},
  {PizzaSize::L,   "L"},
  {PizzaSize::XL,  "XL"},
  {PizzaSize::XXL, "XXL"}
};

const std::map<Ingredient, std::string> ingredientToString = {
  {Ingredient::DOUGH,       "Dough"},
  {Ingredient::TOMATO,      "Tomato"},
  {Ingredient::GRUYERE,     "Gruyere"},
  {Ingredient::HAM,         "Ham"},
  {Ingredient::MUSHROOMS,   "Mushrooms"},
  {Ingredient::STEAK,       "Steak"},
  {Ingredient::EGGPLANT,    "Eggplant"},
  {Ingredient::GOAT_CHEESE, "Goat cheese"},
  {Ingredient::CHIEF_LOVE,  "Chief love"}
};

const std::map<PizzaType, uint8_t, ingredient> pizzaRecipe = {
  {PizzaType::Regina,    1, Ingredient::DOUGH | Ingredient::TOMATO | Ingredient::GRUYERE | Ingredient::HAM | Ingredient::MUSHROOMS},
  {PizzaType::Margarita, 2, Ingredient::DOUGH | Ingredient::TOMATO | Ingredient::GRUYERE},
  {PizzaType::Americana, 2, Ingredient::DOUGH | Ingredient::TOMATO | Ingredient::GRUYERE | Ingredient::HAM | Ingredient::EGGPLANT},
  {PizzaType::Fantasia,  4, Ingredient::DOUGH | Ingredient::TOMATO | Ingredient::GOAT_CHEESE | Ingredient::CHIEF_LOVE}
};
```

### Handle kitchen

Each kitchen add itself to a queue inside the receptionist.
The receptionist always send pizza to the first kitchen in the queue and remove it from the queue.
When the kitchen start to cook a pizza she add herself to the queue if she as another chief.
When the queue of kitchen is empty the receptionist create a new kitchen.

### CLI

#### At start

```bash
> ./plazza {COOKING_TIME} {NUMBER_OF_COOKS} {RESTOCK_TIME}
```

```bash
> ./plazza -h
Usage: ./plazza {COOKING_TIME} {NUMBER_OF_COOKS} {RESTOCK_TIME}
    {COOKING_TIME}    Time in ms to cook a pizza
    {NUMBER_OF_COOKS} Number of chief in the kitchen
    {RESTOCK_TIME}    Time in ms to restock the ingredient
```

#### At runtime

```bash
> help
Available commands:
    help: Display this help
    status: Display the status of the kitchen
    {PIZZA} {SIZE} {NUMBER} [; {PIZZA} {SIZE} {NUMBER} ...]*: Order a pizza
        {PIZZA}: Type of pizza
            regina
            margarita
            americana
            fantasia
        {SIZE}: Size of pizza
            S
            M
            L
            XL
            XXL
        {NUMBER}: Number of pizza to cook
            x[1-9][0-9]*
    exit: Exit the program
```

```bash

> status
Kitchen N
    N chief is cooking a pizza
    N chief is waiting for a pizza
    Ingredients
        {NAME} x{NUMBER}
        Next refill in {TIME} ms (at {TIME})
    Pizzas
        {TYPE} {SIZE} x{NUMBER} end in {TIME} ms (at {TIME})
 ```
