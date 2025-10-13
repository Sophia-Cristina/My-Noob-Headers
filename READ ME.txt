Codes here are codes i use since i began programming.
There are utterly noob things here mixed with more advanced things.
I'm too lazy to fix it all, so i do small changes by time.
However, i made such a system that ended up having so much useful stuff in a way that are independent of each
other that it began to be super useful to me.

I really use a lot my own headers.
It is kinda sad how some codes here are super bad, but i may eventually
fix, whenever i use a code i mess a little with it to fix some stuffs.
Some stuffs that are pretty bad that you may find are:
* Things that would be dealt with a 'template' instead of bloating with numerous functions with the same name;
* Lack of use of 'const' and 'constexpr';
* Lack of use of 'pointers' for objects that are better to be pointed instead of making a new instance (i had
to fix lot of 'CImg' image classes and functions because it was heavy and slow);
And many more! You can judge some of my code, but some of it you may judge unaware that i know it is bad.



PHILOSOPHIES AND CONVENTIONS:

* To add everything in the universe that may be of use, the most complete set of headers in the world.
All maths, all logic, all algorithms, magic, everything! Everything being independent and using alike methods.
However, in a way that headers can connect with each other when needed.
And so, for example, functions should work universally and be adaptable to be used by "very unrelated" codes.
Ex.: Electrical engineering headers can be used by trading headers that are used by gaming headers.

* To keep it simple, that any noob can understand. In fact, avoid some modern C++ codes that are not intuitive
for a C user. Try to keep it "C with Classes" + "C with Templates". I like templates, so i don't mind about using
it, however, won't make confusing things with it, there is no need to make a Turing machine with it.
This would be good in case i need to port things from different C++ versions or systems, there are lot of
functions i made that i can use in MS-DOS Borland C++, and i like this!
Considering such idea:
    * Avoid Lambda Functions, just make a normal function, unless if a lambda function would be
      a very useful optimization.
    * Prioritize to do a 'for loop' in the classic format: "for (size_t n = 0; n < N; ++n)";
      instead of "for (const auto& a : V)", but it can be used anyway.

* Based on that concept, use normal pointers instead of smart pointers, unless really need to be secure
about the pointer.
But, at the same time, since it is not C code. Would be better to avoid completely the "new" an "delete"
command, unless impossible to avoid.
I rather to cast something like "(char*)&Var" instead of using "new" and "delete".
I would say to use reference (&) instead of pointer if possible to substitute one to another without a problem.
If a function asks you for a pointer, instead of creating a pointer and using 'new', just pass as reference.
Basically, only create normal objects, and if something require a pointer, use a reference instead, and only
use pointers if that is the last resort.

* CamelCase, the one that starts with a capital letter.
For all data types, functions and classes. For everything but macros.
The use of underline '_' is reserved for the name tag of the headers from certain related directories
and subjects, ex.: 'ysxTRI_Something' for classes, functions, types and etc related to Triangles.
Using '_' in other situations may create confusion and reduce an intuitive approach (people may think there
are other nametags combined). It may be used in very specific cases.

* In the case of macros, it should be everything uppercase, common use constants don't need tags, but specific
macros have uppercase tags, ex.: "YSXTABLE_SOMETHING".

* The use of 'std::vector' almost exclusively as an array, even substituing lot of cases where it would be a
normal array (ex.: 'char a[100]' or 'std::array<>'). I got in lot of situations where i was messing with
the code and had problems that i noticed that i would need modify the array and then i would have to change
the code from a normal array to a vector. And so, even if useless, starting with a std::vector may avoid
possible problems in the future that would break a code when changing type, it is better and easier to change
a vector to an array than otherwise.
Only use arrays if it would be very obvious a constant size data, and, in my headers, i never 'malloc'
anything, use 'std::vector' instead, or better: don't do pointers as arrays. Why?! If there are better
options in C++, why then?! May create a 'std::vector' of pointers, and pass such pointers in a C
function if a header uses C or C-like code.
In such matter, take in mind the premise below.

* As pointed above, by the use of vectors, things that would require a normal array, like 'char a[100]' would
be dealt with a simple "C-like" casting, ex.:
"std::vector<> a(100);
SomeFuncThatUsesCharPointer((char*)&a[0]);"
This is seem as a bad practice by some programmers, but, i don't think so, i never had a problem doing that.
Take in mind that vector may change its location when resizing, but that is why i pass the pointer from the
actual memory location instead of saving the pointer somewhere else.

* And so, a convention and also a programming philosophy i have, is to be very specific in the type you use
even if that requires that it forces some strange and supposedly "dangerous" cast hacking to achieve a
objective.
Use specific types for the specific range needed, it is better that you start with an 'uint8_t' and later
figure out you should use 'uint16_t' than just 'int' everything. Once you adapt to it, you rarely get it wrong.
I use 'uint8_t' if the number wouldn't go above '255', and if it end up going, i would rather
rewrite to 'uint16_t' than to use an 'int' for convenience. This makes it universal to any system, compiler and
etc.
I also do that in 'for loop', i may use 'uint8_t' instead of 'size_t' if i know that it shouldn't be above '255',
this way, by merely reading the code, you know what you are messing up with. By seeing an 'uint8_t' in a 'for
loop', i know for sure this code wont deal with a large amount of processing.

