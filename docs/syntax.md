NoctScript Syntax
=================

NoctScript is a simple scripting language.

## Assignments

Variables in NoctScript are dynamically typed and don't require explicit
declaration. The assignment operator (`=`) is used to create and
assign values to variables.

As shown in the example below, NoctScript supports various data types
including integers, floating-point numbers, and strings. Variables can
be reassigned to different types at any time during execution.

```
func main() {
    a = 123;
    print(a);

    b = 1.0;
    print(b);

    c = "string";
    print(c);
}
```

## Explicit Local Variables

Using the `var` keyword allows you to explicitly declare a variable as
local. This significantly reduces variable lookup time and can make
your program run faster. Without `var`, assigning to a variable
triggers a symbol lookup across both local and global scopes, which is
less efficient.

```
func main() {
    var a = 123;
    print(a);
}
```

### Array

Arrays are ordered collections of values, accessed by index. Arrays
support iteration through the `for` loop construct, allowing you to
iterate through each value directly.

```
func main() {
    array = [0, 1, 2];
    for (value in array) {
        print(value);
    }
}
```

Arrays can hold values of different types simultaneously, reflecting
the dynamic typing system.

```
func main() {
    array [123, "string"];
}
```

The language provides a built-in function `push()` to add elements to
the end of an array

```
func main() {
    array = []
    push(array, 0);
    push(array, 1);
    push(array, 2);
}
```

### Dictionary

Dictionaries store key-value pairs, similar to hash maps or objects in
other languages. They are defined using curly braces with key-value
pairs separated by colons. Dictionaries support iteration where both
the key and value can be accessed simultaneously.

```
func main() {
    dict = {key1: "value1", key2: "value2"};
    for (key, value in dict) {
        print("key = " + key);
        print("value = " + value);
    }

}
```

Dictionaries may be constructed in a single step way. An assignment
can be an array style which uses `[]`, or an object style which uses
`.`.

```
func main() {
    dict = {};
    dict["key1"] = "value1";
    dict.key2 = "value2";
}
```

The built-in function `remove()` allows for the deletion of entries by
key.

```
func main() {
    dict = {key1: "value1", key2: "value2"};
    remove(dict, "key1");
}
```

### For-loop

The for-loop construct provides a concise syntax for iterating through
sequences such as ranges, arrays, and dictionaries.

The range syntax (using the `..` operator) creates an iterator that
generates values from the start to one less than the end value.

```
func main() {
    for (i in 0..10) {
        print(i);
    }
}
```

For-loops can also iterate directly over arrays and other collection
types.

Arrays can be iterated by the for-value syntax.

```
func main() {
    array = [0, 1, 2];
    for (value in array) {
        print(value);
    }
}
```

Dictionaries can be iterated by the for-key-value syntax.

```
func main() {
    cit = {key1: "value1", key2: "value2"};
    for (key, value in dict) {
        print(key + "=" + value);
    }
}
```

### While Loops

The while-loop provides a traditional iteration mechanism that
continues execution as long as a specified condition remains
true. Unlike for-loops which are designed for iterating over
collections, while-loops are more flexible and can be used for
implementing various algorithms where the number of iterations isn't
known in advance. The example shows a basic counter implementation
incrementing from 0 to 9.

```
func main() {
    i = 0;
    while (i < 10) {
        print(i);
        i = i + 1;
    }
}
```

### If and Else Blocks

Control flows allow for conditional executions based on evaluated
expressions. The if-else construct follows a familiar syntax where
conditions are evaluated in sequence.

```
func main() {
    a = readint();
    if (a == 0) {
        print("0");
    } else if (a == 1) {
        print("1");
    } else {
        print("other");
    }
}
```

### Lambda Functions

Functions are first-class objects in the language. Anonymous
functions, also known as `lambda` expressions, allow you to create
functions without names.

```
func main() {
    f = lambda (a, b) { return a + b; }
    print(f(1, 2));
}
```

Lambda functions are simply translated to named functions in the
compilation process. Therefore, they can't capture variables declared
in outer functions.

## Intrinsics

### substring()

```
func main() {
    var s1 = "ABCDEFG";
    var s2 = substring(s1, 1, -1); // from the char 1, to the end
}
```

### length()

```
func main() {
    var str = "ABCDEFG";
    var slen = length(str);

    var array = [0, 1, 2];
    var alen = length(array);
}
```

### push()

```
func main() {
    var array = [0, 1, 2];
    push(array, 3);        // Add to the last.
}
```

### global

```
func main() {
    var my_class = {
        member: 0,
        method: lambda (this, a) {
            return this.member + a;
        }
    };

    global("MyClass", my_class);
}
```
