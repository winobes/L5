Here I will keep a list of the conventions that I'm loosing so that I don't 
loose track. Generally I'll follow the linux kernel style with som exceptions.

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
* When declaring a pointer, the `*` is part of the type (I.e. NOT `Point 
  *vertices`).

# Spacing #

- Two empty lines between functions
- One empty line after function declaration and before the final brace
- Inside functions, one empty line can be inserted between blocks of code for 
  readability.
- Tabs are four spaces


# Headers #

- ever .c file should have a header file excetp for main.c
- header declare only functions and macros that they need to export


- 