* Focus extremely in object oriented, make a class for the most simple things that are a little more complex
than a simple function and use inheritation.
Use structs as data protocol / package, but don't abuse structs, the codes should be designed in a way that the
user writes the correct structs in the 'main' file, and that is it. That does not mean "do not make structs",
structs are very useful if you need to config a class or use a config on a function, that config which is used
in at least more than one place.
Most things that uses structs as a protocol have specific uses for such protocol that the struct can be
inside a class and then: just make a class for it.
However, a good use of structs are for things like data mapping. One example in my headers is the:
'ysxData/Files/ysxWAVE.h' for '.wav' files, this header have structures to deal with the file's header.
Since things like a file header is basically universal to everything people do for files, and so, that is not
a problem.

* I don't care about what people think, this is the best organization i have for my own coding and how i
learned to code, it is so ingrained in me that i learned how to map myself in such mess of heritage
connections that it is now a part of me. I can't think of a code without my mind going in directions of
"how to solve this" that are aligned with OOP.
I think there is no need to be a cultist in programming paradigms and languages.
People learn how to code by using stuff and it becomes part of their nature, i'm bad with Sniper in FPS games,
but i'm very good using an AK-47. This is because i learned how to play FPS with fast-paced games like Doom,
Quake and Half-Life.
Things are about how we do things at a point it become natural to us. I don't think there is something that is
inherently better, it may have one thing or another that is better.
Well, i said all that to say i focus on OOP, and i love C++, it is my fav language. I also like Ruby for small
things.
I think the critics towards C++ are poor and small, using small problems that are easily avoided,
or about the "bloat", that is STL and not C++, and which i like, because is standardized and you would
eventually have to do in other langauges or install a lib and learn a lib (that is like learning a new
language anyway) just because "MuH BlOaTed C++" and would end up with the same degree of bloatness anyway.
The same for Rust, i don't care about such "security features", modern C++ can deal very well with it, i think
C is the one that really have a problem with it, not C++, and it is also a small thing that is easy to deal
with C++.
I'm not a C++ cultist, even if i love this language a lot, it is just preference and a favorite.
I think the same way i grew with C++ is the same way a C and Rust cultist would feel about their languages,
it becomes part of us, our nature.
Once you begin to think in "C++-way", it is strange to change, even if you can. One example is how when i use
Ruby, even if Ruby is simpler, i still have to "re-think" how i code because my brain is thinking in my C++
solutions.

* Use UNIONS, people forget this awesome data type, even if there is rare use case.
Like one of the premises i said, be very specific in the type used, and so, this parameter also consider
that philosophy. And because my philosophy to avoid declaring pointers if you don't need to. Instead of using
pointer to "hack out" and cast a type, just use unions.
Even in Templates, I only use template types if i really need your class / function to use universal types.
Even 'void', i rarely use 'void' if not in a function, there are lot programmers that complain about that.
I care alot about data type, i like to know exactly what is happening in my machine.

* Use macros instead of 'const', unless it is inside a class or things like that.
Use macros mostly for 'const' and for text, scopes, tables, but avoid using macros for functions.

* I'm a polemic person, i think programmers should have lot of freedom to shot their own foot.
What i mean with that, is that i rather to interact with classes variables directly instead of using a
function for it.
And so, if something is not something that, in most cases, will break the class, let it in
'public', most things in a class should be 'public', going against a big majority of people.
Only use 'private' if it is something that should indeed be used exclusively by the class.

* Since the first lib i used was CImg, i love that they made everything in a single header file.
So my philosophy of headers came from this. I don't like, and i think it is worse in terms of readability,
to make a '.cpp' file to access and write functions inside a class, ex.:
class A
{
 int Something();
}

cpp file:
A::Something()
{ /*Code*/ }
Just write in the header file and inside the class, and that is fine.
I don't care about modifying a class directly instead of modifying a function that overwrites the
class function.
Also, with that being said, i also think it is more readable and uses less space to add all inside the
class scope instead of coding the functions outside of it.

* If a function or expression fits in a line, i think it is more readable to make it in a line.
I don't have OCD, but, i feel annoyed to vertical scrolling, i don't know why.
So, i rather have thousands of functions in a single line, than a simple function with multiple lines, ex.:
Instead of:
int area(int a)
{
 return(a * a);
}
Do:
int area(int a) { return(a * a); }

* As you can see above, i dislike return without parenthesis, it is a function, and in math, functions uses
parenthesis. all 'return' should be 'return()'.
The same for things like 'if', i used to make a line for a simple 'if' expression, until i had to modify and
noticed it was (even if a little) more of a chore to add in brackets than to make it already inside brackets.
So, instead of:
if (FooBar)
 DoSomething();
Do:
if (FooBar) { DoSomething(); } // Note, same line!
Even when there is an 'else', if it is simple and fits a line, it should be in a line. ex.:
if (FooBar) { DoSomething(); } else { DoAnotherThing(); }
It is not like modern computers have little horizontal space.
What do you think is more readable?:
int area(int a)
{
 return(a * a);
}
int square(int a)
{
 return(a * a);
}
int power(int a)
{
 return(a * a);
}
Or:
int area(int a) { return(a * a); }
int square(int a) { return(a * a); }
int power(int a) { return(a * a); }
Come on?! Am i the only one that thinks that things in a line is way more readable and organized?!
My opinion, and i have a strong opinion about that, in fact, i can't understand how someone would disagree
with me!

* Just like you can see in my examples, with multiple lines, brackets should have its own line.
Is that really better in terms of readability?:
int Func() {
 if (FooBar) {
 }
}
Better than that?:
int Func()
{
 if (FooBar)
 {
 }
}
Which one is easier to find the end of the function? Don't lie to me!

* Try to make comments fit a specific horizontal size. As someone that uses i3 in Linux, having to
scroll text horizontally is painful. Just make a new line.
Not only on Linux, if i want to have a 'fast read' of a code, i may use a notepad in a small window.
You can see the horizontal size i use in this document itself, or in the comments in my headers.






