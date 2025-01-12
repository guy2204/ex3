/******************
Name: Guy Melamed
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define ADDONE 1
#define ADDALL 2
#define STATS 3
#define PRINT 4
#define INSIGHTS 5
#define DELTAS 6
#define DONE 7

void printMenu();
void ResetDayOfYearValue(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void StatusAnalyze(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                   char brands[NUM_OF_BRANDS][BRANDS_NAMES], char types[NUM_OF_TYPES][TYPES_NAMES]);
int SumAllSaels(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void BestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day,
                   char brands[NUM_OF_BRANDS][BRANDS_NAMES]);
void BestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, char types[NUM_OF_TYPES][TYPES_NAMES]);
void OverAllBestSaleType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                         char types[NUM_OF_TYPES][TYPES_NAMES]);
void PrintAllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                  char brands[NUM_OF_BRANDS][BRANDS_NAMES], char types[NUM_OF_TYPES][TYPES_NAMES]);
void OverAllBestSaleBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                          char brands[NUM_OF_BRANDS][BRANDS_NAMES]);
void OverAllBestSaleDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR]);
void AvgDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCounter,
                     char brands[NUM_OF_BRANDS][BRANDS_NAMES]);
void DataOfBrands(int dataForBrandsPerDay[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day,
                  int daysValide[DAYS_IN_YEAR], char brands[NUM_OF_BRANDS][BRANDS_NAMES], int brandInput,
                  int typesInput[NUM_OF_TYPES]);

int main()
{
    char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
    char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
    int brandInput = -1, typesInput[NUM_OF_TYPES] = {0};
    int day = 0;
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int dataForBrandsPerDay[NUM_OF_BRANDS] = {0};
    int daysValide[DAYS_IN_YEAR] = {0};
    int choice;
    ResetDayOfYearValue(cube);
    printMenu();
    scanf(" %d", &choice);
    while (choice != DONE)
    {
        switch (choice)
        {
        case ADDONE:

            break;
        case ADDALL:
            DataOfBrands(dataForBrandsPerDay, cube, day, daysValide, brands, brandInput, typesInput);
            day++;

            break;
        case STATS:
            StatusAnalyze(cube, daysValide, brands, types);
            break;
        case PRINT:
            PrintAllData(cube, daysValide, brands, types);
            break;
        case INSIGHTS:
            OverAllBestSaleBrand(cube, daysValide, brands);
            OverAllBestSaleType(cube, daysValide, types);
            OverAllBestSaleDay(cube, daysValide);
            break;
        case DELTAS:
            AvgDeltaMetrics(cube, day, brands);
            break;
        default:
            printf("Invalid input\n");
            break;
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
void AvgDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int dayCounter,
                     char brands[NUM_OF_BRANDS][BRANDS_NAMES])
{
    int delta = 0;
    double avg = 0;
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
    {
        delta = 0;
        for (int type = 0; type < NUM_OF_TYPES; type++)
        {
            for (int day = 0; day < (dayCounter - 1); day++)
            {
                delta += cube[day + 1][brand][type] - cube[day][brand][type];
            }
        }
        if (dayCounter > 1)
        {
            avg = (double)delta / (dayCounter - 1);
            printf("Brand: %s, Average Delta: %f\n", brands[brand], avg);

        }
        else if(dayCounter == 1)
        {
            avg = (double)delta / dayCounter;
            printf("Brand: %s, Average Delta: %f\n", brands[brand], avg);

        }
        else
        {
            printf("Brand: %s, Average Delta: 0.000000\n", brands[brand]);
        }
    }
}
void OverAllBestSaleDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR])
{
    int maxDay = -1;
    int maxDayIndex = -1;
    int sum = -1;
    for (int day = 0; day < DAYS_IN_YEAR && daysValide[day]; day++)
    {
        sum = 0;
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
        {
            for (int type = 0; type < NUM_OF_TYPES; type++)
            {
                sum += cube[day][brand][type];
            }
        }
        if (maxDay < sum)
        {
            maxDay = sum;
            maxDayIndex = day;
        }
    }
    printf("The most profitable day was day number %d: %d$\n", maxDayIndex + 1, maxDay);
}
void OverAllBestSaleType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                         char types[NUM_OF_TYPES][TYPES_NAMES])
{
    int maxType = -1;
    int maxTypeIndex = -1;
    int sum = -1;
    printf("The best-selling type of car is ");
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        sum = 0;
        for (int day = 0; day < DAYS_IN_YEAR && daysValide[day]; day++)
        {
            for (int j = 0; j < NUM_OF_BRANDS; j++)
            {
                sum += cube[day][j][i];
            }
        }
        if (sum > maxType)
        {
            maxType = sum;
            maxTypeIndex = i;
        }
    }
    printf("%s: %d$\n", types[maxTypeIndex], maxType);
}
void OverAllBestSaleBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                          char brands[NUM_OF_BRANDS][BRANDS_NAMES])
{
    int maxBrand = -1;
    int maxBrandIndex = -1;
    int sum = -1;
    printf("The best-selling brand overall is ");
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        sum = 0;
        for (int day = 0; day < DAYS_IN_YEAR && daysValide[day]; day++)
        {

            for (int j = 0; j < NUM_OF_TYPES; j++)
            {
                sum += cube[day][i][j];
            }
        }
        if (sum > maxBrand)
        {
            maxBrand = sum;
            maxBrandIndex = i;
        }
    }
    printf("%s: %d$\n", brands[maxBrandIndex], maxBrand);
}
void PrintAllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                  char brands[NUM_OF_BRANDS][BRANDS_NAMES], char types[NUM_OF_TYPES][TYPES_NAMES])
{
    printf("*****************************************\n\n");
    for (int y = 0; y < NUM_OF_BRANDS; y++)
    {
        printf("Sales for %s:\n", brands[y]);
        for (int z = 0; z < DAYS_IN_YEAR && daysValide[z]; z++)
        {
            printf("Day %d- ", z + 1);
            for (int x = 0; x < NUM_OF_TYPES; x++)
            {
                printf("%s: %d ", types[x], cube[z][y][x]);
            }
            printf("\n");
        }
    }
    printf("\n*****************************************\n");
}
void printMenu()
{
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
// reset the arry 'cube', change the value 'DAYS_IN_YEAR' to -1
void ResetDayOfYearValue(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for (int x = 0; x < DAYS_IN_YEAR; x++)
    {
        for (int y = 0; y < NUM_OF_BRANDS; y++)
        {
            for (int z = 0; z < NUM_OF_TYPES; z++)
            {
                cube[x][y][z] = -1;
            }
        }
    }
}

void DataOfBrands(int dataForBrandsPerDay[NUM_OF_BRANDS], int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day,
                  int daysValide[DAYS_IN_YEAR], char brands[NUM_OF_BRANDS][BRANDS_NAMES], int brandInput,
                  int typesInput[NUM_OF_TYPES])
{
    int counter = 0;
    while (counter < NUM_OF_BRANDS)
    {
        printf("No data for brands");
        for (int x = 0; x < NUM_OF_BRANDS; x++)
        {
            if (dataForBrandsPerDay[x] == 0)
            {
                printf(" %s", brands[x]);
            }
        }
        printf("\n");
        printf("Please complete the data \n");
        scanf("%d", &brandInput);
        while (brandInput < 0 || brandInput >= NUM_OF_BRANDS)
        {
            printf("invalid numbers, all numbers need to be positive\n");
            scanf("%d", &brandInput);
            // scanf("%d %d %d %d", &typesInput[0], &typesInput[1], &typesInput[2], &typesInput[3]);
        }
        scanf("%d %d %d %d", &typesInput[0], &typesInput[1], &typesInput[2], &typesInput[3]);
        while (brandInput < 0 || brandInput >= NUM_OF_BRANDS || typesInput[0] < 0 || typesInput[1] < 0 
                || typesInput[2] < 0 || typesInput[3] < 0)
        {
            printf("invalid numbers, all numbers need to be positive\n");
            // scanf("%d", &brandInput);
            scanf("%d %d %d %d", &typesInput[0], &typesInput[1], &typesInput[2], &typesInput[3]);
        }
        if (dataForBrandsPerDay[brandInput] == 0)
        {
            for (int i = 0; i < NUM_OF_TYPES; i++)
            {
                cube[day][brandInput][i] = typesInput[i];
            }
            dataForBrandsPerDay[brandInput] = 1;
            counter++;
        }
        else
        {
            printf("This brand is not valid\n");
        }
    }
    daysValide[day] = 1;
    for (int x = 0; x < NUM_OF_BRANDS; x++)
    {
        dataForBrandsPerDay[x] = 0;
    }
}
void StatusAnalyze(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int daysValide[DAYS_IN_YEAR],
                   char brands[NUM_OF_BRANDS][BRANDS_NAMES], char types[NUM_OF_TYPES][TYPES_NAMES])
{
    int choice = -1;
    printf("What day would you like to analyze?\n");
    scanf("%d", &choice);
    while (choice < 0 || choice >= DAYS_IN_YEAR || daysValide[choice - 1] == 0)
    {

        printf("Please enter a valid day.\n");
        printf("What day would you like to analyze?\n");
        scanf("%d", &choice);
    }
    printf("In day number %d:\n", choice);
    int sum = SumAllSaels(cube, choice);
    printf("The sales total was %d\n", sum);
    printf("The best sold brand with ");
    BestSoldBrand(cube, choice, brands);
    printf("\n");
    printf("The best sold type with ");
    BestSoldType(cube, choice, types);
    printf("\n");
}
void BestSoldType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, char types[NUM_OF_TYPES][TYPES_NAMES])
{
    int maxType = -1;
    int maxTypeIndex = -1;
    int sum = -1;
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        sum = 0;
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            sum += cube[day - 1][j][i];
        }
        if (sum > maxType)
        {
            maxType = sum;
            maxTypeIndex = i;
        }
    }
    printf("%d sales was %s", maxType, types[maxTypeIndex]);
}
void BestSoldBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day,
                   char brands[NUM_OF_BRANDS][BRANDS_NAMES])
{
    int maxBrand = -1;
    int maxBrandIndex = -1;
    int sum = -1;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        sum = 0;
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            sum += cube[day - 1][i][j];
        }
        if (sum > maxBrand)
        {
            maxBrand = sum;
            maxBrandIndex = i;
        }
    }
    printf("%d sales was %s", maxBrand, brands[maxBrandIndex]);
}
int SumAllSaels(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int sum = 0;
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
    {
        for (int type = 0; type < NUM_OF_TYPES; type++)
        {
            sum += cube[day - 1][brand][type];
            // printf("day: %d, brand: %d, type: %d,sum:: %d\n",day,brand,type,sum);
        }
    }
    return sum;
}
