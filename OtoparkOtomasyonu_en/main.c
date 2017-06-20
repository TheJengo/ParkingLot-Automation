#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/*

    Daily Parking Lot Automation ( with C)
    Auth: Cengiz Cebeci
    Questions & Information : thejengo0o@gmail.com
    Language: English

*/
/* Global Variables*/
int countTry=0; // Error Counter
int park[25][10]; // Parking Lot Array

int main()
{   /* Local Variables */
    setlocale(LC_ALL, "English");
    int countCar=240,carProperty=4;
    /*
        countCar variable has 240 because our parking lot
        has 10 spot for in an hour so with a quick math
        our Max Car size is "24 x 10 = 240"

        You can change the sizes easily on park[][] Array and the rest of the code

        carProperty is an Array for properties of Car with 4 columns
        [Type] [Plate] [In] [Out]
        these are the values of the columns.
    */
    int car[countCar][carProperty]; // The Array for Cars informations
    int payment[countCar][carProperty-2]; // The Array for Payment informations
    /*
        If an entry is success we hold the informations of car Payments in this Array
        [Plate] [Payment]
        like this.
    */
    int lastCarPos=0; // Index Of Last Car that parked in the lot.
    char forMenu;   // Char For Menu Processes

    setZero(24,10,park);
    setZero(countCar,carProperty,car);
    setZero(countCar,carProperty-2,payment);
    /*
        Those three functions
        sets "0" for all elements of the Arrays.
        Normally we should use
        park[24][10] = {0}; or park[24][10] = 0;
        but sometimes those code lines does not work this why we set the values manually with this method.
    */

    /* Menu Process */
    do{
    int menuChoise=0;
    printf("INSERT / DELETE Car\t\t\t-1 \nList Cars\t\t\t\t-2 \nPayment Queries\t\t\t\t-3 \nMaximum & Minimum Payment Information\t-4 : ");
    scanf("%d",&menuChoise);
    printf("\n");
    printf("--------------------------------------------------------\n");
    switch(menuChoise)
    {
        /* Carr Add/Delete Processes */
        case 1:
                countTry=0;
                do{
                    int processChoise=0;
                    printf("Insert\t\t-1\nDelete\t\t-2 : "); scanf("%d",&processChoise);
                    printf("\n");
                    if(processChoise == 1)
                    {
                        lastCarPos = addCar(countCar,carProperty,car,payment,lastCarPos);
                        /*
                            To understand how addCar function works. Go to the Lines 274.
                            This line holds the return value of the addCar function and
                            assign the value to lastCarPos variable. We can use it continuously.
                        */
                        countTry = 3;
                    }
                    else if(processChoise == 2)
                    {
                       countTry=0;
                        do{
                            int carPlate=0;
                            listCars(lastCarPos,carProperty,car);
                            /*
                                Lists the cars in lot.
                            */
                            printf("Enter the plate of car you want to delete :"); scanf("%d",&carPlate);
                            if(checkInArray(countCar,carProperty,car,carPlate) == 1)
                            {
                                deleteCar(lastCarPos,carProperty,car,payment,carPlate,lastCarPos);
                                /*
                                    To understand how deleteCar function works. Go to the Lines 506.
                                    Girilen Plaka degerini ve ilgili plakaya ait butun verileri butun dizilerde temizler.
                                */
                                printf("%d Plate numbered car deleted on car list.\n",carPlate);
                                printf("\n");
                                countTry = 3;
                            }
                            else{
                                printf("The Plate number is doesn't exist.\n");
                                countTry++;
                            }
                            /*
                                if checkInArray returns 1 it works and deletes car.
                                it its retruns 0 it output the Errors in the else block.
                            */
                       }while(countTry != 3);
                    }
                    else
                    {
                      countTry++;
                      tryChecker(countTry);
                      /*
                        This function counts normal errors and returns the related outputs for user.
                      */
                    }
                }while(countTry!=3);
                returnMenu(forMenu);
                /*
                    After error counting processes the program asks the user "Exit/Return Menu".
                */
        break;

        /* Listing Processes */
        case 2:
            countTry=0;
                do{
                    int processChoise=0;
                    printf("Registered Cars\t\t\t-1 \nParking Lot Information\t\t-2 : "); scanf("%d",&processChoise);
                    printf("\n");
                    if(processChoise == 1)
                    {
                        if(lastCarPos == 0)
                        {
                            printf("You haven't car entry yet. Please insert car...\n");
                            countTry = 3;
                        }
                        listCars(lastCarPos,carProperty,car);
                        countTry = 3;
                    }
                    else if(processChoise == 2)
                    {
                        countTry=0;
                        int inHour,exitHour; // Variable for Check-In/Out Time
                        do{
                            printf("Check-IN time <0-24> : ");
                            scanf("%d",&inHour);
                            printf("Check-Out time <1-24> : ");
                            scanf("%d",&exitHour);
                            /* Check-In/Out Time Controls */
                            if(inHour>24 || inHour<-1 || exitHour<0 || exitHour>24 )
                            {
                                countTry++;
                                inHour=0;
                                exitHour=0;
                                printf("Invalid Check-in/out time!\n");
                            }
                            else if(exitHour<=inHour)
                            {
                            countTry++;
                            inHour=0;
                            exitHour=0;
                            printf("Check-Out time must be bigger than Check-in Time.!\n");
                            }
                            else{
                            listPark(inHour,exitHour);
                            /*
                                Lists the cars in lot.
                            */
                            countTry = 3;
                            }
                        }while(countTry!=3);
                    }
                    else
                    {
                      countTry++;
                      tryChecker(countTry);
                    }
                }while(countTry!=3);
              returnMenu(forMenu);
        break;

        /* Payment Processes */
        case 3:
           countTry=0;
                do{
                    int carPlate=0,carPosition=0;
                    if(lastCarPos == 0)
                    {
                        printf("You haven't car entry yet. Please insert car...\n");
                        countTry = 3;
                    }
                    else{
                        listCars(lastCarPos,carProperty,car);
                        printf("Enter the Plate Number of the car you want to get Payment information : "); scanf("%d",&carPlate);
                        if(checkInArray(countCar,carProperty,car,carPlate) == 1)
                        {
                            carPosition = paymentDetail(countCar,carProperty,car,carPlate);
                            /*
                                We are reaching the indis of car with Plate in the Array of Cars.
                                This function built for reach the informations of the cars and get those informations to use in Main function.
                            */
                            printf("\nPlate :\t\t%d\nCheck-in Time :\t%d\nCheck-out Time :\t%d\nVehicle Type:\t%d\nPayment :\t\t%d $\n\n",car[carPosition][1],car[carPosition][2],car[carPosition][3],car[carPosition][0],payment[carPosition][1]);
                            countTry = 3;
                        }
                        else{
                            printf("The Plate Number doesn't exist.\n");
                            countTry++;
                        }
                    }
                }while(countTry!=3);
             returnMenu(forMenu);
        break;

        /* Maximum/Minimum Payment Informations */
        case 4:
            countTry=0;
            do{
                int processChoise=0,max = 0,min = 0;
                printf("Maximum Payment\t\t-1  \nMinimum Payment\t\t-2 : "); scanf("%d",&processChoise);
                if(processChoise == 1)
                    {
                        max = maxPayment(lastCarPos,carProperty,payment,lastCarPos);
                        /*
                            maxPayment returns the Maximum value in Payment Array.
                        */
                        if(max == 0) // If Max = 0 that means our Payment Array is Empty.
                        {
                            printf("You haven't car entry yet. Please insert car...\n");
                        }
                        else{
                            printf("Maximum Payment: %d $\n",max);
                        }
                        countTry = 3;
                    }
                    else if(processChoise == 2)
                    {
                        min = minPayment(lastCarPos,carProperty,payment,lastCarPos);
                        /*
                            minPayment returns the Minimum value in Payment Array.
                        */
                        if(min == 0) // If Max = 0 that means our Payment Array is Empty.
                        {
                            printf("You haven't car entry yet. Please insert car...\n");
                        }
                        else{
                            printf("Minimum Payment: %d $'dir.\n",min);
                        }
                        countTry = 3;
                    }
                    else{

                    }
            }while(countTry != 3);
           returnMenu(forMenu);
        break;

        default:
            countTry++;
            tryChecker(countTry);
        break;
    }
    }
    while(countTry!=3);
}
/* FUNCTIONS */

