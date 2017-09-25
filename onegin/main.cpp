#include <iostream>
#include <gmpxx.h>

void sort(int, char[][255]);

int main() {

    printf("Sorting english version of Zhenya Onegin\n"
                   "1.0 (c) Lesha\n");

    int number_of_verses = 0;
    printf("Enter the number of verses: ");
    scanf("%d", &number_of_verses);

    char verses[number_of_verses][255];
    printf("Enter the novel:\n");
    for (int i = 0; i<number_of_verses; i++)
        scanf("%s", verses[i]);

    sort(number_of_verses, verses);

    return 0;
}

void sort(int number_of_verses, char verses[][255]) {
    for (int i = 0; i<number_of_verses-1; i++) {
        if (*verses[i] > *verses[i + 1])
            std::swap(verses[i], verses[i + 1]);
    }
}