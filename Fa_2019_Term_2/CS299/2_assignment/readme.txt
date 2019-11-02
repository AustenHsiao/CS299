 _______________________________________________________________                                   
/                                                               \
/This program is written by Austen Hsiao for CS299 assignment 2 \
/_______________________________________________________________\


I wrote the program as if in terms of buying a new car, apparent in some of the variable/object names.
There are 3 main components to this program-- attribute, available, and reject.

Attribute is supposed to be implemented as an absolute ordered list, but the structure
under the hood is a linear linked list in which each node captures a desirable 
feature and the priority level as dictated by the user.

Available is implemented as a circular linked list queue. This class holds the available
products (be it cars, houses, etc.) and their features. The program as a whole compares
the features of each product to the desirable attributes the user enters.

Reject is implemented as a linear linked list of dynamically allocated arrays. What this
ends up being is a bunch of nodes that contain a double pointer. There are 4 functions available
to the user, push, pop, peek, and display. 'push' function is the only one that requires an
argument.

Issues: The largest issue with this program is that each product can only hold 3 attributes.
I was originally going to have a double-pointer to hold the attributes for each product 
so that the number of attributes would be flexible, but this ended up taking too much 
time to implement and I decided it wasn't worth doing... but if I did it, the user would specify
the number of attributes associated with the given product, then each character array (string)
would be converted to a dynamically allocated array, then the pointer would be stored 
in the double-pointer that is allocated just enough memory to hold the number of attributes.


 
