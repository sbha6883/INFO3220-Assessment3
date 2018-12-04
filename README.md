# Read Me
Object Oriented Design

1. Extensions friendly design.
The Code Base “A” is implemented beautifully. Very clear and understandable implementations and coding. The code provides decoupling which is very helpful for some easy extensions. There were no concrete objects being passed around.
However, there are somethings to be mentioned in the code. All the mouse and Keyboard events happens in the dialog. But adding concrete implementation of the cue ball is not easy in the dialog because it should not know any concrete table elements. What’s being done in the code, is letting mouse event create a signal and letting the other objects deciding on how to use the signal. When the signals from dialog are released, the cue ball class used this connect function to call its own mouse function.
The ChangeInPoolGame class also allow to access to change the elements of the PoolGame to the class that have no access to the PoolGame class which allows a better functionality with weak coupling.
2. Implementation
All design pattern including abstract factory, builder, decorator and composite were implemented with good programming knowledge. It was a good idea to have use the ChangeInPoolGame class to give direct access to the ball vector int PoolGame to the table and ball object which intended to affect the ball vectors with the collision functions. The composite pattern was used to create the child balls in the parent ball. The code also has a call decorator to duplicate the balls. But he duplicated balls are so and have no control to change the size of the ball which I have tried to resolve.
3. Documentation of Code.
The code uses Doxygen comments which are quite helpful in describing most of the places such as header files, classes and member functions. This was very helpful when understanding the relation between different classes and other design decisions made in the program. There we some places where I thought the commenting was inadequate and required more explanation that I was looking for.
Generally, the code is of a really good quality and layout of the program is clean and well designed. It was very easy for me to be able to read the names and understand the purpose of those functions or classes but there were places where I was confused with some other names.
About my Code
1. Implementations:
Overview:
a. Clone() function added to all ball classes, which will support both deep copying balls for memento design pattern and ball cloning for prototype design pattern.
b. New classes and functions for the implementation of the undo feature using the memento design pattern
c. New classes functions for adding ball groups to the game using the prototype design pattern
Game new features:
Revert back
1. Game state will be auto saved, press “r” to revert the game to the state before firing the cueball last time.
Reset the game
2. Press “b” to totally reset the game to before the first time hitting the cue ball.
Adding new Group of balls
2. For stage 3, adding 1 ball in the “ballGroup” section in the config file will create a new group of same balls that are located in particular positions.
Memento Design Pattern
Key Classes and functions
Class: memento
member variable:
m_state: stores a list of balls' information in a Ball vector, which are the balls' deep copies given by the Originator (the PoolGame class). It is a snapshot of the balls' states.
function:
getSavedState(): return the m_state. This function is private, so it can only be called by the friend class PoolGame, which is the originator in memento design pattern.
class: PoolGame (which works an originator in Memento)
member vairable:
m_states: deep copy of each balls in current m_ball vector, which will be passed to memento to be saved as a snapshot of the game.
functions:
saveToMemento(): create m_states and pass it to memento when it is called.
restoreFromMemento(): replaces the balls (m_ball vector) in the pool game with ball copies in a given memento object when it is called.
class: dialog (which work as Caretaker in Memento)
functions:
saveState(): the dialog has keeps the PoolGame instance as a member variable, the saveToMemento() function of the PoolGame object—m_game is called here.
KeyPressEvent(): when detects a keypress, call restoreFromMemento() function of the PoolGame to revert the game.
class: cueballdecorator
function:
mousePressed(): when cueball is pressed, before shooting the white ball all the ball states will be saved by calling the saveState() function of the PoolGame class.
Advantage and Disadvantages
One of main benefits of the memento design pattern is the pre-existing encapsulation. It protects the stored states to be accessed by another object than the originator. Another important feature is the implementation of undo feature which is one of most important features in this game. At least I need this feature in every game. It is also a grate usability feature since like me, a lot of people are bound to make mistake and using this feature can retrieve their state back to a previous one.
One of the disadvantage that found was that there could be way too many balls that are stored in memento which in my program case we allow for adding balls and every time the state is saved, all balls have been cloned. If there was a way to optimize this feature by deleting older states.
Prototype design pattern
key classes and functions
Class: ball, stage1ball, stage2ball, balldecorator, cueballdecorator, duplicationballdecorator
function:
clone(): create and return a new ball that has the same state of the cloned ball. Because each ball class has this function, we can clone the ball without knowing which type of ball it is.
Class: gamebuilder
function:
addBallGroup(): By taking advantage of the clone function, we can create prototypes of a ball and add to the game. The function requires data from the table to location the ball group in the middle by default.
Without the clone() function, we will have to move each ball in the group one by one. With the clone() function, each ball's position is depending on where the original ball is. So, we need only to change the position of the original ball, then all other balls in the group will be moved together.
Class: initializer
function:
createPoolGame(): now reads the ballGroup data, only reads when it is stage 3. We need only one ball's information in the “ballGroup”, the ball will be cloned 5 times to create a group of 6 balls.
Advantage and Disadvantages
The prototype design pattern has a great advantage when it comes to simplifying the design patterns which still hiding the implementation details. C++ is a good language for using the Prototype pattern because classes are not “first class citizens” so you can’t pass then around as such. You can however pass around class instances which means you can call class methods on those instances such as “clone” which is used extensively in my implementation.
