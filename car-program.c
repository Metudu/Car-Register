#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1)

// Creating "CAR" variable type
typedef struct structure
{
    char carbrand[20];
    char ownername[20];
    int firstregistration;
} CAR;

void clear() // to clear the console
{
    system("clear");
}

int isSelectionCorrect(char control[])
{
    char input;
    printf("Do you want to %s?(y/n):", control);
    scanf("%c", &input);
    getchar();
    while (input != 'y' && input != 'n')
    {
        printf("Invalid option. Plese try again.\nDo you want to %s?(y/n):", control);
        scanf("%c",&input);
        getchar();
    }

    if (input == 'y')
        return 1;
    else if (input == 'n')
        return 0;
    
}

//  Main Screen
//  The screen that shows to the user the options
int main_screen()
{
    int select;
    printf("========================================\n1 -> Add a car\n2 -> Remove a car\n3 -> Show All Cars\n9 -> Exit\nSelect:");
    scanf("%d", &select);
    getchar();
    return select; //  returns the option user selected
}

//   Adding car Function
void addCar(CAR *p, int i)
{
    //  CAR *p represents the pointer which stores the memory location where all of the information is
    //  If we assume *p like an array, "i" represents the length of the array"
    printf("Car - %d\n-----------------------------\n", i);
    printf("Enter the car brand:");
    fgets((p + i - 1)->carbrand, 20, stdin);
    printf("Enter the owner's name:");
    fgets((p + i - 1)->ownername, 20, stdin);
    printf("Enter the car model:");
    scanf("%d", &((p + i - 1)->firstregistration));
    getchar();
}

//  Show Information Function
//  The screen that shows to the user the cars and it's information
void showInfo(CAR *p, int i)
{

    //  CAR *p represents the pointer which stores the memory location where all of the information is
    //  If we assume *p like an array, "i" represents the length of the array"
    printf("***************************************");
    for (int r = 0; r < i; r++)
    {
        printf("\n\nCar - %d\n________________________\n", r + 1);
        printf("Car Brand: %s", ((p + r)->carbrand));
        printf("Owner Name: %s", ((p + r)->ownername));
        printf("Car's first registration: %d\n", ((p + r)->firstregistration));
        printf("=============================================\n");
    }
    printf("\n***************************************\n");
}

int removeCar(CAR *p, int i)
{
    //  CAR *p represents the pointer which stores the memory location where all of the information is
    //  If we assume *p like an array, "i" represents the length of the array"
    showInfo(p, i);
    int remove, tempint;
    char temp[20];
    printf("Which car you want to delete:");
    scanf("%d", &remove);
    getchar();

    while (remove < 1 || remove >= i)
    {
        printf("This car is not exist!\nWhich car you want to delete:");
        scanf("%d",&remove);
        getchar();
    }
    
    clear();
    int return_remove = remove;
    for (; remove < i; remove++)
    {
        strcpy(temp, (p + remove - 1)->carbrand);                              //
        strcpy((p + remove - 1)->carbrand, (p + remove)->carbrand);            //
        strcpy((p + remove)->carbrand, temp);                                  //
        strcpy(temp, (p + remove - 1)->ownername);                             //  If we assume *p like an array, this all processes
        strcpy((p + remove - 1)->ownername, (p + remove)->ownername);          //  interchanges p[index] and p[index+1]
        strcpy((p + remove)->ownername, temp);                                 //
        tempint = (p + remove - 1)->firstregistration;                         //
        (p + remove - 1)->firstregistration = (p + remove)->firstregistration; //
        (p + remove)->firstregistration = tempint;                             //
    }
    clear();
    printf("Car - %d removed successfully!\n",return_remove);
    return return_remove;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    CAR *cars = malloc(sizeof(CAR) * i);

here:
    switch (main_screen())
    {
    case 1:
        if (isSelectionCorrect("add car"))
        {
            clear();
            cars = realloc(cars, sizeof(CAR) * (++i));
            addCar(cars, i);
            clear();
            printf("Car - %d added successfully!\n", i);
        }
        else
        {
            clear();
            printf("Returned to main menu!\n");
        }
        goto here;
        break;

    case 2:
    if (i == 0) //  If the length equals to 0, that means there is no car registered
    {
        clear();
        printf("\nYou can't do this because car list is already empty!\n\n");
    }
    else
    {
        if (isSelectionCorrect("remove car"))
        {
            clear();
            int remove = removeCar(cars, i);
            cars = realloc(cars, sizeof(CAR) * (--i));
        }
        else
        {
            clear();
            printf("Returned to main menu!\n");
        }
    }
    
        goto here;
        break;
    case 3:
        clear();
        showInfo(cars, i);
        goto here;
        break;
    case 9:
        printf("Exited successfully!");
        return EXIT_SUCCESS;
        break;
    default:
        break;
    }

    free(cars);
    return 0;
}