/* Insert Car Function */
int addCar(int countCar,int carProperty,int car[countCar][carProperty],int payment[countCar][carProperty-2],int lastCarPos){
    /*
        Parameters respectively row,column ,Car Array, Payment Array and last car position(index).
    */
    int i,j;
    int flagOne=0,flagTwo=0,flagThree;
    for(i=lastCarPos;i<lastCarPos+1;i++)
    {
        /* Getting The Properties of Car */
        for(j=0;j<carProperty-1;j++)
        {
            countTry=0;
            if(j==0)
            {   do{
                printf("Motorcycle\t\t>1\nPersonal Car\t\t>2\nCommercial Car\t\t>3\Vehicle Type:");
                scanf("%d",&car[i][j]);
                if(car[i][j]>3 || car[i][j]<1){
                    countTry++;
                    car[i][j]=0;
                    /*
                        If vehicle type is wrong it assign car[i][j] with 0 with this assignment
                        we didn't filled our Array.
                    */
                    printf("Invalid Vehicle Type please enter type value between 1-3.\n");
                }
                else{
                    countTry = 3;
                }
                }while(countTry!=3);
            }
            else if(j==1)
            {   do{
                if(car[i][0]==1){
                    printf("Vehicle Plate (---) : ");
                }
                else if(car[i][0]==2){
                    printf("Vehicle Plate (----) : ");
                }
                else{
                    printf("Vehicle Plate (-----) : ");
                }
                scanf("%d",&car[i][j]);
                    if((car[i][j]>1000 || car[i][j]<100) && car[i][0]==1)
                    {
                        countTry++;
                        car[i][j]=0;
                        printf("Invalid Plate Number please enter plate number value 3 digits.\n");
                    }
                    else if((car[i][j]>10000 || car[i][j]<1000) && car[i][0]==2)
                    {
                        countTry++;
                        car[i][j]=0;
                        printf("Invalid Plate Number please enter plate number value 4 digits.\n");
                    }
                    else if((car[i][j]>100000 || car[i][j]<10000) && car[i][0]==3)
                    {
                        countTry++;
                        car[i][j]=0;
                        printf("Invalid Plate Number please enter plate number value 5 digits.\n");
                    }
                    /*
                        Like those 3 query above, if our plate info is wrong assign the car[i][j] with 0
                        and reject to fill our Array with wrong values.
                    */
                    else{
                        countTry=3;
                    }
                }while(countTry!=3);
            }
            else{
                do{
                    printf("Check-in Time <0-24> : ");
                    scanf("%d",&car[i][j]);
                    printf("Check-out Time <1-24> : ");
                    scanf("%d",&car[i][j+1]);
                    if(car[i][j]>24 || car[i][j]<-1 || car[i][j+1]<0 || car[i][j+1]>24 )
                    {
                        if(car[i][j]==0)
                        {
                            flagThree=1;
                        }
                        else{
                             car[i][j]=0;
                        }
                        countTry++;
                        car[i][j+1]=0;
                        printf("Invalid check-in/out time!\n");
                    }
                    else if(car[i][j+1]<=car[i][j])
                    {
                        countTry++;
                        car[i][j]=0;
                        car[i][j+1]=0;
                        printf("Check-Out time must be bigger than Check-in Time.!\n");
                    }
                    /*
                        If Check-In/Out time values invalid don't fill the Array.
                    */
                    else
                    {
                        countTry=3;
                    }
                }while(countTry !=3);
            }
        }
        /*
            End of Controls values.
            But thats not mean to car is added.
        */
        /*
            If the car parked already in the lot the query below output for error to adding car.
        */
        if(checkInArray(countCar,carProperty,car,car[i][1]) != 1)
        {
            if(checkInArray(countCar,carProperty,car,car[i][1]) == 0)
            {
                printf("Insert Car is Failed!(Invalid values)\n");
            }
            flagOne=1;
            printf("Insert Car is Failed!(Same car cant insert twice.)\n");
        }
        /*
            Those queries controlling also is anything missed or invalid in the car properties. Simply it checks for 0.
        */
        for(j=0;j<carProperty;j++)
        {   if((flagThree == 1 && j!=2) || flagThree == 0)
            {
                if(car[i][j]==0)
                {
                    flagTwo=1;
                    printf("Insert Car is Failed!(Invalid values)\n");
                }
            }
        }
        /*
            We used Flags above because we want to know "Does our query work?" if its work "What happend?" so this is why we used flags.
        */
        /*
            If those 2 queries above doesn't work
            Car adding to Parking Lot.
        */
        if(flagOne == 0 && flagTwo == 0 )
        {
            /*
                if addToPark query returns 0 (below)
                that means parking lot is full.
                addToPark sorgusu 0 donduruyorsa
                if parking lot is available to park it returns 1.
            */
            if(addToPark(car[i][2],car[i][3],car[i][1]) == 0)
            {
                printf("Parking Lot is Full between this Check-In/Out time.\nTo reach empty hours information -> Main Menu -> List Cars -> Parking Lot -> Hour List.\n");
                /*
                    addToCar fails. Set 0 the values and properties of this car and return the last car position.
                */
                for(j=0;j<carProperty;j++)
                {
                    car[i][j]=0;
                }
                return lastCarPos;
            }
            /*
                If everything goes right calculate payment and get values for Payment Array.
            */
            else{
            printf("Insert car successful!\n");
            payment[i][0] = car[i][1];
            payment[i][1] = calculatePayment(car[i][0],car[i][3]-car[i][2]);
            }
        }
        else{
            /*
                addToCar fails. Set 0 the values and properties of this car and return the last car position.
            */
            for(j=0;j<carProperty;j++)
            {
                 car[i][j]=0;
            }
            return lastCarPos;
        }
    }
    lastCarPos = i;
    return lastCarPos;
}
/* Insert into Lot Function */
int addToPark(int inHour,int exitHour,int carPlate){
    /*
        Parameters perspectively in hour, exit time, plate.
        It adds the car plate for every hour between in/exit time to someplace empty.
    */
    int i,j,indexPlate,capacity=0;
    for(i=inHour;i<exitHour;i++)
    {
        indexPlate=0;
        capacity=0;
        for(j=0;j<10;j++)
        {
            if(park[i][j]==0)
            {
                park[i][indexPlate]=carPlate;
                indexPlate++;
                break;
            }
            else
            {
                capacity++;
                indexPlate++;
                if(park[i][j]==carPlate)
                    continue;
                if(capacity == 10 )
                    return 0;
            }
        }
    }
    return 1;
}

