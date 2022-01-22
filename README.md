# Genetic-algorithm-implementation

## Work Description
In this work we implemented the Genetic algorithm from scratch with C++ & without using any library to get a deep understanding on every aspect in this subject

### Goal
As we know about the Genetic algorithms is we have to Define a Function that we need to maximise and try to find the best solution for that function by Applying Cross and Mutation for a set of given numbers in their Binary form, and it selects the best elements, and we mate these element between each other to get a better generation, and eliminates the weak ones, and keeps iterating until it converge to the best solution for a given function

#### Code parameters  
In this Code we chose:
*  Objective function as `pow(x, 2)` (and u can change it to what ever you want in the code)
* Population between 0 and 65 535

#### Code Workflow
1. Initialize Random First generation
2. Calculate Picked element with the Objective Function
3. Get the Binary form of these Elements
4. Calculating the selection probability of being picked
5. Loop through Elements and select the best Element   
6. Cross and mutate between those element
7. Stop when a probability percentage is reached or the maximum iteration is reached

#### Code Functions  
In this code you will find:

* Function `Dec2Bin` that transforms from Decimals to binary
* Function `Bin2Dec` that transforms from binary to Decimals

* Function `GenerateRandom` that generates Random elements from a given set of population
* Function `GenerateRandomPicking` that picks best couples to cross or mutation between them
* Function `HowmanyCouples` that sees how many elements that can mutate and cross
* Function `cross` that does the cross between two elements
* Function `Mutation` that does the mutation between two elements

#### Code Preview
##### Initialization
where we can chose the Cross and mutation chances and number of iterations
![ini](Results/Capture.png)

##### After 10 Iterations
![ini](Results/Capture2.png)

###### Information about the picked elements &  Details about the cross and mutation positions
![ini](Results/Capture3.png)

##### After 15 Iterations
![ini](Results/Capture4.png)

##### Best solution found after 15 Iteration
![ini](Results/Capture5.png)

#### Discussion
This is the Downside of genetic algorithms, like in this example the better solutions was in **Iteration 10**, (`x6 = 51 995`) but it was lost during the process because it had competition and his probability wasn't high enough to be picked as the best solution.
