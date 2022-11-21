# Instructions for the program

## 1. **Generate matrix/map**

You can define the size of the matrix or the map in the config.txt file with statement like:
> SIZE = N

Plus, You can also define the new random numbers' portion with statement like this:
> RAND = R
---

## **2. Write commands**

You can write the command in the cmd.txt file in this format:
> OP1 OP2

 OP1 stands for the operation to cope, while the OP2 stands for the direction of the operation.

 **NOTE:** You have to know that even some operations do not have a direction, you still need an arbitary direction to have the program running fine.

### **Operations and directions**

#### **Operations**

|**Operation**|**Compatible with directions**|
|-------------|------------------------------|
|compress|Yes
|combine|No
|rotate|No

**NOTE:** You don't need to care whether the letters are upper or lower case, because an inner transformation will take place anyhow.

#### **Directions**

Even though **Up**, **Down**, **Left** and **Right** are recommended to use, but you can use any word with **U**, **D**, **L** and **R** as the first letter to be a direction.
