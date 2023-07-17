#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

/*
Question: https://cs50.harvard.edu/x/2023/psets/1/credit/
this uses the Lunn's algorithm to check if a card is legit.
then based on the
*/

int main(void)
{
    // variable declarations
    long int cardNumber; // to get the card number
    int numberCount = 0; // to get the length of the card number for validation
    long int  checksum; // copy for card number for destructive calculations
    bool isCardLengthValid; // flag value to set validness based on length of the card number
    bool isCardValid; // flag value to set validness based on Lunn's algorithm
    long int divisor = 1;
    long int multiplier = 10;
    int cardType;
    int lunnCheck;
    int lunnCheckSum1;
    int lunnCheckSum2;

    // getting the card number from the user and makeing a copy in checksum as our length check is destructive
    cardNumber = get_long("Enter your card number: ");
    checksum = cardNumber;

    // finding the length of the card
    while(checksum > 0){
        checksum = checksum / 10;
        numberCount++;
    }

    // the average length of the card numbers are 13 to 16, if its outside this spectrum card will be marked invalid
    if((13 <= numberCount) && (numberCount <= 16)){
        isCardLengthValid = true;
    }
    else{
        isCardLengthValid = false;
    }



    // code for checking cards validity using Lunns algorithm
    checksum = cardNumber;
    lunnCheck = 0;
    lunnCheckSum1 = 0;

    for(int i = 0; i < numberCount; i++){
        lunnCheck = (checksum%100 - checksum%10)/10;
        lunnCheck = lunnCheck * 2;
        if(lunnCheck * 2 >= 10){
            lunnCheck = lunnCheck % 10 + ((lunnCheck % 100)/10);
        }
        lunnCheckSum1 = lunnCheckSum1 + lunnCheck;
        checksum /= 100;
    }

    lunnCheck = 0;
    lunnCheckSum2 = 0;
    checksum = cardNumber;
    for(int i = 0; i < numberCount; i++){
        lunnCheck = checksum % 10;
        checksum = checksum / 100;
        lunnCheckSum2 = lunnCheckSum2 + lunnCheck;
    }

    if(((lunnCheckSum1 + lunnCheckSum2)%10) == 0){
        isCardValid = true;
    }
    else{
        isCardValid = false;
    }

    // checking the type of card
    if(isCardValid && isCardLengthValid){
        for(int i=0; i < numberCount-2; i++){
            divisor = divisor * multiplier;
        }
        cardType = cardNumber / divisor;


        if((cardType >= 51) && (cardType <= 55)){
        printf("MASTERCARD\n");
        }
        else if((cardType >= 40) && (cardType <= 49)){
            printf("VISA\n");
        }
        else if((cardType == 34) || (cardType == 37)){
            printf("AMEX\n");
        }
        else{
            printf("INVALID\n");
        }
    }
    else{
        printf("INVALID\n");
    }

}
