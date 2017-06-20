/* DAILY PARKING LOT AUTOMATION */
This is a simple Daily Parking Lot Automation.
This Parking Lot has 10 parkings spaces.
Vehicles has 4 properties as Plate Numbers, Check-In time, Check-out time and type(1,2,3) of vehicle.

Enterance fee is 5$.
If the vehicle type is 1 add 1$ for every hour in parking lot, if vehicle type is 2 add 2$, else vehicle type is 3 add 3$ on enterance fee. 

/* TIPS FOR WEEKLY, MONTHLY OR LONGER PARKING LOT AUTOMATION */
First if you guys want to make it bigger.
  Add dimensions to the main arrays.(Car[][],Park[][],Payment[][])
	For Ex:(monthly)
	car[][]	-> car[30][CarCount][CarProperties]; // 30 is for Number of Days in a Month.
		or 
	car[][] -> car[30*(DailyCarCount)][CarPropeties];
	you can do the one of them for payment they are same.

	park[][] -> park[30][24][10]; // 30 is for Number of Days in a Month.
				      // 24 is for there are 24 hours in a Day.
				      // 10 for parking spaces you want.

After this changes you have to change and go for an other algorithm in functions "addCar,deleteCar, ListCars and Payments". Their logics are same but we just 
need to make it better for bigger datas.
You should add the dimensions of arrays, a couple loops for days, a couple ifs for the check-out time is bigger than 24 cuz it can be in Monthly or Weekly proccess 
and you got to the all of these in all the functions that connects between in the code.
	For Ex:
	Code Line 532:
 		we are calling the Car Array.
		if you guys add this Car array a dimension it has to be like this.
	      for(d = 0;d < 30 ; d++) // If its weekly you can make it to 7.
		{
		 for(i=0;i<row;i++)
   		 {
        		for(j=0;j<column;j++)
        		{
            			if(arr[d][i][j]!=0 && j!=2)
            		{
            	    printf("%d\t\t",arr[d][i][j]);
            	 }
		}	


/* TIPS FOR BIGGER PARKING LOT SPACES OR More/Less Car/Vehicle PROPERTIES YOU WANT TO KNOW */
You just need to change the numbers of these variables in the code.
	For Ex:
	countCar = 24 * ParkingSpaces; // Multiply with 24 because we are calculating the worst scene. For Parking Lot owner its the best scene. :)
	carProperties = 3; // Plate, Check-In, Check-Out if you do like this that means you dont need to know type of car and you'll gonna change the whole code for this situation.
	Monthly Ex:
	countCar = 30 * 24 * ParkingSpaces;