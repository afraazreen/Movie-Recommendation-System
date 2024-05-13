// Movie Recommendation System 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Removing underscore from title
void removeFromTitle(char *mName) {
    int length = strlen(mName);
 for (int i=0; i < length; i++) {
            if (mName[i] == '_') 
            {
                mName[i] = ' ';

            }

        }
}

// This method processes ratings and/or handles them. (case 3)
void ratingProcessing(int movieIndex, int userID, int newRating) {
    FILE *rateFile;
    int users;
    int movies;
    float **uRatings;

    rateFile = fopen("user_ratings.txt", "r");

    if (rateFile == NULL) {
        printf("Error. File could not be opened.");
        exit(1);
    }

    // This reads through the values in the files. 
    fscanf(rateFile, "%d %d", &users, &movies); 

    // Now, we dynamically allocate space for the userRatings array (similar to what was done in the previous method.)
    uRatings = (float**) malloc(users*sizeof(float*));

    if (uRatings == NULL) {
        printf("Error. Memory was unable to be allocated. \n");
        return;
    }

    for (int i=0; i < users; i++) {
        uRatings[i] = (float*) malloc(users*sizeof(float*));

        if (uRatings[i] == NULL) {
            printf("Error. Memory was unable to be allocated.");
            return;
        }


    }

    for (int i = 1; i < users; i++) {
        for (int j = 0; j < movies; j++) {
            fscanf(rateFile, "%f", &uRatings[i][j]);
        }
    }

    fclose(rateFile);

    rateFile = fopen("user_ratings.txt", "w");

    if (rateFile == NULL) {
        printf("Error. File could not be opened.");
        exit(1);
    }

    // Modify only the specific rating within the array. 
    uRatings[userID - 1][movieIndex -1] = newRating;

    // Then, we write these back into the file. 
    fprintf(rateFile, "%d %d\n", users, movies);

    for(int i=0; i < users; i++) {
        for (int j=0; j < movies; j++){
            fprintf(rateFile, "%.1f", uRatings[i][j]);
        } 

        fprintf(rateFile, "\n");
    }

    fclose(rateFile);

    // Then, we will free the allocated memory:
    for(int i=0; i < userID; i++) {
        free(uRatings[i]);
    }

  







}

// This method prints the movies (case 2)
int printMovies() {
 FILE *file2;
    char line2[256];
    char movie[150];
    char genre[100];
    float rating;
    int index = 1;

    file2 = fopen("movie_database.txt", "r");

    if(file2 == NULL){
        printf("Error. File could not be opened\n");
        exit(1);
    }

    printf("***** Movie Database *****\n");

    // This while loop reads through the file line by line, and identifies the title, genre and rating of the movie. 
    while (fgets(line2, sizeof(line2), file2)) {


        sscanf(line2, "%s %s %f", movie, genre, &rating);

        // This loop removes all underscores from the movie title
        removeFromTitle(movie);
       

        // The format specifier ensures that only one digit is displayed. 
        printf("%d. %s (%s) - %.1lf\n", index, movie, genre, rating);
        index++;





    }

    fclose(file2);
    return index; 

}

