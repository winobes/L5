Here is list of style conventions. 
Generally we follow the linux kernel style with some exceptions.

# Naming #

## Case ##
* Functions shall have `lower_case_names`.
* Local variables shall have `short` lower case names (this especially applies
  to variables whose are important in the function i.e., return values and 
  passed arguments), 
* Local variables may also have `descriptive_longer_names` if they aren't used
  very much and would otherwise require a comment.
* Enums and macros shall have `ALL_UPPER_CASE` names.
* Typedefs shall have `Capital_Names`.
* Struct members have `lower_case` names.
* Except for Allegro's structs which are in `ALL_UPPER_CASE`.

## Misc. ##
* The names of arrays shall be plural. (E.g., `Point* vertices`)
* Any function allocating memory (e.g. with malloc) should start with `create_`
  and should have a corresponding `destroy_` function.

# Spacing #
- Two empty lines between functions
- One empty line after function declaration and before the final brace
- Inside functions, one empty line may be inserted between blocks of code for 
  readability.
- Tabs are four spaces

# Headers #
- every .c file should have a header file except for main.c
- the header should declare only functions and macros that need to be exposed


- 
