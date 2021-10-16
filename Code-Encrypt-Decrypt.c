/*
EXAM - Security authorisation based on numeric codes.
Program that encrypts and decrypts 4 digit codes

Displays a menu with 6 options
1 = create a code or generate a random code,
2 = encrypt the code
3 = compare the code to the access code (4523)
4 = decrypt the encrypted code
5 = display to the user how many codes were correct and/or incorrect
6 = exit the program.

Author: Raphael Bien Cabangbang
Student no.: c19464094
Date: 07/05/20(started), 08/05/20(finished)
OS: Windows 10
Compiler: mingw(gcc) - Code::Blocks
*/
// ANSWER = 1234

//headers
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4         //size of the codes

struct code_counter     //structure that keeps the amount of codes that were correct and/or wrong
{
 int correct_code;
 int wrong_code;
 };

//funtion signatures
int generate_code(int *user_code);
int create_code(int *user_code);
int encrypt_code(int *user_code);
int compare_code(int *access_code, int *user_code, struct code_counter *counter);
int decrypt_code(int *user_code);
int display_code(struct code_counter *counter);
//end of function signatures

//begin main
int main()
{

    struct code_counter counter;

    int input;                          //for the main menu, decidew what the user wants to do
    int access_code[SIZE]={4,5,2,3};    // the access code, does not change
    int user_code[SIZE]={0};            // the user's entered or generated code
    int condition = 0;                  // condition that allow or prohibit the user from doing certain actions
    int case_1_input;                   // allows the user to decide to generate or create a code

    counter.correct_code = 0;           // correct code counter
    counter.wrong_code = 0;             // wrong code counter

    while(1)
    {
        printf("\n\n~~~~~~MENU~~~~~\n");
        printf("1. Enter a code or generate a random code\n");
        printf("2. Encrypt code\n");
        printf("3. Check if the encrypted code matches the default authorised access code\n");
        printf("4. Decrypt code\n");
        printf("5. Display the number of times the encrypted code is (i) correct/ (ii) wrong\n");
        printf("6. Exit Program\n\n");
        printf("Your input:");

        scanf("%d", &input);        //takes user input

        switch(input)
        {


            case 1:     //user wishes to create or generate a code
            {
                printf("1. Enter a code\n");
                printf("2. Generate a random code\n\n"); //asks user to choose to create or generate code
                printf("your input: ");

                scanf("%d", &case_1_input);     // takes user input

                if(case_1_input==1)
                {
                    create_code(user_code);     //function that allow the user to enter a 4 digit code

                     condition = 1;                  //allows the user to access the other options on the menu
                }

                else if(case_1_input==2)
                {
                    generate_code(user_code);   //function that generates a 4 digit code

                    condition = 1;                  //allows the user to access the other options on the menu
                }

                else
                {
                    printf("\ninvalid input");  //error message if the user enters a invalid input
                }

                break;
            }


            case 2:     //encrypts user's code
            {
                if(condition==1)    //wont allow the user to encrypt if they dont have a code
                {
                    encrypt_code(user_code);    // encrypts the user's code

                    condition = 2; //allows the user to acces options 3 & 4 on the menu and prevent them from encrypting twice

                }

                else if(condition==2)   //tells the user they cannot encrypt their code twice
                {
                    printf("You cannot encrypt your code twice");
                }

                else
                {
                    printf("\nYou have not entered or generated a code.\n"); //message that tells the user to get a code
                }

                break;
            }


            case 3:     //compares the access code to the user's encrypted code
            {
                if(condition==2)    //wont allow the user to select this option if they have not encrypted their code first
                {
                    compare_code(access_code, user_code, &counter);     //compares the access code to the user's encrypted code and records the ammount of correct and wrong codes
                }

                else
                {
                    printf("\nEncrypt your code first"); //message that tells the user has to encrypt their code first
                }

                break;
            }


            case 4:     //decrypts the user's encrypted code
            {
                if(condition==2)     //wont allow the user to select this option if they have not encrypted their code first
                {
                    decrypt_code(user_code); //decrypts the user's encrypte code

                    condition=1;    //allows the user to encrypt their code again and prevent the user from decrypting twice
                }

                else if(condition == 1||condition == 0)     //prevets the user from dercypting twice or decrypting an uncrypted code
                {
                    printf("\nEncrypt your code first"); //message that tells the user has to encypt their code first
                }

                break;
            }


            case 5:     //displays the correct and wrong code counter
            {
                display_code(&counter);      //displays the correct and wrong code counter

                break;
            }


            case 6:     //exits the program
            {
                printf("\n\nYou have exited the program\n\n"); //tells the user they have exited the program

                return 0;   //exits the program
            }


            default:    //if the user enters an invalid input
            {
                printf("\ninvalid input\n"); //default reponce if a number not displayed is enetered
            }

        }//end switch
    }//end while
} //end main


