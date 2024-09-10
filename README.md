# Dictionary implementation in C

A naive implementation of python's dynamic dictionaries using a custom implementation of the md5 hash

Keys and Values can only be strings and void pointers respectively 
cause im **NOT** implementing a dynamic typing system `lmao`

Aditionally, for safety reasons, keys are only garanteed uniqueness for the first 64 characters

To top if off, as if this implementation couldnt be more janky, the dictionary does NOT manage the memory of its values, 
meaning if a value it references to gets freed, the dictionary has not way to know it contains a dangling pointer

Mostly done for C practice 

# FEATURES
- [x] Basic I-O
- [x] Dynamic size
- [ ] Deletion of items
- [ ] Value memory management (god this does NOT happen in rust)
- [ ] Logical comparations between dicts (`dict1 == dict2`)