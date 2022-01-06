# Query-Database
Coming to UCLA was a big feat - I was suddenly meeting all these new people and I couldn't remember their favourite songs or favourite shows! Let's create a table that will hold information about these new friends I'm making. 

**Creating the Table**
The user can decide how many fields it wants to keep track of. We can store the field information inside of a vector string. In this case, we'll be storing it inside a vector called newfriends which will keep track of my friend's names, their favourite songs, current binge, grade and their energy level. Obviously, this table is representative of my friend count before school started...

<img width="950" alt="Screen Shot 2022-01-06 at 3 25 16 PM" src="https://user-images.githubusercontent.com/81529754/148446968-858f2468-fb71-4f18-8c96-0b82a6c61c1c.png">

When we create a Table object, we'll need to designate a keyColumn. The keyColumn is the column of information that we'll be using to search whether a record exists. 

# Functions 

**good**
This function makes sure that we aren't creating records with the same keyColumn information, an empty keyColumn record, or if the record exists. It's our initial screener that our Table was constructed properly.

**insert**
This function inserts a record into the Table if the record has the correct number of fields. I used a Hash Table to store each record and hashed into it using keyColumn's information. 

**find**
This function returns all the records whose key field is equal to the keyColumn value the user is searching for.  

**select**
This function is where the magic is at. The user can send in a query which specifies a condition that can hold or can't hold for a record and the function will return the records in the table that satisfy the query. For example, I could get a list of people that have last names that don't start with A or people that have energy levels less than 10. 
