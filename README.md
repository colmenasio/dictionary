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
  - [x] Memory upscaling
  - [ ] Memory donwscaling
- [x] Deletion of items
- [x] Dictionary destruction (propper memory freeing) (this does NOT happen in rust)
- [ ] Value memory management (man i really miss rust ;-;)
- [ ] Logical comparations between dicts (`dict1 == dict2`)


- [x] And if you call within the next 30 minutes, you get a janky-@$$ md5 implementation 
for free!!!1!11! `:D`