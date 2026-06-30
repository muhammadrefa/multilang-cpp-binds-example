#include <iostream>
#include <cstdio>

#include "calculator.hpp"
#include "circular_buffer.hpp"

#include "animal/animal.hpp"
#include "animal/dog.hpp"
#include "animal/cat.hpp"
#include "animal/tiger.hpp"

void calculator_check()
{
    int val;
    // initialise calculator
    MyLibrary::Calculator *calc = new MyLibrary::Calculator();

    // addition
    val = calc->add(1, 1);
    printf("1 + 1 = %d\n", val);
    val = calc->add(2, 3);
    printf("2 + 3 = %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);

    // subtraction
    val = calc->sub(4, 3);
    printf("4 - 3 = %d\n", val);
    val = calc->sub(1, 4);
    printf("1 - 4 = %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);

    // reset
    val = calc->resetCounter();
    printf("counter resetted! last count %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);

    // 1 addition
    val = calc->add(100, 120);
    printf("100 + 120 = %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);\

    // destroy
    delete calc;
}

void circbuff_check()
{
    int len = 0;
    char arr[10];

    // initialise circbuff
    MyLibrary::CircularBuffer *buf = new MyLibrary::CircularBuffer(10);

    // insert 3
    len = buf->put("abcd", 3);
    printf("put %d filled %d\n", len, buf->getLength());

    // insert 5
    len = buf->put("12345", 5);
    printf("put %d filled %d\n", len, buf->getLength());

    // get 4
    len = buf->get(arr, 4);
    arr[4] = NULL;
    printf("get %d filled %d data %s\n", len, buf->getLength(), arr);

    // insert 5
    len = buf->put("abcde", 5);
    printf("put %d filled %d\n", len, buf->getLength());

    // clean
    len = buf->clean();
    printf("cleaned %d! filled %d\n", len, buf->getLength());

    // destroy
    delete buf;
}

void animal_check()
{
    // create animal1
    MyLibrary::Animal *animal1 = new MyLibrary::Animal();
    animal1->name = "specimen1";
    animal1->speak();

    // create animal2
    MyLibrary::Animal *animal2 = new MyLibrary::Animal("specimen2");
    animal2->speak(3);

    // adopt a dog
    MyLibrary::Dog *dog = new MyLibrary::Dog("Pluto");
    dog->speak();
    for (int i=0; i<7; ++i)
    {
        if (dog->fetch())
            std::cout << dog->name << " fetch the stick!" << std::endl;
        else
            std::cout << dog->name << " did not fetch the stick!" << std::endl;
    }
    std::cout << dog->name << " energy: " << std::to_string(dog->getEnergy()) << std::endl;
    dog->sleep();
    if (dog->fetch())
        std::cout << dog->name << " fetch the stick!" << std::endl;
    
    // adopt a cat
    MyLibrary::Cat *cat = new MyLibrary::Cat("Pretty");
    cat->speak(2);
    cat->fight(false);
    cat->fight(true);
    cat->fight(true);
    cat->fight(false);
    if (cat->stillAlive())
        std::cout << cat->name << " still alive" << std::endl;
    for (int i=0; i<9; ++i)
        cat->fight(true);
    if (cat->stillAlive())
        std::cout << cat->name << " still alive" << std::endl;

    // adopt a tiger (?)
    MyLibrary::Tiger *tiger = new MyLibrary::Tiger("Tigris");
    tiger->speak(3);
    tiger->fight(false);
    tiger->fight(true);
    tiger->fight(true);
    tiger->fight(false);
    if (tiger->stillAlive())
        std::cout << tiger->name << " still alive" << std::endl;
    std::cout << tiger->name << " hunger level: " << std::to_string(tiger->getHunger()) << std::endl;
    tiger->hunt();
    tiger->hunt();
    std::cout << tiger->name << " hunger level: " << std::to_string(tiger->getHunger()) << std::endl;
    tiger->sleep();
    std::cout << tiger->name << " hunger level: " << std::to_string(tiger->getHunger()) << std::endl;

    // kill them :(
    delete animal1;
    delete animal2;
    delete dog;
    delete cat;
    delete tiger;
}

int main()
{
    printf("--- calculator check ---\n");
    calculator_check();
    printf("\n");

    printf("--- circbuff check ---\n");
    circbuff_check();
    printf("\n");

    printf("--- animal check ---\n");
    animal_check();
    printf("\n");

    return 0;
}
