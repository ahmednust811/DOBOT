#DOBOT PROGRAM GUIDE
PUT THE ARRAY OF TABLE VALUES IN MOEVEMENT TABLE LIKE THIS
___________________________
| X | Y | Z | R | TYPE    |
|__ |__ |__ |__ |________ |
THERE ARE FOUR TYPES OF TYPES
home_t -> home type(1)
move_t  -> move type(2)
pick_t  -> pick type(3)
place_t  -> place type(4)

while making the array values from table you can either put the labels of types defined above OR the corresponsing int value

n_cds -> number of CDs in the rack at the moment the program doesnot have any effect of it but the value should be atleast 1 
columns -> number of columns in array at the moment they are '5' neglecting the suction column 
rows -> total number of rows of the table

NOTE: first point must always and always be home point.
