#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // For rand() and srand()
#include <time.h>    // For seeding the random number generator

#define FILENAME "quiz_scores.txt"
#define TOTAL_QUESTIONS 20  // Total number of questions
#define QUESTIONS_TO_ASK 10  // Number of questions to ask

// Structure to store user details
struct User {
    char name[50];
    int score;
};

// Structure to store quiz questions and answers
struct Question {
    char question[256];
    char options[4][50];
    int correctAnswer;  // Index of the correct answer (1 to 4)
};

// Function to shuffle questions
void shuffle(int arr[], int n) {
    srand(time(0));  // Seed random number generator
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Generate a random index
        // Swap arr[i] with arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Function to conduct the quiz with randomized questions
int conductQuiz(struct Question questions[], int numQuestions) {
    int score = 0;
    int answer;

    // Create an array of indices (0 to numQuestions - 1)
    int indices[numQuestions];
    for (int i = 0; i < numQuestions; i++) {
        indices[i] = i;
    }

    // Shuffle the indices to randomize question order
    shuffle(indices, numQuestions);

    // Ask questions in the shuffled order
    for (int i = 0; i < QUESTIONS_TO_ASK; i++) {
        int questionIndex = indices[i];

        printf("\n%s\n", questions[questionIndex].question);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, questions[questionIndex].options[j]);
        }
        printf("Enter your answer (or 0 to exit): ");
        scanf("%d", &answer);

        // Check if the user wants to exit
        if (answer == 0) {
            printf("Exiting the quiz. Your current score: %d\n", score);
            return score;  // Return the score before exiting
        }

        // Check if the answer is valid
        if (answer < 1 || answer > 4) {
            printf("Invalid option. Please select a number between 1 and 4.\n");
            i--;  // Decrement i to repeat the current question
            continue;  // Skip to the next iteration
        }

        // Check if the answer is correct
        if (answer == questions[questionIndex].correctAnswer) {
            score++;
        }
    }

    return score;  // Return the total score
}

// Function to save score to file
void saveScore(struct User user) {
    FILE *file = fopen(FILENAME, "a");  // Open the file in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    // Use tab to separate the name and score, ensuring space handling
    fprintf(file, "%s\t%d\n", user.name, user.score);  // Save user name and score
    fclose(file);  // Close the file
}

// Function to display previous scores
void displayPreviousScores(char name[]) {
    FILE *file = fopen(FILENAME, "r");  // Open the file in read mode
    if (file == NULL) {
        printf("No previous scores found.\n");
        return;
    }

    char storedName[50];
    int storedScore;
    int found = 0;

    printf("\nPrevious scores for %s:\n", name);

    // Use fscanf to handle spaces in names
    while (fscanf(file, "%49[^\t]\t%d\n", storedName, &storedScore) != EOF) {
        if (strcmp(storedName, name) == 0) {  // Check if the name matches
            printf("Score: %d\n", storedScore);
            found = 1;
        }
    }

    if (!found) {
        printf("No previous scores found for this user.\n");
    }

    fclose(file);  // Close the file
}

int main() {
    struct User user;  // Declare a User structure variable
    int choice;  // For the main menu

    // Define the quiz questions
    struct Question questions[TOTAL_QUESTIONS] = {
        {"What is the capital of France?", {"Berlin", "Madrid", "Paris", "Rome"}, 3},
        {"What Subject Aaron sir teaches ?", {"python", "C", "Hindi", "Maths"}, 2},
        {"Which planet is known as the Red Planet?", {"Mars", "Earth", "Jupiter", "Venus"}, 1},
        {"What is the url of Aaron sir's website", {"Art.santechz.com", "art.santa.com", "art.santeckz.com", "art.santechz.com"}, 4},
        {"Who is known as the father of computers?", {"Alan Turing", "Steve Jobs", "Bill Gates", "Charles Babbage"}, 4},
        {"What is the chemical symbol for gold?", {"Au", "Ag", "Fe", "Hg"}, 1},
        {"How many continents are there?", {"5", "6", "7", "8"}, 3},
        {"What is the speed of light?", {"299,792 km/s", "150,000 km/s", "1,080 km/s", "100,000 km/s"}, 1},
        {"What is the boiling point of water?", {"50°C", "100°C", "150°C", "200°C"}, 2},  // Corrected question
        {"Who is HOD of the It department?", {"Sir Aaron", "Sir Roy", "Sir Jojan", "Sir Ashok"}, 2},
        {"What is the smallest prime number?", {"0", "1", "2", "3"}, 3},
        {"What is the capital of Japan?", {"Beijing", "Seoul", "Bangkok", "Tokyo"}, 4},
        {"What is H2O commonly known as?", {"Water", "Salt", "Sugar", "Oxygen"}, 1},
        {"Which is the largest continent?", {"Africa", "Asia", "North America", "Antarctica"}, 2},
        {"Who painted the Mona Lisa?", {"Vincent Van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Claude Monet"}, 3},
        {"Which sport is not officially played in xaviers?", {"Boxing", "badminton", "Basketball", "hockey"}, 1},
        {"How many bones are in the adult human body?", {"213", "305", "150", "206"}, 4},
        {"Who is the principle of st xaviers college", {"Dr. Hrishikesh Samant", "Dr. Rajendra Shinde", "Dr. Sanjay Parab", "Mr. Hasnain Naqvi"}, 2},
        {"Who was the first man on the Moon?", {"Neil Armstrong", "Buzz Aldrain", "Yuri Gagarin", "Michael Collins"}, 1},
        {"What is the longest river in the world?", {"Amazon", "Yangtze", "Nile", "Mississippi"}, 3},
        {"Who is the founder of C language", {"Walter White", "Tony Stark", "Thomas Shelby", "Dennis Ritchie"}, 4}
    };

    // Main menu loop
    do {
        printf("\n--- Quiz Menu ---\n");
        printf("1. Start Quiz\n");
        printf("2. Show Previous Scores\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline left by scanf

        switch (choice) {
            case 1:
                // Get user details each time the quiz starts
                printf("Enter your name: ");
                fgets(user.name, 50, stdin);  // Read user name
                user.name[strcspn(user.name, "\n")] = 0;  // Remove newline character from the input

                // Conduct the quiz with random question order and calculate score
                user.score = conductQuiz(questions, TOTAL_QUESTIONS);

                // Display user details and score
                printf("\nUser: %s\n", user.name);
                printf("Your score: %d/%d\n", user.score, QUESTIONS_TO_ASK);

                // Save the score to file
                saveScore(user);
                break;

            case 2:
                // Get user name for viewing previous scores
                printf("Enter your name to view previous scores: ");
                fgets(user.name, 50, stdin);
                user.name[strcspn(user.name, "\n")] = 0;

                // Display previous scores for the entered name
                displayPreviousScores(user.name);
                break;

            case 3:
                printf("Exiting the program.\nThank you for playing the quiz.\n");
                break;

            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
