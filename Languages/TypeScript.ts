/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TYPESCRIPT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Adds type system to Javascript and future features
• Node.js is the environment used to run the TypeScript compiler
• Use VSCode and Live Server for hotloading
• Use NVM for Windows Node.js and NPM management
**************************************************************************************************************/

// VARIABLES
let x: string;                     // Define type of variable  
let x: 'str';                      // String literal, can only hold value 'str'
let x: boolean = true;
let x: number = 100;               // All numbers are floating or bigint
const x: number = "str";           // BAD Assigning string to number gives error (accepted in Javascript)
let x = 10;                        // Auto adds the ': number' with first assignment

// GLOBAL VARIABLES
// Can be seen by whole app, requires 'var'
declare var myGlobal: number                // For files without any import/exports, 'declare' optional
declare global { var myGlobal: number; }    // For files with import/exports

// UNKNOWN
let x: unknown;                    // Type not initially known but still requires type checking
(x as number[]).length             // Requires calling methods with explicit type

// ANY
let x: any;                        // Type not known and disable type checking (Javascript)
let x;                             // No type or assignment auto becomes 'any'

// ARRAYS
let x: string[] = ['x', 'y']; 
let x = [1, 2, 3, 'x'];            // Type set to array of numbers and strings only

// TUPLES
let x: [string, number, number?];  // Tuple with 2 arguments and 1 optional argument
x = ['str', 5];

// UNIONS
let x: number | string;            // Allow both number of string but no other type

// ENUMS
enum MyEnum {
    One = 1,    // Normally starts with 0
    Two         // Auto assigned 2
}
MyEnum.One

// TYPE ALIAS
type MyAlias = MyType;
type MyObject = {  // Alias object
  str: string;
  x: number;
};
type MyConcat = MyObject & MyObject2;  // Combining types
let myConcat: MyConcat = {
    str: "str"
    x: 10
    x2: 20
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function fn(x: number, y: number) : number { return x + y; } 
function fn(x: number | string) { }      // Union as type
function fn(x: MyEnum) { }               // Enum as type
function fn(x: number, y?: number) { }   // Optional parameter, if not set will be undefined, must be last in list
function fn(x: number = 10) { }          // Default values, can be set in any order in list
function fn({x, y}: MyObj) { }           // Object destructuring with type
function fn() : void { }                 // Void for no return, implicit
function fn() : MyObj {
  return {
    str: "str",
    value: 1.0
  };
}

// ARROW FUNCTIONS
let fn : (x: string) => string;
fn = function (x: string) { return "str"};

// REST PARAMETERS (VARIADIC ARGS)
// A function has only one rest parameter
// The rest parameter appear last in the parameter list
// The type of the rest parameter is an array type
function fn(...numbers: number[]) { numbers.forEach((num) => console.log(num)); }
function fn(...numberAndStrings: (number | string)[] { } // Allow multiple types

// FUNCTION OVERLOADING
// Parameter count must be the same, optionals not part of count
function fn(a: number, b: number): number;
function fn(a: string, b: string, c?: number): string;
function fn(a: any, b: any): any { } // Implementation uses any but only accepts types from overloads
function fn2(a: number): number;
function fn2(a: number, b?: string) { } // Implementation 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASSES / OBJECTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MyClass {
  x: string;                                 // Defaults to 'public'
  protected y: number;                       // Only access inside class and subclasses
  private z: number;                         // Only access inside class
  readonly value: number;                    // Const member
  private static headcount: number = 0;      // Shared across all instances of class

  constructor(x: string) { this.x = ssn; }
  getFn(): string { return this.x }
  private getFn(): string { return this.x }
  public static staticFn() { }

  // Adds property with setter/getter, access like normal property 'obj.myProp'
  get myProp() { return this.x }
  set myProp(x: number) { this.x = x }
    
  // Function Overloading
  count(): number;
  count(target: number): number[];
  count(target?: number): number | number[] { return 1 }
}

// INHERITANCE
class MyClass extends MyBaseClass { // MyBaseClass becomes prototype
    constructor(value) {
        super(value); // Call base constructor
    }

    // Override base function
    myBaseFn(): string { 
        return super.methodInParentClass();  // Call method from base class
    }
}

// OBJECTS
let obj: {};   // Empty object
let obj: {
    str: string;
    value: number;
};

// ABSTRACT CLASSES
// Define function without implemtation, requires implementation in derived classes
abstract class MyAbstractClass {
    abstract fn(): number; 
}
class MyClass extends MyAbstractClass {
    fn(): number { return 1; }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERFACES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Used to enforce types and contracts for objects, functions, classes
interface MyInterface {
    x: string;
    y?: string;           // Optional, can be in any order
    readonly z: number;   // Only modifiable when object first created
}
let value: MyInterface = {
  x: 'x',
  z: 10
};

// EXTEND INTERFACE
interface MyInterface {
    fn(): string;
}
interface MyInterface extends MyBaseInterface {
    fn2(): boolean;
}
interface MyInterface extends A, B, C  {
}

// FUNCTION INTERFACES
interface StringFormat {
    (str: string, isUpper: boolean): string
}
let format: StringFormat = function (str: string, isUpper: boolean) {
    return isUpper ? str.toLocaleUpperCase() : str.toLocaleLowerCase();
};

// CLASS INTERFACES
interface MyInterface {
  fn(): string;
}
class MyClass implements MyInterface {
  constructor() {}
  fn(): string { return ""; }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GENERICS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GENERIC FUNCTIONS
function fn<T>(items: T[]): T { // Enforces passed in type and returned type are the same
    return items[0];
}
fn<number>(arr); 
fn<string>(arr); 
fn<MyType>(arr); 

function fn<T1, T2>(obj1: T1, obj2: T2) { }   // Multiple types
function fn<T extends object>(T obj) { }      // Enforce specific types

// Generic Keys
function fn<T, K extends keyof T>(obj: T, key: K) {
    return obj[key];
}
fn({ key: 'value' }, 'key');

// GENERIC CLASSES
class MyClass<T> { }
class MyClass<T1,T2>{ }

// GENERIC INTERFACES
interface MyInterface<T> { 
    x: T; 
    fn(obj: T): void;
}
interface MyInterface<T1, T2> { }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MODULES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MyModule.ts
export interface MyInterface { } // export will allow it to be used outside module
export { MyInterface };          // export can be placed at bottom after types declared

// App.ts
import { MyInterface } from './MyInterface';
import { MyInterface as MyAlias } from './MyInterface';
import * from './MyInterface';  // Import everything
