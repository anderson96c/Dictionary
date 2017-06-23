## DICTIONARY ##

### What is it? ###

This program implements a DE of a Dictionary and its functions.

The elements are storeds as Nodes with a key(id) and a data(info).

	DAL : Unordered Dictionary, with linear search.

	Heritage from DAL:

	DSAL : Sorted Dictionary, with binary search.

### Functions ###

This functions are in the DAL and the DSAL class, and has the same returns and parameters in both of then.

`insert()`      : inserts an element with a key and an data in the Dictionary.
`remove()`      : removes an element associated to a key and recover the data from this element.
`max()`         : returns the biggest key in the Dictionary.
`min()`         : returns the smallest key in the Dictionary.
`predecessor()` : returns if the key given as a parameter has a predecessor and recover this predecessor. 
`sucessor()`    : returns if the key given as a parameter has a sucessor and recover this sucessor.

`search()[only avaliable on DAL class]` : returns if there's an element associated to the given key and recover its data

### Compiling ###

Compile the program using the code:

`make`

### Running ###

To run the program use the following code:

`./bin/dal'`

This program was made by ANDERSON CAIO.