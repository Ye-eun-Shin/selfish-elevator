# selfish-elevator🛗
[문제해결] dp를 이용한 elevator optimization 문제 : 딱 몇 개의 층에서만 내려드립니다^ㅡ^

## 1️⃣ Problem explanation
### Problem Summary

There is an **elevator** that doesn't want to work, so everyone doesn't stop on the floor that they want to get off, but only on **the given number of floors**. 

So it's a question of finding a combination of floors that minimizes the cost of going 
up and down the floor. If the cost is the same, output the **highest** layer among 
them.

### Example

• nriders = 2, nstops=1

• One wants to get off on the first floor, and the other wants to get off on the third 
floor.

➡️ In this case, all have the same cost of 2 whether they get off the first floor, 
second floor, or third floor. 

➡️ Therefore, the highest third floor is the answer.

## 2️⃣ Solution explanation
**0. Variable Definition**

**1. Calculating the cost between two floors**

  - When there are people who want to get off between the two floors, see which of the two floors is closer, and calculate the cost when they go close.
  - The innermost if syntax was added because it was correct that all of them should be lowered to the current side if the previous is 0 and the current is not INT_MAX.
  
**2. Floors are piled up slowly => Dynamic Programming!!**
  - Resetting everyone to get off the 0th floor
  - Stack layers one by one from the first floor, and store the minimum cost in the array and the optimal solution in the array.
  - In order to store the highest layer in p, the p value was updated even when the cost was the same.
  - When determining the last layer, the index with the smallest value is the last layer, looking back at the last column of m recorded so far.
  - It is designed so that the last stop value is updated even when the m value is the same so that the highest layer is selected when the cost is the same.

**3. Deciding which floor to stop**
  - This continues to call out **its very downstair** through recursive functions.
  - The resulting values are stored in an array called **result**. This will save it from downstairs.

**4. Outputting Results**
  - All values were inserted into the result array as the **reconstruction_path** function.
  - It compares the value in the result with the destination layer that people are trying to get off, and determines **the nearest number** as the destination layer and outputs it.
