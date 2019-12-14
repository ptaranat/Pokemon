# Text-based Pokemon Game

## Commands List
```
v       advance time 1 step
x       advance time until something happens or 5 units passed

m 1 2 3 move Pokemon 1 to location (2, 3)

g 1 3   move Pokemon 1 to Gym 1
g 1 3   train Pokemon 1 at Gym 1

c 1 2   move Pokemon 1 to Center 2
r 1 2   heal Pokemon 1 at Center 2

a 1 2   move Pokemon 1 to Arena 2
b 1 4   have Pokemon 1 battle Rival 4

s 1     stop Pokemon

n [char] 1 5 6 create a new object ID=1 at location (5, 6)  
        valid codes: P Pokemon, G Gym, C Center, R Rival

q       quit
```

Check out the `attack` branch for these additions  
- Improve battle function
- Lets you select moves, Rival randomly selects moves
- Display health as @ symbols instead of numbers
- Can add as many Rivals and update the Arena's num_rivals automatically