// This method updates the user count. (case 1)
void updateUserCount (int newUsers) {

    // This is a pointer which points to the ratings file. 
    FILE *ratingsFile;

    // Creating a variable to represent the movies and the users.
    int users, movies;

    // Creating a double pointer variable to help me create the 2D array. 
    float **ratingsArray;

    // Opening the file to read it. 
    ratingsFile = fopen("user_ratings.txt", "r");

    // If the file could not be opened. 
    if (ratingsFile == NULL) {
       printf("Error. File could not be opened.");
        exit(1);


    }

    // Then, I am scanning the contents of the file, and storing them in the variables I have created earlier.
    fscanf(ratingsFile, "%d %d", &users, &movies);


    // Then, I am using malloc to create the 2D dynamically allocated array.
    // This is stored in the double pointer I created earlier.
    ratingsArray = (float**) malloc((users+1)*sizeof(float*));

    // If the pointer is set to null, then the memory is unable to be allocated.
    if (ratingsArray == NULL) {
       printf("Error. Memory was unable to be allocated. \n");
    }


    // Using the for loop, I am now creating the second part of the 2D array:
    for (int i = 0; i < (users+1); i++) {

        // I am again using malloc to do this.
        ratingsArray[i] = (float*) malloc(movies*sizeof(float));

        // Error Handling
        if (ratingsArray[i] == NULL){
            printf("Error. Memory was unable to be allocated. \n");
            return;
        }
    }


    // This loop reads and stores the existing ratings. 
    // The loop begins at 1 rather than 0 as the first element contains data which tells us about the number of users created and the movies. 
    // Hence, we skip that line and read starting the next line. 
    // The loop iterates over the movies for each user. 

    for (int i = 1; i < users; i++) {
        for (int j = 0; j < movies; j++){
            fscanf(ratingsFile, "%f", &ratingsArray[i][j]);
        }
    }


    // This part of the code initalizes the ratings for the new user to 0 for all movies in the array.
    for(int j = 0; j < movies; j++){
        ratingsArray[users][j] = 0.0;
    }

    // We then close the ratingsFile.
    fclose(ratingsFile);

    // We now reopen, but in write mode.
    ratingsFile = fopen("user_ratings.txt", "w");

    // If the file cannot be opened. 
    if (ratingsFile == NULL) {
     printf("Error. File could not be opened.");

    }

    // We update the header, with the new information regarding how many users and movies are present.
    fprintf(ratingsFile, "%d %d\n", newUsers, movies);

    // Here, we have the loop to now print the new data out into the file. 
    for (int i = 0; i< users+1; i++){
        for (int j=0; j < movies; j++) {
            fprintf(ratingsFile, "%.1f", ratingsArray[i][j]);
        }
        fprintf(ratingsFile, "\n");
    }

    // Closing the file.
    fclose(ratingsFile);

    // Free allocated memory
    for(int i =0; i < newUsers; i++){
        free(ratingsArray[i]);

    }
    free(ratingsArray);


    

}

// This handles the recommendations
int recommendationHandling(int userIDrec, float ratingscores[]) {
    // First, we are going to open the file and read through it:
    FILE *rFile;
    __ssize_t readrating;
    char* ratingLine;
    size_t ratinglength = 0;

    if ((rFile = fopen("user_ratings.txt", "r")) != NULL) {

    // Stores the num of users and movies. 
    int users4;
    int moviesNum;
   
    // This reads through the values in the files. 
    fscanf(rFile, "%d %d", &users4, &moviesNum); 

    // Create arrays to store this data:
    float cumulativeMScore[moviesNum];
    int movieRater[users4];
    int valid_recommendations[users4];

    // Now, we are going to make sure that these arrays, although statically set, are set to 0. 
    // Essentially, we are setting every element in these arrays to 0. 
    memset(cumulativeMScore, 0, sizeof(cumulativeMScore));
    memset(movieRater, 0, sizeof(movieRater));
    memset(valid_recommendations, 0, sizeof(valid_recommendations));

    // Now, we will create a pointer which will be used to store tokens.
    char *tokens = NULL; // Initalized to null

    // Declares a variable which will store the value of each token representing a rating.
    float currentRatings;

    // This loop is responsible for:
    // reading each line of ratings from the file, removes the newline character from the end of the line, 
    // then tokenizes the line to extract individual ratings
    // This loop continues for all the users until userIDrec.

    for (int i = 1; i < userIDrec; i++) {
    readrating = getline(&ratingLine, &ratinglength, rFile);

    // It identifies wherever the newline char is and replaces it with a O.
    ratingLine[strcspn(ratingLine, "\n")] = 0;

    // tokenizes aka breaks the string down based on the " ". 
    tokens = strtok(ratingLine, " ");

    // Only ratings above 0.0  are considered
            for(int j = 0; j < moviesNum; j++) {

                // This converts the tokens to float. 
                currentRatings = atof(tokens);

                // movieRater represents the cumulative sum of how many people have rated this movie. 
                if (currentRatings != 0.0) {

                    cumulativeMScore[j] += currentRatings;
                    movieRater[j] += 1;
                }

                // This retrieves the next part of the string.
                tokens = strtok(NULL, " ");
            }

}

// This is for a specified user at specified lines.
// this code reads a line of ratings from a file, removes the newline character from the end of the line, 
// then tokenizes the line to extract individual ratings
readrating = getline(&ratingLine, &ratinglength, rFile);

// Replaces the newline with a zero after identifying it's index
ratingLine[strcspn(ratingLine, "\n")] = 0;
tokens = strtok(ratingLine, " ");


// this loop iterates over the ratings of a user for each movie. 
// If a movie has not been rated by the user, 
// it marks it as a valid recommendation by setting the corresponding element in the valid_recommendations array to 1
        for(int i = 0; i < moviesNum; i++) {

            currentRatings = atof(tokens);

            if (currentRatings == 0.0) {
                valid_recommendations[i] = 1;
            }
            tokens = strtok(NULL, " ");
        }


    // Return to adding up the rest of the scores
    // this code reads each line of ratings from the file
    // removes the newline character from the end of the line
    // tokenizes the line to extract individual ratings
    // and processes the ratings to accumulate movie scores and count the number of raters for each movie. 
       
        while ((readrating = getline(&ratingLine, &ratinglength, rFile)) != -1) {
            readrating = getline(&ratingLine, &ratinglength, rFile);
            ratingLine[strcspn(ratingLine, "\n")] = 0;
            tokens = strtok(ratingLine, " ");
            for(int i = 0; i < moviesNum; i++) {

                currentRatings = atof(tokens);

                if (currentRatings != 0.0) {
                    cumulativeMScore[i] += currentRatings;
                    movieRater[i] += 1;
                }
                tokens = strtok(NULL, " ");
            }
        }

    // The average score by other users which rated it is then stored in the array that was intially passed into the method. 
    // valid_recommendations array makes sure that only unwatched movies are there. 
        for(int i = 0; i < moviesNum; i++) {

            ratingscores[i] = cumulativeMScore[i]/movieRater[i] *valid_recommendations[i];
        }

    }

    else {
        printf("Error. File could not be opened.");
        return 0;
    }

    fclose(rFile);
    return 1;

}

