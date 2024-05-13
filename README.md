# Movie Recommendation System
This program is a movie recommendation system, with each part of the code responsible for management of different functionalities. 

## Functionalities

### MenuSwitch()
The method MenuSwitch() is responsible for holding a switch statement which handles all these cases. 

### Case One: User Registration
Request a user to provide a name for registration within the application. It is assumed that only the first name is required. The application is required to keep track of all
the registered users in a text file named "user_data.txt" and should verify whether a user with the entered name already exists. If so, then a respective message is displayed. This case makes a call to the method: updateUserCount() which is responsible for updating the user count and ensuring that the user ID and username is linked together, so that the user is later able to use the other functions of the program. Note that the search is case insensitive, thus cases "Afra", "afRa" and "aFrA" are all equivalent. Upon a successful registration, the application should display the message "User is successfully registered" followed by the main menu.


### Case Two: Printing Movies List
This case is just responsible for printing all the movies from the input file, “movie_database.txt". It makes use of a method called printMovies() to do so, and displays them in an indexed manner.


### Case Three: Ratings
This case is responsible for ratings and processing them. It makes use of a method called ratingProcessing() to do so efficiently. Request the user to input a username. If the provided username is not found in the user database, the application should display the message "User not found. Please register first." Subsequently, the main menu must be presented again. In the event that the entered username exists, the application should exhibit a list of all movies from the database. Next, the user is prompted to input a movie index number to provide a rating. It is assumed that the user will enter a number; nonetheless, the program must validate the number to ensure it falls within the specified range. For example, if there are ten movies, any numbers outside the range of 1-10 must then be considered invalid. The rating information is preserved in an m x n matrix, where 'm' represents number of movies and 'n' represents number of users. The updated matrix is stored in a text file named "user_ratings.txt."

### Case 4: Recommend Movies
This allows us to recommend movies and shows those which have yet to be rated by the user, to do so, it uses the methods getMovData() and also arrayFull() if needed. 

#### Recommendation Algorithm

##### Filtering Rated Movies
Exclude movies that target user has already rated, as these movies are assumed to have been seen. 

##### Average Rating Computation
For each unseen movie, calculate the predicted rating by averaging ratings given by all other users who have rated that movie. 

##### Prediction Formula
I utilized a formula, whereby we take the sum of the ratings of the movies of a specific user (where they have yet to rate the movie), and then we divide it by the number of users who have watched the movie. This algorithm leverages the collective wisdom of other users to predict how much the target user might like unseen movies. The exclusion of movies already rated by the user ensures that the recommendations are personalized and aligned with the user's unique preferences. 

### Case 0: Exit
This allows the program to be exited successfully, ensuring resources are deallocated efficiently. 