/* Delete Car Function */
void deleteCar(int countCar,int carProperty,int car[countCar][carProperty],int payment[countCar][carProperty-2],int plate,int lastCarPos){
        /*
            Parameters perspectively, row, column, Car Array, Payment Array, plate, last Car Position.
            1. step:  using Plate for find the car informations in the Car Array and set the values to 0.
            2. step:  use the Plate information again and set 0 for the Payment informations to that car's informations.
            3. step:  delete the informations in the Parking Lot.
        */
        int i,j;
        for(i=0;i<lastCarPos;i++)
        {
            if(car[i][1] == plate)
            {
                for(j=0;j<carProperty;j++)
                {
                    car[i][j]=0;
                }
            }
            if(payment[i][0] == plate)
            {
                 for(j=0;j<carProperty-2;j++)
                {
                    payment[i][j]=0;
                }
            }
        }
        for(i=0;i<24;i++)
        {
            for(j=0;j<10;j++)
            {
                if(park[i][j] == plate)
                 {
                     park[i][j] = 0;
                 }
            }
        }
}
/* List Car Function */
void listCars(int row,int column,int car[row][column])
{
    /*
      Parameters perspectively, row, column, Array
      This function lists the Cars only.
    */
    int i,j;
    printf("Type\t\tPlate\t\tCheck-In\t\tCheck-Out\n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            if(car[i][j]!=0 && j!=2)
            {
                printf("%d\t\t",car[i][j]);
            }
            else if(car[i][j-1] != 0 && j==2)
            {
                printf("%d\t\t",car[i][j]);
            }
            else
            {
                break;
            }
        }
        if(j==column)
        printf("\n");
    }
}
/* List Car in Park Function */
void listPark(inHour,exitHour)
{
     /*
      Parameters perspectively, in,exit hours.
      This functions lists the cars between those two hours in Parking Lot.
    */
    int i,j;
    printf("Vehicle  : ");
    for(i=1;i<=10;i++)
        printf("%d\t",i);
    printf("\n");
    for(i=inHour;i<exitHour;i++)
    {   if(i<10)
        {
            printf("0%d:00 : ",i);
        }
        else{
            printf("%d:00 : ",i);
        }
        for(j=0;j<10;j++)
        {
            if(park[i][j]==0)
                printf("--\t");
            else
            printf("%d\t",park[i][j]);
        }
        printf("\n");
    }
}
/* Payment Calculater */
int calculatePayment(int type, int hour){
    /*
        Parameters perspectively, type and hour.
        It calculates the payment.
    */
        int payMuch = 5;
        if(type==1)
            payMuch += hour ;
        else if(type == 2)
            payMuch += (hour * 2);
        else
            payMuch += (hour * 3);
        return payMuch;
}
/* Payment Detailer */
int paymentDetail(int countCar,int carProperty,int car[countCar][carProperty],int plate){
    /*
         With those parameters this functions returns the index of car.
    */
    int i,j;
    for(i=0;i<countCar;i++)
    {
        if(car[i][1] == plate)
        {
            return i;
        }
    }
}
/* Maximum Payment Finder */
int maxPayment(int countCar,int carProperty,int payment[countCar][carProperty-2],int lastCarPos){
          int i;
          int payMax=payment[0][1];
          for(i=1;i<lastCarPos;i++)
          {
              if(payMax<payment[i][1] && payment[i][0] != 0)
                payMax = payment[i][1];
          }
          return payMax;
}
/* Minimum Payment Finder */
int minPayment(int countCar,int carProperty,int payment[countCar][carProperty-2],int lastCarPos){
          int i,j;
          int payMin=0;
          for(i=0;i<lastCarPos;i++)
          {
              if(payment[i][0]!=0)
              {
                payMin=payment[i][0];
                break;
              }
          }
          for(j=i;j<lastCarPos;j++)
          {
                if(payment[j][0]==0)
                {
                    continue;
                }
                else{if(payMin>payment[j][1])
                {
                    payMin = payment[j][1];
                }
                }

            }
          return payMin;
}
/* Check In Array Function */
int checkInArray(int row,int column, int car[row][column],int plate){
    /*
        If plate number exists in the Array it returns 1 else returns 0.
    */
    int i,j;
    int isThere=0;
    for(i=0;i<row;i++)
    {
        if(plate == car[i][1])
            isThere++;
    }
    return isThere;
}
/* Set Zero Function */
void setZero(int row,int column,int arr[row][column]){
    /*
        Resets the values in the Matris.
    */
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<column;j++){
            arr[i][j]=0;
        }
    }
}
/* Error Counter */
void tryChecker(int countTry)
{
    /*
        Display the outputs depend of error numbers.
    */
    if(countTry == 3)
    printf("Programme ending...");
    else
    printf("You made an incorrect entry please re-enter the value.\n\n");
}
/* Return To Menu Function */
void returnMenu(char forMenu){
    /*
        Returns the Menu or Exits the programme.
    */
    printf("\nTo Return the Main Menu press 'Y', To Exit the System press any key: ");
    scanf(" %c",&forMenu);
    if(forMenu == 'Y' || forMenu == 'y')
    {
        system("CLS");
        countTry = 0;
    }
}
