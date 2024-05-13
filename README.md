
This is Assignment 1 of COMP 348, written by Afra Azreen (Student ID: 40234047)

This program is a movie recommendation system, with each part of the code responsible for management of different functionalities. 

The method MenuSwitch() is responsible for holding a switch statement which handles all these cases. 

Case One: User Registration
Here, the users can be registered into the system. This case checks the database to see if the username already exists, and if so a respective message is displayed. This case makes a call to the method: updateUserCount() which is responsible for updating the user count and ensuring that the user ID and username is linked together, so that the user is later able to use the other functions of the program. 


Case Two: 
This case is just responsible for printing all the movies from the file we were provided. It makes use of a method called printMovies() to do so.


Case Three:
This case is responsible for ratings and processing them. It makes use of a method called ratingProcessing() to do so efficiently. 

Case 4:
This allows us to recommend movies and shows those which have yet to be rated by the user, to do so, it uses the methods getMovData() and also arrayFull() if needed. 

Case 0: 
This allows the program to be exited successfully. 