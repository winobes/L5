# TODOs #

* mechanics
  * symmetric collision response for ship/ship collisions (use mass?)
  * player weapons
  * health and damage 
* graphics
  * backgrounds
  * parallax scrolling for backgrounds
  * drawing ship sprites & animations
  * support for full-screen
* features/long-term
  * load ship templates from XML or something instead of hard-coding
  * AI
  * multiplayer
  * UI for settings, etc.

# Code Style #

An incomplete summary of conventions. We mostly follow the linux kernel style.

## Naming ##
* Functions have `lower_case_names`.
* Local variables have `short` lower case names (this especially applies
  to variables whose are important in the function i.e., return values and 
  passed arguments), 
* Local variables may also have `descriptive_longer_names` when they aren't used
  very much and would otherwise require a comment.
* Enums and macros have `ALL_UPPER_CASE` names.
* Typedefs have `Capital_Names`.
* Struct members have `lower_case` names.
* Except for Allegro's structs which are in `ALL_UPPER_CASE`.
* The arrays have plural names. (E.g., `Point* vertices`)
* Functions allocating memory (e.g. with `malloc`) start with `create_`
  and should have a corresponding `destroy_` function wich calls `free`.

## Whitespace ##
- Two empty lines between functions
- One empty line after function declaration and before the final brace
- Inside functions, one empty line may be inserted between blocks of code for 
  readability.
- Tabs are four spaces

## Headers ##
- every `.c` file should have a header file except for `main.c`
- the header should contain prototypes and structs that need to be exposed,
  but not ones that are only used internally.


- 
