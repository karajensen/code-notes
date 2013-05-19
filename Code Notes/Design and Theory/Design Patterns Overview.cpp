//////////////////////////////////////////////////////////////////////////////
//DESIGN PATTERNS OVERVIEW
//////////////////////////////////////////////////////////////////////////////
/*

=============================================================================
CREATION PATTERNS
=============================================================================

FACTORY:   
Creates groups of objects

BUILDER:   
Connects together components of the one object

PROTOTYPE: 
Copies from a set of base objects to create new objects

SINGLETON: 
Ensure a class only has one instance and allow anyone seeing that 
class to have access to it
                                                                             
=============================================================================
STRUCTURAL PATTERNS                                                          
=============================================================================

PIMPL:     
Allows changing the implementation without touching the interface

DECORATOR: 
Allows mixing/matching of classes without need for writing a 
subclass for each and every match

FLYWEIGHT: 
Use of an object to store common information for a class of objects

COMPOSITE: 
A class built ontop of an object class that manages groups of the objects

PROXY:    
Uses a pointer/reference/proxy object to send changes to the real object

FACADE:   
Wrapper class on top of a complicated class

ADAPTER:   
Wrapper class on top of unrelated classes

BRIDGE:    
Creates a bridge between a class and different ways of using that class
           

=============================================================================
BEHAVIOURAL PATTERNS
=============================================================================

MEMENTO:     
Allows object to restore to a previous state (undo/redo)

ITERATOR:    
Allows movement over range of elements in a container

INTERPRETER: 
Decodes each symbol in a string/sentence

TEMPLATE:    
Skeleton algorithm; changing a method won't change the overall algorithm

COMMAND:     
Holds a method and the object to use the method and used as a 
functor at a later time

CHAIN OF RESPONSIBILITY:         
Passes a command through a series of objects until handled

STATE:       
Alters an object's behaviour when its state changes

STRATEGY:    
Allows choosing an algorithm at runtime

VISITOR:     
Seperates objects from their methods; calls custom methods in 
derived objects from base*

OBSERVER:    
Sends an event message when an object changes state to any observers

MEDIATOR:    
Talks between two classes without either having to know about the other