// This method prints the movies. (menu)
void printMenu() {


    printf("***** Movie Recommendation System *****\n");
	printf("1. Register User\n");
	printf("2. Display Movies\n");
	printf("3. Rate a Movie\n");
	printf("4. Get Movie Recommendations\n");
	printf("0. Exit\n");
    printf("Enter your choice: ");




}

// Method to check if recommendation array is full (case 4)
int arrayFull(int *num) {
    for (int i=0; i < 10; i++) {
        if (num[i]==1) {
            return 1;
        }
        return 0;

    }
}

// This method specifically retrieves the data concerning the movies.
// Here, pos refers to the movie position that needs to be returned. 
// nameM and category are pointers and they work with where the name or category should go. 
int getmovData(int pos, char *nameM, char *category) {

    // Creating the different components which will allow me to read through and extract the data in the files. 
    FILE *newfp;

    // An array which will store the info line by line. 
    char* mLine = NULL;
    
    // Stores the length. 
    size_t mlength = 0;

    // This will allow us to read the movies. 
    __ssize_t readM;

    // Opening the file. 
    newfp = fopen("movie_database.txt", "r");

    // Array to store the name. 
    char *movieName4 = NULL;

    readM = getline(&mLine, &mlength, newfp);

    // For each position skip those lines. 
    // Essentially skips positions based on those lines. 
    for (int i = 0; i < pos; i++)
        readM = getline(&mLine, &mlength, newfp);
    
    
    // Remove the break and tokenize by using the space. 
    // Extracts the movie name and category. 
    mLine[strcspn(mLine, "\n")] = 0;
    movieName4 = strtok(mLine, " ");

   // Replace the underscores with spaces by calling removeFromTitle()
   removeFromTitle(movieName4);

    // Then, we copy the movie name and the category into specific locations. 
    // Essentially, it copies the data into the respective buffers. 
    strcpy(nameM, movieName4);
    strcpy(category, strtok(NULL, " "));

    // Close the file. 
    fclose(newfp);

    // Returns one to show that everything occured successfully. 
    return 1;
}

