#include <Servo.h>

Servo base;
Servo left;
Servo right;
Servo claw;

void setup () {
    base.attach(3);
    left.attach(5);
    right.attach(6);
    claw.attach(9);
}

void loop() {
    base.write(90);
    left.write(170);
    right.write(90);
    claw.write(30);

    int i = 0;

    for (; i < 180; ++i)
    {
        base.write(i);
        right.write(i);

        if(i > 120)
        {
            left.write(i);
        }

        claw.write(i%30);

        delay(50);
    }

    for(i = 180; i > 0; --i)
    {
        base.write(i);
        right.write(i);

        if(i > 120)
        {
            left.write(i);
        }

        claw.write(i%30);

        delay(50);
    }
}