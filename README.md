# AdvProg1-3: KNN: K-Nearest Neighbors
Third task for Advanced Programming 1 course

Authors:
Gal Pearl,
Dekel Schreiber

In this task, there will be five algorithms for calculating vectors, in different approaches.
For example:
We will receive a vector of data of some flower, lets say an Iris. We will find it's closest neighbor, with the least difference between their
attributes:
1) Cup leaves width
2) Cup leaves length
3) Petals width
4) Petals length
We will find the closest neighbors and classify the input vectors as the flower.

Comparisons can be made between each family: Irises, Wines, Beans, etc etc.

### Compliation Instructions:
First, clone/download zip of the repository, 
cloning:
```
git clone https://github.com/GLPRL/AdvProg1-3
```
(ZIP requires unpacking, use your preffered method)
Among all the files, there's a makefile for using make:

```
make
```
Then, the output will be a.out. Now you can run it:

**For the program to identify the input files, they need to be in the same directory with the project files**

```
./a.out <Some integer for K> <file.csv> <ALG>
```

   
Instruction for fillers (Any <>):
- <K> must be a natural number (K>0). We will check if it is valid.
- <file.csv> is required to be in the same directory with project files/a.out . We will check for this requirement.
- <ALG> must be one of the following, resepectively to the algorithms we implemented:
   1) AUC for Euclidan
   2) MAN for Manhattan
   3) CHB for Chebyshev
   4) CAN for Canberra
   5) MIN for Minkowski
 The program will check if the parameters are valid.

## General implementation details
### Distance Algorithms

In this project, we created a Main file, which will handle all the basic requirements -
Building the vectors according to the user's input as command line arguements, 

The algorithms implementation reside in Algorithms.cpp source file. There is also a header file Algorithms.h for this source file which the main includes in order to have access to the algorithms.

The Algorithms are implemented in accordance to the guidlines that are listed below.

List of Algorithms:

1) Euclidean Distance: We receive two points, each one will be represented as an array - the size of the array is as the size of the dimension.
   Points will be marked as P and Q, and coordinates will be marked as p1, p2, p3 .... and q1, q2, q3 .... for each i, qi and pi will be the coordinate of the
   point, and "i" will not be larger than the size of the dimension. General idea:
   
   ![image](https://user-images.githubusercontent.com/116657293/201177857-87b63e5f-3d96-40c0-8830-92bd56ce6340.png)
   
2) Manhattan Geometry: Sum of two points in their cartesian coordinates. We will receive two points, in a given dimension, marked as N.
   Points are represented by arrays with N slots.Calculation will present the sum of lengths of the projections of the line segment between points onto the coordinate      axes. Formally:
   
   ![image](https://user-images.githubusercontent.com/116657293/201179543-c6ef7476-f613-4903-acb6-cb0a0cbf0a75.png)
   
   Where P = (p1, p2, ... , pn) and Q = (q1, q2, ... , qn)
   
3) Chebyshev Distance: The distance is defined by the greatest distance difference, between two vectors, in a vector space.
   Each vector will be represented by N numbers (N >= 1), and will be represented as an array. For each Xi and Yi, as Xi is a coord. from X, and Yi from Y,
   will return the max distance of Xi - Yi, for each i in range of 1 to N. Formally:
   
   ![image](https://user-images.githubusercontent.com/116657293/201183032-e4f08c81-3ece-415a-b3d4-25ccf5729271.png)
   
4) Canberra Distance: numerical measure of the distance between pairs of points in a vector space. It is used to compare ranked lists.         
   Formally: (For P = (p1, p2, ... , pn) and Q = (q1, q2, ... , qn))
   *Fun fact: Also used for intrusion detection in computer security (IDS).*
   
   ![image](https://user-images.githubusercontent.com/116657293/201183812-5c097577-4977-4eff-a4cc-c545d3817105.png)

   **Important Notice** : If Pi = Qi = 0, then we divide by zero. Instead, the calc. of abs(Pi)+abs(Qi), will make the division
   zero, in total, with a simple condition to check if it's met. Otherwise, the program will work as usual.

5) Minkowski Distance: metric for a normed vector space, which is a generalization of Euclidean and Manhattan Distance formulas.

   ![image](https://user-images.githubusercontent.com/116657293/201184801-bcb3d888-f0a9-4b54-8b15-e9f8aa8c3509.png)

      As for P: The formula uses P=1 or P=2, which corresponds to the Manhattan and Euclidean formulas, respectively.
      In this task, we take P=2 only (as stated by TA, We can choose any parameter P). So eventually, it'll run Euclidean formula.
      
### TypeVector
We introduce a new object: TypeVector.
It contains three field:
   - Vector of double type numbers. Stores values of location in some dimention
   - String, describing the type of the vector. Ex.: Our vector is a type of flower, "iris-versicolor". So, "iris-versicolor" will be stored.
   - Distance of type double. We will store the distance of the vector with a given user vector, according to algorithm of their choosing.
### Classification
We receive some vector of some size, and calculate it's differences between all the known vectors.
Afterwards, we find the K closest neighbors - their attributes are the closest to our data vector.
Lastly, we classify our input vector according to the type we see has the most neighbors to our vector,
and print our decision to the user.

###### Images and some explanations sourced from Wikipedia pages of the distance formulas
