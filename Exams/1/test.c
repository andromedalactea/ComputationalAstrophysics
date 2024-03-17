#include <stdio.h>

int main() {
    // Define an array with the specific values
    int values[] = {50, 100, 300, 1000};
    // Calculate the number of elements in the array
    int length = sizeof(values) / sizeof(values[0]);

    // Iterate over the array using a for loop
    for (int i = 0; i < length; i++) {
        // Use values[i] as the current value
        printf("Current value: %d\n", values[i]);
        // Your code that uses values[i] goes here
    }

    return 0;
}