// This method handles the switch. 
void MenuSwitch(int choice) {

   switch (choice) {
    case 1:
        // This is a pointer to the user_data.txt file.
    FILE *userDataFile;
    
    // This stores the input.
    char uInput[100];

    // This will read each line of the file.
    char fileLine[256];

    // This will store the names already present in the file.
    char dataName [100];

    // This will store the id number of the user. 
    int idNum;

    // This is the variable which checks to see if the user has already been registered. 
    // It is initally set to O, and if the user has already been registered and their name has been found:
    // We will then set it to 1. 
    int registered = 0;


    // This prompts the user for the registration details. 
	printf("Enter username for registration: ");

	// This line ensures that it will only take a word of 50 chars.
	scanf("%50s", uInput);

    // This opens the file for reading. 
	userDataFile = fopen("user_data.txt", "r");

	// Here, I will check if the file was opened successfully. 
	if (userDataFile == NULL) {
	printf("Error. File could not be opened.\n");
	exit(1);
    }

    // This allows the file to continue being read until the end has been reached.
	while (fgets(fileLine, sizeof(fileLine), userDataFile)) {

        sscanf(fileLine, "%s %d", dataName, &idNum);

	    if (strcasecmp(dataName, uInput) == 0) {
	        registered = 1;
            printf("User already exists. Please choose a different name. \n");
	        break;
	    }
				
                
        }

        fclose(userDataFile);

        if (registered == 0) {
            idNum++;
            userDataFile = fopen("user_data.txt", "a");
            fprintf(userDataFile, "\n%s %d", uInput, idNum);

            // Update the number of users to ensure a new one is created:
            updateUserCount(idNum);

            // Print that the user has been created. 
            printf("User %s is successfully registered. \n", uInput);
            fclose(userDataFile);

        }
    break;

    case 2:

    printMovies();
   

    break;

    case 3:

    char userEnter[50];
    char registeredUsers[50];
    FILE *fileUser; 
    int userID3;
    int found3 = 0;
    int count;
    int mvChoice;
    float rating; 

    // This is the line array, which will read through it line by line. 
    char line3[256];



    printf("Enter your username: ");
    scanf("%s", userEnter);

    fileUser = fopen("user_data.txt", "r");

    if (fileUser == NULL) {
    printf("Error. File could not be opened. \n");
    exit(1);
    }

    while (fgets(line3, sizeof(line3), fileUser)) {
        sscanf(line3, "%s %d", registeredUsers, &userID3);

        if (strcasecmp(registeredUsers, userEnter) == 0) {
            found3 = 1;

            // This will display the movie menu
            count = printMovies();


            printf("Enter the number of the movie you want to rate: ");
            scanf("%d", &mvChoice);

            // We must use count - 1 as due to i++ in the printMovies() the count will be one bigger than the actual number of movies. 
            if (mvChoice < 0 || mvChoice > (count - 1)) {
                printf("Your choice is invalid. No movie choice presented at %d \n", mvChoice);
            }

            else {
                printf("Enter your rating (1-5): ");
                scanf("%f", &rating);

                if (rating < 1 || rating > 5) {
                    printf("Invalid rating. Please enter a rating between 1 and 5.\n");

                    // insert continue statement?
                }

                else {

                    // This is how the ratings will be processed and/or written:
                    ratingProcessing(mvChoice, userID3, rating);
                    printf("Rating recorded successfully.\n"); 
                }

            }

             break;





        }

        


    }

    if (found3 == 0) {
        printf("User not found. Please register first.\n");
    }

    fclose(fileUser);
    break;

    case 4:

    // This case is used to provide movie recommendations:
    FILE *userInfo;
    char nameIn[50];
    char line4[100];
    char username4[50];
    int movieChoice;
    int userID4;
    int found4 = 0;
    int full = 0;


    // Initalize recommendation array
    float recArray[10];

    printf("Enter your username: ");
    scanf("%s", nameIn);

    userInfo = fopen("user_data.txt", "r");

    if (userInfo == NULL) {
        printf("Error. File could not be opened. \n");
        exit(1);
    } 

    while (fgets(line4, sizeof(line4), userInfo)) {

        sscanf(line4, "%s %d", username4, &userID4);

        if(strcasecmp(username4, nameIn) == 0) {
            found4 = 1; 

        // Here, I am allocating memory to hold the data from the function that will be called.
        // I declared it 256.  
        char *recomName = malloc(256 * sizeof(char));
           
        // If the array is null, that means that memory was unable to be allocated. 
        if (recomName == NULL) {
        printf("Error. Memory could not be allocated.\n");
        }
            
        char *recCategory = malloc(256 * sizeof(char));
        
        if (recCategory == NULL) {
        printf("Error. Memory could not be allocated.\n");
           
            }

        
        // This will only execute if the ratings file is not found by the system. 
        if (recommendationHandling(userID4, recArray) == 0) {
                    free(recomName);
                    free(recCategory);
                    exit(1);
                }
        

        // Here, we are using the ratings given by the functions, 
        printf("***** Recommended Movies *****\n");

        // Creating an array to store the movies. 
        int completeMovies[10];

        for (int i = 0; i < 10; i++)  {
                    
            // Only those with scores above 0 are recommended 
            // They are marked as one in the array.

            if (recArray[i] > 0.0) {

                completeMovies[i] = 1;
            }
            
            else {

                completeMovies[i] = 0;

                }

        }

        // This is a loop which will run for as long as the array is not full. 
         
        while (full==0) {

            // This calls the method to check if the array has been filled with ones, and if it has, we break this loop. 
            if (arrayFull(completeMovies) == 0) {
                full = 1;
                break;
            }

            else {

                // Here we are initalizing all the array variables for the array:
                // Allocated to max size. 
                char *currentCat = malloc(256 * sizeof(char));
                
                
                // I
                if (currentCat == NULL) {

                 printf("Error. Memory could not be allocated.\n");

                 }

                // Create variables to keep track of operations. 
                int catAllocated = 0;
                int recNum = 1;

                // This loop checks through each element in the indice of the array.
                        for(int i = 0; i < 10; i++) {

                            // This checks if the movie is registered as a recommendation. 
                            if (completeMovies[i] == 1) {

                                // This checks if the category of the movie to be allocated is already there, if not allocate it.
                                if (catAllocated == 0) {
                                    
                                    // This gives us the movie data and then copies the category into the current category. 
                                    getmovData(i, recomName, recCategory);
                                    strcpy(currentCat, recCategory);
                                    
                                    // This prints the current category and then displays the recommended movies. 
                                    printf("\n***** %s Movies *****\n", currentCat);

                                    // Prints out the recommended movies. 
                                    printf("%d. %s (%s) - Predicted rating: %1.1f\n", recNum, recomName, recCategory, recArray[i]);

                                    // This removes the recommendation flag, then increments the recNum whilst category flag is turned on. 
                                    completeMovies[i] = 0;
                                    catAllocated = 1;
                                    recNum += 1;
                                }


                                else {

                                    // This prints the recommendation in the same place if it is of the same category. 
                                    getmovData(i, recomName, recCategory);

                                    // This checks that and then does it. 
                                    if (strcmp(currentCat, recCategory) == 0) {
                                        printf("%d. %s (%s) - Predicted rating: %1.1f\n", recNum, recomName, recCategory, recArray[i]);
                                        completeMovies[i] = 0;
                                        recNum += 1;
                                    }
                                }
                            }
                        }

                        // Free up the current category variable after each cycle
                        free(currentCat);



            }



        }

        printf("\n");
        break;

        }

        // In the event that the user could not be found:
        if (found4 == 0) {
            printf("User not found. Please register first. \n");
            break;

        }
    }

    fclose(userInfo);
    break;

    case 0:

    // Terminating the program when the user presses O. 
    printf("Program will now terminate. Thank you for using our Movie Recommendation Program.\n");
    exit(1);

    break;

    default:
    printf("Error. Something went wrong in the switch.");

    break;


   }

}

int main() {
    
    int choice;

    do{
        printMenu();
        scanf("%d", &choice);
        MenuSwitch(choice);
    } while (choice >= 0 && choice <= 4);



    return 0;
}
