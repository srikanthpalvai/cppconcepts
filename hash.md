# Hashing in Data Structures

## 1️⃣ **Hashing Basics**
Hashing is a process of converting data into a fixed-size numerical value (hash code) using a mathematical function called a hash function. The hash value represents the index at which data can be stored in a hash table.

### **Hash Function**
A **hash function** takes an input (or key) and produces an index in a hash table where the corresponding value is stored. 

#### Types of Hash Functions:
1. **Division Method**: 
   - `index = key % table_size;`
   - This method works by dividing the key by the table size and using the remainder as the index.
   
2. **Multiplication Method**: 
   - `index = floor(table_size * (key * A % 1));`
   - This method uses the fractional part of multiplying the key by a constant `A` and multiplies by the table size.
   
3. **Mid Square Method**:
   - `index = (key * key) % table_size;`
   - Square the key and use the last digits (mod table size) to determine the index.
   
4. **Folding Method**: 
   - Divides the key into equal parts and adds them together to generate the index.

## 2️⃣ **Handling Hash Collisions**

A **hash collision** occurs when two different keys produce the same hash value. There are two common techniques to handle hash collisions:

### **Separate Chaining (Linked List in a Bucket)**
🔹 **Concept**: Each bucket (array index) stores a linked list of items that have the same hash value (collision).

🔹 **When Used**: When multiple keys hash to the same index.

#### Example:
Let’s say we have a hash table of size = 5 and use the hash function:

```cpp
index = hash(key) % table_size;

We insert these values:

"apple" -> hash % 5 = 2
"banana" -> hash % 5 = 4
"grape" -> hash % 5 = 2 (collision with "apple")
"melon" -> hash % 5 = 1
"peach" -> hash % 5 = 4 (collision with "banana")

Index   Bucket (Linked List)
----------------------------
0       NULL
1       ["melon"]  
2       ["apple"] -> ["grape"]  
3       NULL
4       ["banana"] -> ["peach"]  

🔹 What happens during retrieval?

To find "grape", go to bucket 2, then traverse the linked list.

🔹 Advantages:

No need to resize immediately.
Handles collisions efficiently.
🔹 Disadvantages:

Extra memory (linked list storage).
Worst case: If all elements hash to the same bucket, search time becomes O(n).
Open Addressing (Probing for Empty Slots)
🔹 Concept: Instead of a linked list, we store values directly in the hash table and find empty slots if a collision occurs.

🔹 When Used: When the table itself stores values, avoiding extra memory for pointers.

Types of Open Addressing:
Linear Probing:
If the target index is occupied, try the next available slot (i.e., index + 1, index + 2, ...).
Quadratic Probing:
Instead of checking index + 1, it checks index + 1², index + 2², index + 3²...
Helps reduce clustering.
Example:
We insert values into a hash table of size = 5 and use:

index = hash(key) % table_size;
We insert:

"apple" -> hash % 5 = 2
"banana" -> hash % 5 = 4
"grape" -> hash % 5 = 2 (collision with "apple")
"melon" -> hash % 5 = 1
"peach" -> hash % 5 = 4 (collision with "banana")
Using Linear Probing, we resolve collisions by checking the next available slot.

Visual Representation (Open Addressing - Linear Probing)
Index   Value
----------------
0       NULL
1       "melon"
2       "apple"
3       "grape"  <- Collision solved by shifting to next slot!
4       "banana"
5       "peach"  <- Collision solved by shifting!

🔹 What happens during retrieval?

To find "grape", start at index 2 (original hash). If it’s occupied by "apple", we probe index 3.

🔹 Advantages:

No extra memory for linked lists.
Works well with low load factor (< 70%).
🔹 Disadvantages:

More rehashing needed as the table fills up.
Primary Clustering: If many elements are inserted close together, performance degrades.
Comparison Table
Method	How It Works	Pros	Cons
Separate Chaining	Uses a linked list at each index for collisions	Handles high load factors well	Extra memory for pointers
Open Addressing	Stores items in the table, probes for empty slots	No extra memory needed	Slower if table gets full
