// a program that prompts the user for a credit card number and then reports (via printf) whether it
// is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s
// format herein.

// AMEX -->> 15 digits, starts with 34 or 35
// MASTERCARD -->> 16 digits, starts with 51, 52, 53, 54 or 55
// VISA -->> 13 or 16 digits, starts with 4

// valid (VISA) sample: 4003600000000014

#include <cs50.h>
#include <stdio.h>

bool validate(long num);
int count_length(long num);
string check_length(int length, long num);

int main(void)
{
    // prompt for input
    long number = get_long("Number: ");

    // calculate the checksum
    if (!validate(number))
    {
        printf("INVALID\n");
        return 0;
    }

    // check for card length and starting digits
    int length = count_length(number);

    // print resault (AMEX, MASTERCARD, VISA or INVALID)
    string resault = check_length(length, number);

    printf("%s\n", resault);
}

// Calculates the checksum using the Luhn algorithm
bool validate(long num)
{
    int sum = 0;
    int pos = 0; // Position counter, starting from the last digit
    while (num != 0)
    {
        int digit = num % 10; // Extract the last digit

        if ((pos % 2) == 1) // If it's every other digit (starting from second-to-last)
        {
            int product = digit * 2;

            if (product < 10)
            {
                // If product is a single digit, add it directly
                sum += product;
            }
            else
            {
                // If product is two digits, add the digits separately
                int first_digit = product / 10;
                int second_digit = product % 10;
                sum += (first_digit + second_digit);
            }
        }
        else
        {
            // For digits not being multiplied by 2, just add them to the sum
            sum += digit;
        }
        num /= 10; // Remove the last digit
        pos++;     // Move to the next digit position
    }

    // ckeck if the last digit is 0
    if ((sum % 10) != 0)
    {
        return false;
    }
    return true;
}

// count the card's length
int count_length(long num)
{
    int count = 0; // card length
    while (num != 0)
    {
        count++;
        num /= 10;
    }
    return count;
}

// check for card length and starting digits
string check_length(int length, long num)
{
    // Get first two digits
    long copy = num;
    while (copy >= 100)
    {
        copy /= 10;
    }
    int first_two = copy;
    int first = first_two / 10;

    // check for AMEX -->> 15 digits, starts with 34 or 35
    if (length == 15 && (first_two == 34 || first_two == 37))
    {
        return "AMEX";
    }

    // check for VISA -->> 13 or 16 digits, starts with 4
    else if ((length == 13 || length == 16) && first == 4)
    {
        return "VISA";
    }

    // check for MASTERCARD -->> 16 digits, starts with 51, 52, 53, 54 or 55
    else if (length == 16 && (first_two >= 51 && first_two <= 55))
    {
        return "MASTERCARD";
    }

    return "INVALID";
}
