# Syntax

## Control Flow

A program reads from left to right, then top to bottom (like a book). This is known as control flow. When the program is run a set of instructions is created to determine how it is run. In processing, it is guaranteed that only one instruction will be run at a time. The order may change during runtime due to if statements, loops, or any other runtime decisions.

## Pseudo-Code

Pseudo-Code is instructions that help us to understand what our code does. Large projects can reach thousands of lines of code and with a team, hundreds of thousands. Without comments, it would be very difficult to understand exactly what everything does. When the program runs, pseudo-code is just ignored. Pseudo-code is often simply referred to as comments. To type a comment in processing simply type two slashes

'''//The rest of the line is ignored by the compiler'''

We can also type multiline comments using this format.

'''/* 
Any text in between will be ignored by the compiler too. 
 */'''

## Statements

A statement is a complete instruction to the computer. For example, drawing a shape would be a complete instruction. Adding two numbers together isn’t. This will become more clear as syntax is shown, but the importance of understanding this is that a statement must be terminated by a semicolon. 

'''statement;'''

We can also create compound statements which don’t need to be followed by a semicolon. A compound statement is able to have as many statements as you want, this example only shows two. The syntax for a compound statement is as follows. Keep in mind that the indentation is simply cosmetic and the spaces don’t actually matter here.

'''{

	statement;
	statement;

}'''

# Functions

Functions are tools that allow us to assign a name to a chunk of code. They don’t work this way internally (most of the time), but for all intents and purposes, we can think of them this way. Processing gives us many predefined functions so that we don’t have to worry about the code that is executed when we call them.

## Predefined Functions

size(width, height); Set the width and height of the window

background(r, g, b); draws a background with that color
fill(r, g, b); sets the next fill color for the next shapes
stroke(r, g, b); sets the next outline color for the next shapes
strokeWeight(thickness); sets the thickness for the stroke

rect(x, y, w, h); draws  a rectangle with top-left point and (x, y) with width w and height h
ellipse(x, y, w, h); draws oval with center at (x, y) and width and height of w and h
triangle(x1, y1, x2, y2, x3, y3); connects (x1, y1); (x2, y2); and (x3, y3) into triangle
point(x, y); places a point at (x, y)

# Operators

Operators are a tool in programming that takes in two values and give one value back. All but a few of the operators follow this rule. We have six different types of operators in processing: arithmetic, comparison, logical, assignment, conditional, and bitwise. This is certainly a handful but it will become clear as you read about them.

## Arithmetic Operators

Arithmetic operators are used to compute simple arithmetic and you are likely familiar with them already. 

+, -, *, /, %, 

# Variables

Variables are containers in a program. They store a value and have a name. We can only use a variable once we’ve created it. We need to know two things about a variable before we create it: the name and the data type. The name is straightforward but the data type is slightly more complicated. Essentially, a data type is the type of container it is, or what kind of data it will hold. Here is a list of the data types support by processing.

## Data Types - Primitives

*    int (an integer)
*    float (a decimal number, or integer)
*    double (a decimal number, or integer, but it can be bigger)
*    long (an integer, but it can be bigger)
*    char (a letter or a character)
*    byte (a numerical value of 8 bits, not very useful)
*    boolean (true or false)
*    color


## Data Types - Composite

*   Array
*   ArrayList
*   FloatDict
*   FloatList
*   HashMap
*   IntDict
*   IntList
*   JSONArray
*   JSONObject
*   Object
*   String
*   StringDict
*   StringList
*   Table
*   TableRow
*   XML


## Assignment vs. Comparison

In algebra, is it perfectly reasonable to say that x = 5 and 5 = x. But in programming, the equals symbol isn’t saying that the two values are equal. Instead, it takes the right value and copies it into the left value. That means that saying 5 = x, is changing the value of the number five, which isn’t allowed by the computer.

## Scope

Scope in programming is the idea that in whatever place a variable is declared it can’t be used outside of that area, also known as scope. For example, if we create a variable inside of our draw function, it will not be able to be used anywhere else. Not only this, but it will be destroyed after draw ends. Since draw is called repeatedly, it will just create a new variable every time.

## Creating Variables

There are many ways to create a variable or multiple variables. You don’t need to put in a value right away. You can also create multiple variables by listing them with commas. You may use any combination of these:

'''Type Name;

Type Name, Name, Name;

Type Name = Value;'''

## Assigning Values

Assigning a value to a variable is usually done using the following format. However, we also can change the value of any variable by a certain factor.

'''Name = Value;'''

## Predefined Variables

Processing has some predefined variables that will update automatically as they change. 

*   width (width of window)
*   height (height of window)
*   mouseX (mouse position on x-axis)
*   mouseY (mouse position on y-axis)
*   frameRate (fps)


# If Statements

Checks if a condition true, and if it is, then executes specified code. Otherwise, it just skips the section.

## Structure

'''if (comparison)
{
  code...
}'''


# Project Code

'''void setup() { 
	size(800, 600);
}

void draw() {

}'''