/*----------------------------------FUNCTIONS--------------------------------*/
int generate_code(int *code) //generates a random code
{
    int i;

    for(i=0;i<SIZE;i++)
    {
        *(code+i) = rand() % 10; //selects a random number between 0-9
    }

    printf("\nYour randomly generated code is: ");

    for(i=0;i<SIZE;i++)
    {
        printf("%d", *(code+i)); //displays the 4 digit code to the user
    }
}
//end function

int create_code(int *code)  //allows the user to create their own 4 digit code
{
    int i;

    printf("\nEnter a 4 digit code using numbers between 0-9 \n");


    for(i=0;i<SIZE;i++)
    {
        scanf("%d", (&*(code+i)));  //takes user input

        if(*(code+i)<0||*(code+i)>9)             //makes sure the user inputs numbers from 0-9
        {
            printf("invalid number, please re-enter a valid number\n");
            i--;        //this puts the for loop back so that the invalid number isn't stored in the array
        }
    }

     printf("\nYour code is: ");

      for(i=0;i<SIZE;i++)
    {
        printf("%d", *(code+i));    //displays the code to the user
    }

}
//end function

int encrypt_code(int *code) //encrypts the user's code
{
    int i;
    int swap;       //temp variable

    swap = *(code+0);       //stores the first digit in a temp variable
    *(code+0) = *(code+2);  //puts the third digit in the first position
    *(code+2) = swap;       //puts the fist digit in the third position

    swap = *(code+1);       //stores the second digit in a temp variable
    *(code+1) = *(code+3);  //puts the fourth digit in the second position
    *(code+3) = swap;       //puts the second digit in the fourth position

    for(i=0;i<SIZE;i++)
    {
        *(code+i) = *(code+i)+1;    //increases the value of each digit by 1
    }

    for(i=0;i<SIZE;i++)
    {
        if(*(code+i)== 10)          //checks if any digit has increased to 10
        {
            *(code+i) = 0;          //if any digit has increase to 10 it is replaced by a 0
        }
    }

    printf("\nYour encrypted code is: ");

    for(i=0;i<SIZE;i++)
    {
        printf("%d", *(code+i));    //displays encrypted code to user
    }
}
//end function

int compare_code(int *access, int *user, struct code_counter *counter) //compares the user's encrypted code with the access code(4523)
{
    int i = 0;
    int count = 0;  //keeps track of the digits that match the access code

    for(i=0;i<SIZE;i++)
    {
        if(*(access+i)==*(user+i)) //checks if the user's code matches the access code
        {
            count++;    //for every correct digit in the right position the count increases
        }
    }

    if(count==SIZE)     //if count = SIZE(4) all the digits in the user's code are in correct and in the correct position
    {
        printf("\nCorrect Code entered");

        counter->correct_code = counter->correct_code+1;    //increase the correct code counter by 1
    }
    else            //if count != SIZE(4) the user's code is not the same as the access code
    {
        printf("\nWrong Code entered");

        counter->wrong_code = counter->wrong_code+1;        //increases the wrong code counter by 1

    }
}
//end function

int decrypt_code(int *code)
{

    int i;
    int swap;       //temp variable



    for(i=0;i<SIZE;i++)
    {
        *(code+i) = *(code+i)-1;    //decreases all the digits in the code by 1
    }

    swap = *(code+0);               //stores the first digit in the temp variable
    *(code+0) = *(code+2);          //puts the third digit in the first position
    *(code+2) = swap;               //puts the first digit in the thrid position

    swap = *(code+1);               //stored the second digit in the temp variable
    *(code+1) = *(code+3);          //puts the fourth variable in the second position
    *(code+3) = swap;               //puts the second variable in the fourth position


    for(i=0;i<SIZE;i++)
    {
        if(*(code+i)== -1)          //checks if any digit has decreased to -1
        {
            *(code+i) = 9;          //if any digit has decreased to -1 it is replaced by 9
        }
    }

    printf("\nYour decrypted code is: ");

    for(i=0;i<SIZE;i++)
    {
        printf("%d", *(code+i));    //displays the decrypted code to the user
    }
}
//end fuction

int display_code(struct code_counter *counter) //displays the ammount of correct and wrong codes in this session
{
    printf("\nCorrect codes: %d \n", counter->correct_code); //displays the ammount of correct codes
    printf("Wrong codes: %d \n", counter->wrong_code);     //displays the amount of wrong codes
}
//end function
/*----------------------------------FUNCTIONS--------------------------------*/
