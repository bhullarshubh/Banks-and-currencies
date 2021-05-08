## Brief Description of our project
## Project on Currency 
## Team 4
> Prerak Srivastava ,Shubh Karman Bhullar, Knv Karthikeya, Rohan Madinei ,Sai Aaditya
## TA assigned
> Dhruv Sharma

### Objective of the project
To develop and design a currency exchange monitor that can :

1. Add or delete a trade bank.
2. Add or delete a currency.
3. Add or delete a currency conversion between two currencies.
4. Figure out the best possible path to convert the given two currencies.

## Our approach towards this problem

The first data structure that came to our mind for solving this problem was to use graphs and the various algorithms associated with graphs.

1. Create an array of all the trade-banks given by the user.
2. Each Trade-bank will have it's individual graph.
3. Each node in the graph here behaves like a node containing the currency name and it's respective weight.
4. The following graph can be represented in the form of a adjacency matrix or a list.
5. Each currency is linked to the other on the basis of the input given by the user.
6. Application of various algorithms like DFS,BFS,Dijkstra etc depending on which gives us the best case scenario in finding out the best path to convert a given currency A to a given currency B.
7. Example : If all the weights of the graph are equal it is better to use BFS rather than Dijkstra as it gives us a faster result as 
$$ Time \ complexity \ of BFS \ is \ O(V + E) \ as \ Dijkstras \ is \ O(V + E(log(V))) $$
---

This is our raw solution to the given problem statement.

---


![Example](graph.png)

Here A,B,C and so on depict the currencies and hence are the Vertices.
The edges are the conversions from currency X to currency Y.

